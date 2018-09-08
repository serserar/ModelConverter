/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Main.cpp -- Copyright (c) 2006-2007 David Henry
// last modification: jan. 28, 2007
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Doom 3's MD5Mesh Viewer main source file.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // WIN32

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GlErrors.h"
#include "Mathlib.h"
#include "Font.h"
#include "Md5Model.h"
#include "TextureManager.h"
#include "ArbProgram.h"
#include "Shader.h"
#include "GLRender.h"
#include "../base/Camera.h"
#include "../util/ImageUtils.h"
#include "../image/PPMReader.h"
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

AnimatedModel* bmodel = nullptr;
vector<Ray> rayList;
Camera* cam = nullptr;
Texture2D* texture = nullptr;
Md5Model *model = NULL;
//Md5Object *object = NULL;
TTFont *font = NULL;
SDL_Window* surface;
// Current shader and vertex/fragment programs
ShaderProgram *shader = NULL;
ArbVertexProgram *vp = NULL;
ArbFragmentProgram *fp = NULL;

// All vertex and fragment programs
ArbVertexProgram *vp_bump = NULL;
ArbVertexProgram *vp_bump_parallax = NULL;

ArbFragmentProgram *fp_diffuse = NULL;
ArbFragmentProgram *fp_diffuse_specular = NULL;
ArbFragmentProgram *fp_ds_parallax = NULL;

// We can use a specific render path, depending on
// which shader/program we want to use...
render_path_e renderPath;

// Tangent uniform's location
GLint tangentLoc = -1;


int renderFlags = Md5Object::kDrawModel;
int fps = 0;

bool bAnimate = true;
bool bTextured = true;
bool bCullFace = true;
bool bBounds = false;
bool bParallax = false;
bool bLight = true;
bool bSmooth = true;
bool bWireframe = false;
bool bDrawNormals = false;
bool bDrawVoxels = false;

vector<string> animations;

const char windowTitle[] = "MD5 Model Viewer Demo";
const int windowWidth = 1024;
const int windowHeight = 768;
const int windowDepth = 24;

// Camera
Vector3f rot, eye;

// Application's Timer
struct Timer {
public:
    Timer ()
        : current_time ( 0.0 ), last_time ( 0.0 ) { }

public:
    void update ()
    {
        last_time = current_time;
        current_time = static_cast<double> ( SDL_GetTicks () ) / 1000.0;
    }

    double deltaTime () const
    {
        return ( current_time - last_time );
    }

public:
    double current_time;
    double last_time;

} timer;


// -------------------------------------------------------------------------
// shutdownApp
//
// Application termination.
// -------------------------------------------------------------------------

static void
shutdownApp ( int returnCode )
{
    delete model;
    //666delete object;
    delete bmodel;
    delete font;
    delete shader;
    delete vp_bump;
    delete vp_bump_parallax;
    delete fp_diffuse;
    delete fp_diffuse_specular;
    delete fp_ds_parallax;
    delete texture;
    Texture2DManager::kill ();

    exit ( returnCode );
}


// -------------------------------------------------------------------------
// begin2D
//
// Enter into 2D mode.
// -------------------------------------------------------------------------

static void
begin2D ()
{
    GLint viewport[4];
    glGetIntegerv ( GL_VIEWPORT, viewport );

    glMatrixMode ( GL_PROJECTION );
    glPushMatrix ();

    glLoadIdentity ();
    glOrtho ( 0, viewport[2], 0, viewport[3], -1, 1 );

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
}


// -------------------------------------------------------------------------
// end2D
//
// Return from 2D mode.
// -------------------------------------------------------------------------

static void
end2D ()
{
    glMatrixMode ( GL_PROJECTION );
    glPopMatrix ();
    glMatrixMode ( GL_MODELVIEW );
}


// -------------------------------------------------------------------------
// extractFromQuotes
//
// Extract a string from quotes.
// -------------------------------------------------------------------------

inline const string
extractFromQuotes ( const string &str )
{
    string::size_type start = str.find_first_of ( '\"' ) + 1;
    string::size_type end = str.find_first_of ( '\"', start ) - 2;
    return str.substr ( start, end );
}


// -------------------------------------------------------------------------
// parseLoaderScript
//
// Parse a script file for loading md5mesh and animations.
// -------------------------------------------------------------------------

static void
parseLoaderScript ( const string &filename )
{
    // Open the file to parse
    std::ifstream file ( filename.c_str(), std::ios::in );

    if ( file.fail () ) {
        cerr << "Couldn't open " << filename << endl;
        shutdownApp ( 1 );
    }

    // Get texture manager
    Texture2DManager *texMgr = Texture2DManager::getInstance ();

    while ( !file.eof () ) {
        string token, buffer;
        string meshFile, animFile, textureFile;
        string meshName, animName;

        // Peek next token
        file >> token;

        if ( token == "model" ) {
            std::getline ( file, buffer );
            meshFile = extractFromQuotes ( buffer );

            // Delete previous model and object if existing
            delete model;
            ///666delete object;

            // Load mesh model
            model = new Md5Model ( meshFile );
            //666object = new Md5Object (model);
        } else if ( token == "anim" ) {
            std::getline ( file, buffer );
            animFile = extractFromQuotes ( buffer );

            try {
                // Load animation
                if ( model )
                    model->addAnim ( animFile );
            } catch ( Md5Exception &err ) {
                cerr << "Failed to load animation "
                     << animFile << endl;
                cerr << "Reason: " << err.what ()
                     << " (" << err.which () << ")" << endl;
            }
        } else if ( token == "hide" ) {
            std::getline ( file, buffer );
            meshName = extractFromQuotes ( buffer );

            // Set mesh's render state
            if ( model )
                model->setMeshRenderState ( meshName, Md5Mesh::kHide );
        } else if ( ( token == "decalMap" ) ||
                    ( token == "specularMap" ) ||
                    ( token == "normalMap" ) ||
                    ( token == "heightMap" ) ) {
            // Get the next token and extract the mesh name
            file >> buffer;
            long start = buffer.find_first_of ( '\"' ) + 1;
            long end = buffer.find_first_of ( '\"', start ) - 1;
            meshName = buffer.substr ( start, end );

            // Get the rest of line and extract texture's filename
            std::getline ( file, buffer );
            textureFile = extractFromQuotes ( buffer );

            // If the model has been loaded, setup
            // the texture to the desired mesh
            if ( model ) {
                Texture2D *tex = texMgr->load ( textureFile );
                if ( tex->fail () )
                    cerr << "failed to load " << textureFile << endl;

                if ( token == "decalMap" )
                    model->setMeshDecalMap ( meshName, tex );
                else if ( token == "specularMap" )
                    model->setMeshSpecularMap ( meshName, tex );
                else if ( token == "normalMap" )
                    model->setMeshNormalMap ( meshName, tex );
                else if ( token == "heightMap" )
                    model->setMeshHeightMap ( meshName, tex );
            }
        } else if ( token == "setAnim" ) {
            std::getline ( file, buffer );
            animName = extractFromQuotes ( buffer );

            // Set object's default animation
            //666object->setAnim (animName);
        }
    }

    file.close ();

    //666if (!model || !object)
    //666  throw Md5Exception ("No mesh found!", filename);
}


// -------------------------------------------------------------------------
// announceRenderPath
//
// Print info about a render path.
// -------------------------------------------------------------------------

static void
announceRenderPath ( render_path_e path )
{
    cout << "Render path: ";
    switch ( path ) {
    case R_normal:
        cout << "no bump mapping (fixed pipeline)" << endl;
        break;

    case R_ARBfp_diffuse:
        cout << "bump mapping, diffuse only "
             << "(ARB vp & fp)" << endl;
        break;

    case R_ARBfp_diffuse_specular:
        cout << "bump mapping, diffuse and specular "
             << "(ARB vp & fp)" << endl;
        break;

    case R_ARBfp_ds_parallax:
        cout << "bump mapping with parallax "
             << "(ARB fp & fp)" << endl;
        break;

    case R_shader:
        cout << "bump mapping with parallax "
             << "(GLSL)" << endl;
        break;
    }
}


// -------------------------------------------------------------------------
// initShader
//
// Shader's uniform variables initialization.
// -------------------------------------------------------------------------

static void
initShader ()
{
    if ( NULL == shader )
        return;

    shader->use ();

    if ( GLEW_VERSION_2_0 ) {
        GLuint prog = shader->handle ();

        // Set uniform parameters
        glUniform1i ( glGetUniformLocation ( prog, "decalMap" ), 0 );
        glUniform1i ( glGetUniformLocation ( prog, "glossMap" ), 1 );
        glUniform1i ( glGetUniformLocation ( prog, "normalMap" ), 2 );
        glUniform1i ( glGetUniformLocation ( prog, "heightMap" ), 3 );
        glUniform1i ( glGetUniformLocation ( prog, "parallaxMapping" ), bParallax );

        // Get attribute location
        tangentLoc = glGetAttribLocation ( prog, "tangent" );
    } else {
        GLhandleARB prog = shader->handle ();

        // Set uniform parameters
        glUniform1iARB ( glGetUniformLocationARB ( prog, "decalMap" ), 0 );
        glUniform1iARB ( glGetUniformLocationARB ( prog, "glossMap" ), 1 );
        glUniform1iARB ( glGetUniformLocationARB ( prog, "normalMap" ), 2 );
        glUniform1iARB ( glGetUniformLocationARB ( prog, "heightMap" ), 3 );
        glUniform1iARB ( glGetUniformLocationARB ( prog, "parallaxMapping" ), bParallax );

        // Get attribute location
        tangentLoc = glGetAttribLocationARB ( prog, "tangent" );
    }

    shader->unuse ();

    // Warn ff we fail to get tangent location... We'll can still use
    // the shader, but without tangents
    if ( tangentLoc == -1 )
        cerr << "Warning! No \"tangent\" uniform found in shader!" << endl;
}


// -------------------------------------------------------------------------
// initOpenGL
//
// OpenGL initialization.
// -------------------------------------------------------------------------

static void
initOpenGL ()
{
    glClearColor ( 0.5f, 0.5f, 0.5f, 0.0f );
    glShadeModel ( GL_SMOOTH );
    glCullFace ( GL_BACK );
    glEnable ( GL_DEPTH_TEST );

    glewExperimental = GL_TRUE;
    // Initialize GLEW
    GLenum err = glewInit ();
    if ( GLEW_OK != err ) {
        // Problem: glewInit failed, something is seriously wrong.
        cerr << "Error: " << glewGetErrorString ( err ) << endl;
        shutdownApp ( -1 );
    }

    // Print some infos about user's OpenGL implementation
    cout << "OpenGL Version String: " << glGetString ( GL_VERSION ) << endl;
    cout << "GLU Version String: " << gluGetString ( GLU_VERSION ) << endl;
    cout << "GLEW Version String: " << glewGetString ( GLEW_VERSION ) << endl;

    // Initialize ARB vertex/fragment program support
    initArbProgramHandling ();

    // Initialize GLSL shader support
    initShaderHandling ();

    if ( hasArbVertexProgramSupport () &&
            hasArbFragmentProgramSupport () ) {
        // Load ARB programs
        vp_bump = new ArbVertexProgram ( "../bump.vp" );
        vp_bump_parallax = new ArbVertexProgram ( "../bumpparallax.vp" );

        fp_diffuse = new ArbFragmentProgram ( "../bumpd.fp" );
        fp_diffuse_specular = new ArbFragmentProgram ( "../bumpds.fp" );
        fp_ds_parallax = new ArbFragmentProgram ( "../bumpdsp.fp" );

        // Current ARB programs will be bump mapping with diffuse
        // and specular components
        vp = vp_bump;
        fp = fp_diffuse_specular;
    }

    if ( hasShaderSupport () ) {
        // Load shader
        VertexShader vs ( "../bump.vert" );
        FragmentShader fs ( "../bump.frag" );
        shader = new ShaderProgram ( "bump mapping", vs, fs );

        // Initialize shader's uniforms
        initShader ();
    }

    // Announce avalaible render paths, select the best
    cout << endl << "Avalaible render paths:" << endl;

    cout << " [F3] - No bump mapping (fixed pipeline)" << endl;
    renderPath = R_normal;

    if ( vp_bump && fp_diffuse ) {
        cout << " [F4] - Bump mapping, diffuse only "
             << "(ARB vp & fp)" << endl;
        renderPath = R_ARBfp_diffuse;
    }

    if ( vp_bump && fp_diffuse_specular ) {
        cout << " [F5] - Bump mapping, diffuse and specular "
             << "(ARB vp & fp)" << endl;
        renderPath = R_ARBfp_diffuse_specular;
    }

    if ( vp_bump_parallax && fp_ds_parallax ) {
        cout << " [F6] - Bump mapping with parallax "
             << "(ARB vp & fp)" << endl;
    }

    if ( shader ) {
        cout << " [F7] - Bump mapping with parallax "
             << "(GLSL)" << endl;
        renderPath = R_shader;
    }

    // Announce which path has been chosen by default
    cout << endl;
    announceRenderPath ( renderPath );

    // Initialize true type font
    try {
        font = new TTFont ( "../Vera.ttf", 12, 1 );
    } catch ( std::runtime_error &err ) {
        cerr << "Failed to create truetype font" << endl;
        cerr << "Reason: " << err.what () << endl;
    }

    checkOpenGLErrors ( __FILE__, __LINE__ );
}


// -------------------------------------------------------------------------
// initApplication
//
// Application initialization.
// -------------------------------------------------------------------------

static void
initApplication ( AnimatedModel* otherModel )
{
    // Load model and animations

    try {
        bmodel = otherModel;
        //bmodel->setAnimation("run2");
        string textureFile = "/home/serserar/projects/cpp/ModelConverter/build/null.tga";
        Texture2DManager *texMgr = Texture2DManager::getInstance ();
        texture = texMgr->load ( textureFile );
//         float width=160;
//         float height=120;
//         float width=320;
//         float height=240;
        float width=256;
        float height=256;
        MVector3<float> eye;
        MVector3<float> up ( 0.0f,1.0f,0.0f );
        MVector3<float> center ( 0.0f,0.0f, -1.0f );
        cam = new Camera ( width, height, eye, up, center, 0.5f, 6.0f, 57.82f, 45.0f );
    } catch ( Md5Exception &err ) {
        //cerr << "Failed to load model from " << filename << endl;
        cerr << "Reason: " << err.what () << " ("
             << err.which () << ")" << endl;
        shutdownApp ( -1 );
    }

    // Build animation list
//   Md5Model::AnimMap anims = model->anims ();
//   animations.reserve (anims.size () + 1);
//   animations.push_back (string ()); // bind-pose
//
//   for (Md5Model::AnimMap::iterator itor = anims.begin ();
//        itor != anims.end (); ++itor)
//     animations.push_back (itor->first);

    // Camera initialization
    rot._x = 0.0;
    eye._x = 0.0;
    rot._y = 0.0;
    eye._y = 0.0;
    rot._z = 0.0;
    eye._z = 100.0;
}


// -------------------------------------------------------------------------
// reshape
//
// Reinit OpenGL viewport when resizing window.
// -------------------------------------------------------------------------

static void
reshape ( GLsizei width, GLsizei height )
{
    if ( height == 0 )
        height = 1;

    glViewport ( 0, 0, width, height );

    // Reinit projection matrix
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();
    gluPerspective ( 45.0, width/static_cast<GLfloat> ( height ), 0.1f, 10000.0f );

    // Reinit model-view matrix
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity ();
}


// -------------------------------------------------------------------------
// gameLogic
//
// Perform application logic.
// -------------------------------------------------------------------------

static void
gameLogic ()
{
    // Calculate frames per seconds
    static double current_time = 0;
    static double last_time = 0;
    static int n = 0;

    n++;
    current_time = timer.current_time;
    double dt = timer.current_time -  timer.last_time;
    //Entity* player_entity = EntityManager::GetInstance()->GetEntity(12);
    //player_entity->GetStatus();
    if ( current_time -last_time >= 1.0 ) {
        fps = n;
        n = 0;
        last_time = current_time;
    }
    bmodel->OnUpdate ( dt );
}


// -------------------------------------------------------------------------
// setupLight
//
// Setup light position and enable light0.
// -------------------------------------------------------------------------

void
setupLight ( GLfloat x, GLfloat y, GLfloat z )
{
    GLfloat lightPos[4];
    lightPos[0] = x;
    lightPos[1] = y;
    lightPos[2] = z;
    lightPos[3] = 1.0f;

    glDisable ( GL_LIGHTING );
    glDisable ( GL_LIGHT0 );

    if ( bLight ) {
        glPushMatrix ();
        glLoadIdentity ();
        glLightfv ( GL_LIGHT0, GL_POSITION, lightPos );
        glPopMatrix ();

        glEnable ( GL_LIGHTING );
        glEnable ( GL_LIGHT0 );
    }
}


// -------------------------------------------------------------------------
// drawObb
//
// Draw an Oriented Bouding Box.
// -------------------------------------------------------------------------

static void
drawObb ( const Matrix4x4f &modelView, const BBox &obb )
{
    Vector3f corners[8];

    corners[0] = Vector3f ( obb.boundMin.GetX(), obb.boundMin.GetY(), obb.boundMax.GetZ() );
    corners[1] = Vector3f ( obb.boundMax.GetX(), obb.boundMin.GetY(), obb.boundMax.GetZ() );
    corners[2] = Vector3f ( obb.boundMax.GetX(), obb.boundMin.GetY(), obb.boundMin.GetZ() );
    corners[3] = Vector3f ( obb.boundMin.GetX(), obb.boundMin.GetY(), obb.boundMin.GetZ() );
    corners[4] = Vector3f ( obb.boundMin.GetX(), obb.boundMax.GetY(), obb.boundMax.GetZ() );
    corners[5] = Vector3f ( obb.boundMax.GetX(), obb.boundMax.GetY(), obb.boundMax.GetZ() );
    corners[6] = Vector3f ( obb.boundMax.GetX(), obb.boundMax.GetY(), obb.boundMin.GetZ() );
    corners[7] = Vector3f ( obb.boundMin.GetX(), obb.boundMax.GetY(), obb.boundMin.GetZ() );
    // Setup world model view matrix
    glLoadIdentity ();
    glMultMatrixf ( modelView._m );

    glPushAttrib ( GL_ENABLE_BIT );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_LIGHTING );

    GLuint indices[24] = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    glColor3f ( 1.0, 0.0, 0.0 );

    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, corners );
    glDrawElements ( GL_LINES, 24, GL_UNSIGNED_INT, indices );
    glDisableClientState ( GL_VERTEX_ARRAY );

    // GL_ENABLE_BIT
    glPopAttrib();
}


// -------------------------------------------------------------------------
// drawAxes
//
// Draw the X, Y and Z axes at the center of world.
// -------------------------------------------------------------------------

static void
drawAxes ( const Matrix4x4f &modelView )
{
    // Setup world model view matrix
    glLoadIdentity ();
    glMultMatrixf ( modelView._m );

    // Draw the three axes
    glBegin ( GL_LINES );
    // X-axis in red
    glColor3f ( 1.0f, 0.0f, 0.0f );
    glVertex3fv ( kZeroVectorf._v );
    glVertex3fv ( kZeroVectorf + Vector3f ( 10.0f, 0.0f, 0.0 ) );

    // Y-axis in green
    glColor3f ( 0.0f, 1.0f, 0.0f );
    glVertex3fv ( kZeroVectorf._v );
    glVertex3fv ( kZeroVectorf + Vector3f ( 0.0f, 10.0f, 0.0 ) );

    // Z-axis in blue
    glColor3f ( 0.0f, 0.0f, 1.0f );
    glVertex3fv ( kZeroVectorf._v );
    glVertex3fv ( kZeroVectorf + Vector3f ( 0.0f, 0.0f, 10.0 ) );
    glEnd ();
}

static void drawSkeleton ( const Matrix4x4f &modelView, Skeleton& skeleton )
{

    // Setup world model view matrix
    glLoadIdentity ();
    glMultMatrixf ( modelView._m );
    // Draw each joint
    glPointSize ( 5.0f );
    glColor3f ( 1.0f, 0.0f, 0.0f );
    glBegin ( GL_POINTS );
    for ( auto joint : skeleton.joints )
        glVertex3f ( joint->GetPosition()->GetX(), joint->GetPosition()->GetY(), joint->GetPosition()->GetZ() );
    glEnd ();
    glPointSize ( 1.0f );

    // Draw each bone
    glColor3f ( 0.0f, 1.0f, 0.0f );
    glBegin ( GL_LINES );
    for ( auto joint : skeleton.joints ) {
        if ( joint->GetParent() != -1 ) {
            glVertex3f ( skeleton.joints[joint->GetParent()]->GetPosition()->GetX(),
                         skeleton.joints[joint->GetParent()]->GetPosition()->GetY(),
                         skeleton.joints[joint->GetParent()]->GetPosition()->GetZ() );
            glVertex3f ( joint->GetPosition()->GetX(),
                         joint->GetPosition()->GetY(),
                         joint->GetPosition()->GetZ() );
        }
    }
    glEnd ();
}

static void drawRay ( const Matrix4x4f &modelView, vector<Ray>& rayList )
{
    if ( rayList.size() > 0 ) {
        // Setup world model view matrix
        glLoadIdentity ();
        glMultMatrixf ( modelView._m );
        // Draw each bone
        glColor3f ( 0.0f, 1.0f, 0.0f );
        glPointSize ( 1.0f );
        glBegin ( GL_LINES );
        for ( auto ray : rayList ) {
            glVertex3f ( ray.GetOrigin().GetX(),
                         ray.GetOrigin().GetY(),
                         ray.GetOrigin().GetZ() );
            glVertex3f ( ray.GetOrigin().GetX() + ray.GetDirection().GetX() *256,
                         ray.GetOrigin().GetY() + ray.GetDirection().GetY() *256,
                         ray.GetOrigin().GetZ() + ray.GetDirection().GetZ() *256 );
        }
        glEnd ();
        glPointSize ( 1.0f );
    }
}

static Mesh* buildCubeMesh()
{

    //  vertices
    std::vector<GLfloat> vertices {
        -5,0,-5,
        5,0,-5,
        -5,10,-5,
        -5,0,5,
        5,10,-5,
        5,0,5,
        -5,10,5,
        5,10,5
    };
//  Color buffer
    std::vector<GLubyte> colors {
        0,0,0,255,
        255,0,0,255,
        0,255,0,255,
        0,0,255,255,
        255,255,0,255,
        255,0,255,255,
        0,255,255,255,
        255,255,255,255
    };
//  Vertex index buffer
    std::vector<GLuint> indices {
        0,1,4, 4,2,0,
        0,2,6, 6,3,0,
        0,3,5, 5,1,0,
        1,4,7, 7,5,1,
        5,7,6, 6,3,5,
        2,6,7, 7,4,2
    };
    Mesh* mesh = new Mesh();
    mesh->vertexCoords.insert ( mesh->vertexCoords.end(), vertices.begin(), vertices.end() );
    mesh->colorCoords.insert ( mesh->colorCoords.end(), colors.begin(), colors.end() );
    mesh->indexBuffer.insert ( mesh->indexBuffer.end(), indices.begin(), indices.end() );
    int index = 0;
    for ( int i = 0; i < indices.size(); i++ ) {
        if ( i % 3 == 0 ) {
            mesh->indexModeBuffer.push_back ( Mesh::indexMode::Triangles );
            mesh->indexBuffer.push_back ( index );
            index++;
        }
        mesh->indexSections[0].push_back ( indices.at ( i ) );
    }
    mesh->indexLenghts.push_back ( indices.size() );
    return mesh;
}
static void drawCube()
{

    //  vertices
    std::vector<GLfloat> vertices {
        -5,0,-5,
        5,0,-5,
        -5,10,-5,
        -5,0,5,
        5,10,-5,
        5,0,5,
        -5,10,5,
        5,10,5
    };
//  Color buffer
    std::vector<GLubyte> colors {
        0,0,0,255,
        255,0,0,255,
        0,255,0,255,
        0,0,255,255,
        255,255,0,255,
        255,0,255,255,
        0,255,255,255,
        255,255,255,255
    };
//  Vertex index buffer
    std::vector<GLuint> indices {
        0,1,4, 4,2,0,
        0,2,6, 6,3,0,
        0,3,5, 5,1,0,
        1,4,7, 7,5,1,
        5,7,6, 6,3,5,
        2,6,7, 7,4,2
    };
    glEnableClientState ( GL_COLOR_ARRAY );
    glEnableClientState ( GL_VERTEX_ARRAY );

    glColorPointer ( 4, GL_UNSIGNED_BYTE, 0, &colors.front() );
    glVertexPointer ( 3, GL_FLOAT, 0, &vertices.front() );
    glDrawElements ( GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices.front() );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_COLOR_ARRAY );

}

static GLenum getPrimitive ( Mesh::indexMode imode )
{
    GLenum mode = GL_TRIANGLES;
    switch ( imode ) {
    case Mesh::indexMode::Triangles:
        mode = GL_TRIANGLES;
        break;
    case Mesh::indexMode::TriangleFan:
        mode = GL_TRIANGLE_FAN;
        break;
    case Mesh::indexMode::TriangleStrip:
        mode = GL_TRIANGLE_STRIP;
        break;
    case Mesh::indexMode::Quads:
        mode = GL_QUADS;
        break;
    case Mesh::indexMode::QuadStrip:
        mode = GL_QUAD_STRIP;
        break;
    case Mesh::indexMode::Lines:
        mode = GL_LINES;
        break;
    case Mesh::indexMode::LineStrip:
        mode = GL_LINE_STRIP;
        break;
    case Mesh::indexMode::LineLoop:
        mode = GL_LINE_LOOP;
        break;
    case Mesh::indexMode::Points:
        mode = GL_POINT;
        break;
    }
    return mode;
}

static void CopyDepthBuffer ( GLuint texId, int x, int y, int imageWidth, int imageHeight )
{
    glBindTexture ( GL_TEXTURE_2D, texId );

    glReadBuffer ( GL_BACK ); // Ensure we are reading from the back buffer.
    glCopyTexImage2D ( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, x, y, imageWidth, imageHeight, 0 );
}

static void renderMesh ( const Matrix4x4f &modelView, Mesh& mesh )
{
    //  Vertex index buffer
    std::vector<GLuint> indices {
        0,1,4, 4,2,0,
        0,2,6, 6,3,0,
        0,3,5, 5,1,0,
        1,4,7, 7,5,1,
        5,7,6, 6,3,5,
        2,6,7, 7,4,2
    };
    std::vector<GLfloat> vertices {
        -5,0,-5,
        5,0,-5,
        -5,10,-5,
        -5,0,5,
        5,10,-5,
        5,0,5,
        -5,10,5,
        5,10,5
    };
    // Ensable shader/program's stuff
    //preRenderVertexArrays ();
    // Setup world model view matrix
    glLoadIdentity ();
    glMultMatrixf ( modelView._m );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glEnableClientState ( GL_NORMAL_ARRAY );
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );

    // Upload mesh data to OpenGL
    glVertexPointer ( 3, GL_FLOAT, 0, &mesh.vertexCoords.front() );
    //glVertexPointer (3, GL_FLOAT, 0, &vertices.front());
    glNormalPointer ( GL_FLOAT, 0, &mesh.normalCoords.front() );
    glTexCoordPointer ( 2, GL_FLOAT, 0, &mesh.textureCoords.at ( 0 ).front() );

    // Bind to mesh's textures
    //setupTexture (_heightMap, GL_TEXTURE3);
    //setupTexture (_normalMap, GL_TEXTURE2);
    //setupTexture (_specMap, GL_TEXTURE1);
    //setupTexture (_decal, GL_TEXTURE0);
    texture->bind ( GL_TEXTURE0 );
    // Draw the mesh
    mesh.UpdatePrimitiveCounts();

    for ( int section = 0; section < mesh.GetSectionCount(); section++ ) {

        Mesh::indexMode indexMode = mesh.indexModeBuffer.at ( section );

        glDrawElements ( getPrimitive ( indexMode ), mesh.indexSections[section].size(),GL_UNSIGNED_INT, &mesh.indexSections[section].front() );

    }

// //           glDrawElements (getPrimitive(Mesh::indexMode::Points), mesh.indexSections[section].size(),GL_UNSIGNED_INT, &mesh.indexSections[section].front());
// //           vector<int> indexVec = mesh.indexSections[section];
// //           glBegin(getPrimitive(indexMode));//start drawing a line loop
// //           for(auto index : indexVec){
// //             glVertex3f(mesh.vertexCoords[index*3],mesh.vertexCoords[index*3+1],mesh.vertexCoords[index*3+2]);
// //           }
// //           glEnd();//end drawing of line loop

//     for ( auto triangle : mesh.triangleList ) {
//         glBegin(GL_TRIANGLES);
//         glVertex3f(triangle.v1.GetX(), triangle.v1.GetY(), triangle.v1.GetZ());
//         glVertex3f(triangle.v2.GetX(), triangle.v2.GetY(), triangle.v2.GetZ());
//         glVertex3f(triangle.v3.GetX(), triangle.v3.GetY(), triangle.v3.GetZ());
//         glEnd();//end drawing of line loop
//     }
    glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
    glDisableClientState ( GL_VERTEX_ARRAY );
    if ( bBounds )
        drawObb ( modelView, mesh.bbox );
    // Disable shader/program's stuff
    //postRenderVertexArrays ();
}

// -------------------------------------------------------------------------
// draw3D
//
// Render the 3D part of the scene.
// -------------------------------------------------------------------------

static void
draw3D ()
{
    // Clear the window
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity ();

    // Camera rotation
    Matrix4x4f camera;

#if 0
    camera.identity ();

    glTranslated ( -eye._x, -eye._y, -eye._z );
    glRotated ( rot._x, 1.0f, 0.0f, 0.0f );
    glRotated ( rot._y, 0.0f, 1.0f, 0.0f );
    glRotated ( rot._z, 0.0f, 0.0f, 1.0f );
#else
    camera.fromEulerAngles ( degToRad ( rot._x ),
                             degToRad ( rot._y ),
                             degToRad ( rot._z ) );
    camera.setTranslation ( -eye );
    MVector3<float> camEye;
    camEye.SetX ( eye._x );
    camEye.SetY ( eye._y );
    camEye.SetZ ( eye._z );
    cam->SetEye ( camEye );
#endif

//   Matrix4x4f axismation
//     = RotationMatrix (kXaxis, -kPiOver2)
//     * RotationMatrix (kZaxis, kPiOver2);

//  Matrix4x4f axisRotation = RotationMatrix (kXaxis, -kPiOver2);

    //Matrix4x4f final = camera * axisRotation;
    Matrix4x4f final = camera;
    //glMultMatrixf (final._m);

    // Setup scene lighting
    setupLight ( 0.0f, 20.0f, 100.0f );

    // Enable/disable texture mapping (fixed pipeline)
    if ( bTextured )
        glEnable ( GL_TEXTURE_2D );
    else
        glDisable ( GL_TEXTURE_2D );

//   glFrontFace( GL_CCW );
    glCullFace ( GL_FRONT );
    // Enable/disable backface culling
//   if (bCullFace)
//     glEnable (GL_CULL_FACE);
//   else
//     glDisable (GL_CULL_FACE);

    // Setup polygon mode and shade model
    glPolygonMode ( GL_FRONT_AND_BACK, bWireframe ? GL_LINE : GL_FILL );
    glShadeModel ( bSmooth ? GL_SMOOTH : GL_FLAT );

    // Draw object
    //666object->setModelViewMatrix (final);
    //666object->setRenderFlags (renderFlags);
    //666object->animate (bAnimate ? timer.deltaTime () : 0.0f);
    //666object->computeBoundingBox ();
    //666object->prepare (false);
    //666object->render ();
    auto meshItBegin = bmodel->GetBeginVisibleMeshIterator();
    auto meshItEnd = bmodel->GetEndVisibleMeshIterator();
    while ( meshItBegin != meshItEnd ) {
        //mesh->applyPose();
        renderMesh ( final, **meshItBegin );
        meshItBegin++;
    }
    drawSkeleton ( final,bmodel->GetCurrentPose()->skeleton );
    if ( bBounds )
        drawObb ( final, bmodel->GetBoundingBox() );
    //drawRay(final, rayList);
    //666drawObb (object->boundingBox ());
    if ( bDrawVoxels ) {
        VoxelizerTool voxelizer;
        std::vector<BBox> voxelList;
        BBox size;
        int meshIndex = 0;
        auto meshItBegin = bmodel->GetBeginVisibleMeshIterator();
        auto meshItEnd = bmodel->GetEndVisibleMeshIterator();
        while ( meshItBegin != meshItEnd ) {
            voxelizer.VoxelixeExt ( **meshItBegin, meshIndex, 0.25f, size, true, voxelList );
            meshIndex++;
            meshItBegin++;
        }
        for ( auto voxel: voxelList ) {
            drawObb ( final,voxel );
        }
        bDrawVoxels=!bDrawVoxels;
    }
    glDisable ( GL_LIGHTING );
    glDisable ( GL_TEXTURE_2D );

    drawAxes ( final );
}



// -------------------------------------------------------------------------
// draw2D
//
// Render the 2D part of the scene.
// -------------------------------------------------------------------------

static void
draw2D ()
{
    if ( !font )
        return;

    begin2D ();

    // Reset texture matrix
    glActiveTexture ( GL_TEXTURE0 );
    glMatrixMode ( GL_TEXTURE );
    glLoadIdentity ();
    glMatrixMode ( GL_MODELVIEW );

    glPushAttrib ( GL_ENABLE_BIT | GL_POLYGON_BIT );
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_LIGHTING );
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

    // White text
    glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );

    // Print frame rate int the bottom-left corner
    font->printText ( 10, 10, "%i fps", fps );

    // Print current animation
    //666font->printText (10, 10 + font->getLineSkip (),
    //666object->currAnimName ().c_str ());

    glPopAttrib ();

    end2D ();
}

void ToggleFullscreen ( SDL_Window* Window )
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags ( Window ) & FullscreenFlag;
    SDL_SetWindowFullscreen ( Window, IsFullscreen ? 0 : FullscreenFlag );
    SDL_ShowCursor ( IsFullscreen );
}

void snapshot ( Camera& cam, AnimatedModel& model )
{
    rayList.clear();
    vector<Image*> imageList;
    ImageUtils::Snapshot ( cam, model, rayList, 0, imageList);
    PPMReader writer;
    int index = 0;
    for(Image* img : imageList) {
        std::stringstream ss;
        ss << "output" << index << ".ppm";
        writer.writePGM5 ( ss.str(),*img );
        index++;
        delete img;
    }

}
// -------------------------------------------------------------------------
// display
//
// Render the main scene to the screen.
// -------------------------------------------------------------------------

static void
gameCycle ()
{
    gameLogic ();

    draw3D ();

    draw2D ();

    SDL_GL_SwapWindow ( surface );
}


// -------------------------------------------------------------------------
// handleKeyPress
//
// SDL Keyboard handling.
// -------------------------------------------------------------------------

static void
handleKeyPress ( SDL_Keysym *keysym )
{
    switch ( keysym->sym ) {
    case SDLK_RIGHT:
    case SDLK_LEFT: {
        // Find the current animation in the list
        //666vector<string>::iterator itor
        //666  = find (animations.begin (), animations.end (),
        //666	  object->currAnimName ());

        // Peek next or previous animation name
        if ( keysym->sym == SDLK_RIGHT ) {
            //666++itor;
        } else {
            //666if (itor == animations.begin ())
            //666  itor = animations.end ();

            //666--itor;
        }

        //666if (itor == animations.end ())
        //666  itor = animations.begin ();

        // Set the new animation to play
        //666object->setAnim (*itor);
        break;
    }

    case SDLK_SPACE:
        bAnimate = !bAnimate;
        break;

    case SDLK_b:
        bBounds = !bBounds;
        break;

    case SDLK_c:
        bCullFace = !bCullFace;
        break;
    case SDLK_e:
        snapshot ( *cam, *bmodel );
        break;
    case SDLK_j:
        renderFlags ^= Md5Object::kDrawJointLabels;
        break;

    case SDLK_k:
        renderFlags ^= Md5Object::kDrawSkeleton;
        break;

    case SDLK_l:
        bLight = !bLight;
        break;

    case SDLK_n:
        bDrawNormals = !bDrawNormals;
        break;

    case SDLK_p: {
        bParallax = !bParallax;
        if ( bParallax && shader )
            cout << "Parallax Mapping: on" << endl;
        else
            cout << "Parallax Mapping: off" << endl;

        if ( shader == NULL )
            break;

        shader->use ();

        if ( GLEW_VERSION_2_0 )
            glUniform1i ( glGetUniformLocation ( shader->handle (),
                                                 "parallaxMapping" ), bParallax );
        else
            glUniform1iARB ( glGetUniformLocationARB ( shader->handle (),
                             "parallaxMapping" ), bParallax );

        shader->unuse ();
        break;
    }

    case SDLK_s:
        bSmooth = !bSmooth;
        break;

    case SDLK_t:
        bTextured = !bTextured;
        break;

    case SDLK_v:
        bDrawVoxels = !bDrawVoxels;
        break;

    case SDLK_w:
        bWireframe = !bWireframe;
        break;

    case SDLK_F1:
        ToggleFullscreen ( surface );
        break;

    case SDLK_F3: // R_normal
        renderPath = R_normal;
        announceRenderPath ( renderPath );
        break;

    case SDLK_F4: // R_ARBfp_diffuse
        if ( vp_bump && fp_diffuse ) {
            renderPath = R_ARBfp_diffuse;
            vp = vp_bump;
            fp = fp_diffuse;
        }
        announceRenderPath ( renderPath );
        break;

    case SDLK_F5: // R_ARBfp_diffuse_specular
        if ( vp_bump && fp_diffuse_specular ) {
            renderPath = R_ARBfp_diffuse_specular;
            vp = vp_bump;
            fp = fp_diffuse_specular;
        }
        announceRenderPath ( renderPath );
        break;

    case SDLK_F6: // R_ARBfp_ds_parallax
        if ( vp_bump_parallax && fp_ds_parallax ) {
            renderPath = R_ARBfp_ds_parallax;
            vp = vp_bump_parallax;
            fp = fp_ds_parallax;
        }
        announceRenderPath ( renderPath );
        break;

    case SDLK_F7: // R_shader
        if ( shader )
            renderPath = R_shader;
        announceRenderPath ( renderPath );
        break;

    case SDLK_ESCAPE:
        shutdownApp ( 0 );
        break;

    default:
        break;
    }
}


// -------------------------------------------------------------------------
// MouseMove
//
// SDL Mouse Input Control.
// -------------------------------------------------------------------------

static void
mouseMove ( int x, int y )
{
    static int x_pos = 0;
    static int y_pos = 0;

    SDL_Keymod km = SDL_GetModState ();

    // Right button
    if ( SDL_GetMouseState ( NULL, NULL ) & SDL_BUTTON_RMASK ) {
        // /*Zoom*/
        eye._z += ( x - x_pos ) * 0.1f;
    }
    // Left button
    else if ( SDL_GetMouseState ( NULL, NULL ) & SDL_BUTTON_LMASK ) {
        if ( ( km & KMOD_RSHIFT ) || ( km & KMOD_LSHIFT ) ) {
            // Translation
            eye._x -= ( x - x_pos ) * 0.1f;
            eye._y += ( y - y_pos ) * 0.1f;
        } else {
            // Rotation
            rot._x += ( y - y_pos );
            rot._y += ( x - x_pos );
        }
    }

    x_pos = x;
    y_pos = y;
}


// -------------------------------------------------------------------------
// main
//
// Application main entry point.
// -------------------------------------------------------------------------

int runViewer ( AnimatedModel* model )
{
    cout << "Built release " << __DATE__ << " at " << __TIME__ << endl;

    int videoFlags;
    bool isActive = true;

    // Initialize SDL
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        cerr << "Video initialization failed: "
             << SDL_GetError () << endl;
        shutdownApp ( -1 );
    }

    atexit ( SDL_Quit );


    // Initialize flags to pass to SDL_SetVideoMode
    videoFlags  = SDL_WINDOW_OPENGL;             // Uses OpenGL
    videoFlags |= SDL_GL_DOUBLEBUFFER;    // Uses double buffering
    videoFlags |= SDL_WINDOW_RESIZABLE;          // App. window is resizable

    // Check if we can allocate memory in hardware for the window
    videoFlags |= SDL_SWSURFACE;
    videoFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    // Check if hardware blit is possible
    //  videoFlags |= SDL_HWACCEL;

    // Set double buffering for OpenGL
    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );

    // Initialize video mode
    surface = SDL_CreateWindow ( "MD5 Viewer", 0, 0, windowWidth, windowHeight, videoFlags );
    if ( !surface ) {
        cerr << "Video mode set failed: " << SDL_GetError () << endl;
        shutdownApp ( -1 );
    }
    SDL_SetWindowFullscreen ( surface, 0 );
    SDL_GL_SetAttribute ( SDL_GL_CONTEXT_MAJOR_VERSION , 3 ) ;
    SDL_GL_SetAttribute ( SDL_GL_CONTEXT_MINOR_VERSION , 0 ) ;

    SDL_GLContext gi_glcontext = SDL_GL_CreateContext ( surface );

    if ( gi_glcontext == NULL ) {
        std::cerr << "SDL Error(something about glcontext): " << SDL_GetError() << std::endl;
    }

    std::cout << glGetString ( GL_VERSION ) << std::endl;

    if ( SDL_GL_MakeCurrent ( surface, gi_glcontext ) < 0 ) {
        std::cerr << "SDL Error(something about glcontext): " << SDL_GetError() << std::endl;
    }
    // Initialize OpenGL
    initOpenGL ();

    // Initialize application
    initApplication ( model );

    // Resize OpenGL window
    reshape ( windowWidth, windowHeight );

    // Loop until the end
    while ( 1 ) {
        SDL_Event event;

        // Parse SDL event
        while ( SDL_PollEvent ( &event ) ) {
            switch ( event.type ) {
            case SDL_WINDOWEVENT_LEAVE:
                // Don't draw scene if the window has been minimized
// 	      isActive = !((event.active.gain == 0) &&
// 			   (event.active.state & SDL_APPACTIVE));
                break;

            case SDL_WINDOWEVENT_RESIZED:
                // Resize Window
                SDL_SetWindowSize ( surface,event.window.data1,
                                    event.window.data2 );

                reshape ( event.window.data1, event.window.data2 );
                initOpenGL ();
                break;

            case SDL_KEYDOWN:
                handleKeyPress ( &event.key.keysym );
                break;

            case SDL_MOUSEMOTION:
                mouseMove ( event.button.x, event.button.y );
                break;

            case SDL_QUIT:
                shutdownApp ( 0 );
                break;

            default:
                break;
            }
        }

        // Update the timer
        timer.update ();

        // Draw scene if window is active
        if ( isActive )
            gameCycle ();
    }

    // We should never go here
    return 0;
}


