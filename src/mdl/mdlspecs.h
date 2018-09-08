#ifndef MDLSPECS_H
#define MDLSPECS_H
typedef struct {
    float x;
    float y;
    float z;

} vec3_s;

typedef struct {
    unsigned int id;
    unsigned int version;
    char name[64];
    unsigned int length;
    vec3_s eyeposition; // ideal eye position
    vec3_s min; // ideal movement hull size
    vec3_s max;
    vec3_s bbmin; // clipping bounding box
    vec3_s bbmax;
    unsigned int flags;
    unsigned int numbones; // bones
    unsigned int boneindex;
    unsigned int numbonecontrollers; // bone controllers
    unsigned int bonecontrollerindex;
    unsigned int numhitboxes; // complex bounding boxes
    unsigned int hitboxindex;
    unsigned int numseq; // animation sequences
    unsigned int seqindex;
    unsigned int numseqgroups; // demand loaded sequences
    unsigned int seqgroupindex;
    unsigned int numtextures; // raw textures
    unsigned int textureindex;
    unsigned int texturedataindex;
    unsigned int numskinref; // replaceable textures
    unsigned int numskinfamilies;
    unsigned int skinindex;
    unsigned int numbodyparts;
    unsigned int bodypartindex;
    unsigned int numattachments; // queryable attachable points
    unsigned int attachmentindex;
    int soundtable;
    int soundindex;
    int soundgroups;
    int soundgroupindex;
    int numtransitions; // animation node to animation node transition graph
    int transitionindex;

} mdl_header;

typedef struct {
    char name[32]; // bone name for symbolic links
    int parent; // parent bone
    int flags; // ??
    int bonecontroller[6]; // bone controller index, -1 == none
    float value[6]; // default DoF values
    float scale[6]; // scale for delta DoF values
} bone_s;

typedef struct {
    int bone; // -1 == 0
    int type; // X, Y, Z, XR, YR, ZR, M
    float start;
    float end;
    int rest; // byte index value at rest
    int index; // 0-3 user set controller, 4 mouth
} bonecontroller_s;

typedef struct {
    int bone;
    int group; // intersection group
    vec3_s bbmin; // bounding box
    vec3_s bbmax;
} hbbox_s;

typedef struct {
    int id;
    int version;
    char name[64];
    int length;
} seqheader_s;

// sequence descriptions

typedef struct {
    char label[32]; // sequence label
    float fps; // frames per second
    int flags; // looping/non-looping flags
    int activity;
    int actweight;
    int numevents;
    int eventindex;
    int numframes; // number of frames per sequence
    unsigned int numpivots; // number of foot pivots
    unsigned int pivotindex;
    int motiontype;
    int motionbone;
    vec3_s linearmovement;
    int automoveposindex;
    int automoveangleindex;
    vec3_s bbmin; // per sequence bounding box
    vec3_s bbmax;
    int numblends;
    int animindex; // SHalflifeAnimOffset pointer relative to start of sequence group data
    // [blend][bone][X, Y, Z, XR, YR, ZR]
    int blendtype[2]; // X, Y, Z, XR, YR, ZR
    float blendstart[2]; // starting value
    float blendend[2]; // ending value
    int blendparent;
    int seqgroup; // sequence group for demand loading
    int entrynode; // transition node at entry
    int exitnode; // transition node at exit
    int nodeflags; // transition rules
    int nextseq; // auto advancing sequences
} sequence_s;

// demand loaded sequence groups

typedef struct {
    char label[32]; // textual name
    char name[64]; // file name
    int cache; // cache index pointer
    int data; // hack for group 0
} sequencegroup_s;

typedef union 
{
	struct {
		unsigned char	valid;
		unsigned char	total;
	} num;
	short		value;
} animvalue_s;

typedef struct {
    char name[64];
    int flags;
    int width;
    int height;
    int index; //SkinIndex
} texture_s;

// meshes

typedef struct {
    unsigned int numtris;
    unsigned int triindex;
    unsigned int skinref;
    unsigned int numnorms; // per mesh normals
    unsigned int normindex; // normal vec3_hl

} mesh_s;

// studio models

typedef struct {
    char name[64];
    int type;
    float boundingradius;
    unsigned int nummesh;
    unsigned int meshindex;
    unsigned int numverts; // number of unique vertices
    unsigned int vertinfoindex; // vertex bone info
    unsigned int vertindex; // vertex vec3_hl
    unsigned int numnorms; // number of unique surface normals
    unsigned int norminfoindex; // normal bone info
    unsigned int normindex; // normal vec3_hl
    unsigned int numgroups; // deformation groups
    unsigned int groupindex;

} model_s;

// body part index

typedef struct {
    char name[64];
    unsigned int nummodels;
    unsigned int base;
    unsigned int modelindex; // index into models array

} bodypart_s;

 struct vertexinfo_s{
    int triangletype; //triangle type 0 : Strip, 1: Fan.
    int triangleTypeIndex; //Triangle Type index
    int triangleIndex; //triangle index
    int bone; //bone id wich coordinate system is used to specify the vertex position and normal orientation
    /**
     * Coordenadas del vértice en el sistema del hueso vertexBone.
     */
    vec3_s vertex;
    /**
     * Coordenadas de la normal del vértice en el sistema del hueso
     * normalBone.
     */
    vec3_s normal;
    float ucoord;//texture u coordinate
    /**
     * Coordenada u de la textura sin normalizar. La normalización se
     * realiza dividiendo este valor por el ancho en pixeles de la
     * textura. Se almacena este valor para utilizarlo en las
     * comparaciones. El campo uCoord se calcula a partir de uCoordS
     * y el ancho de la textura, por lo que al comparar y ordenar dos
     * variables de este tipo sólo se utiliza el campo uCoordS y no
     * uCoord.
     */
    float ucoords;
    float vcoord;//texture v coord
    /**
     * Coordenada v de la textura sin normalizar. La normalización se
     * realiza dividiendo este valor por el alto en pixeles de la
     * textura. Se almacena este valor para utilizarlo en las
     * comparaciones. El campo vCoord se calcula a partir de vCoordS
     * y el alto de la textura, por lo que al comparar y ordenar dos
     * variables de este tipo sólo se utiliza el campo vCoordS y no
     * vCoord.
     */
    float vcoords;
    int index;
} ;

#endif // MDLSPECS_H
