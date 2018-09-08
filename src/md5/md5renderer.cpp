/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "md5renderer.h"

md5model* md5renderer::model = 0;

md5renderer::md5renderer(md5model* model)
{
     md5renderer::model = model;
}


void md5renderer::initialize(int argc, char* argv[])
{
    initGL(argc, argv);
}


void md5renderer::reshape (int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    //glMatrixMode (GL_PROJECTION);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluPerspective (45.0, w/(GLdouble)h, 0.1, 1000.0);
}

void md5renderer::keyboard (unsigned char key, int x, int y)
{
    /* Escape */
    if (key == 27)
        exit (0);
}

void md5renderer::setModel(md5model* model)
{
   md5renderer::model = model;
}

md5model* md5renderer::getModel()
{
    return model;
}

void md5renderer::drawModel()
{
    for (int i = 0; i < md5renderer::model->getMeshes().size(); i ++) {
        vector<MVector3<float>*> vertexList =  md5renderer::model->getVertexFinalPosition(i);
        int* vertexIndex = md5renderer::model->getVertexIndex(i);
        float* vertexArray = new float[vertexList.size()*3];
        int numtris = md5renderer::model->getMeshes().at(i)->numtris;
        for (int j = 0; j < vertexList.size(); j ++) {
            vertexArray[j] = (float)vertexList.at(j)->getX();
            vertexArray[j] = (float)vertexList.at(j)->getY();
            vertexArray[j] = (float)vertexList.at(j)->getZ();
        }
        drawVertexArrayf(vertexArray, vertexIndex, numtris);
    }
}

void md5renderer::drawSkeleton(md5joint* skeleton, int numjoints)
{
  int i;

  /* Draw each joint */
  //glPointSize (5.0f);
  glColor3f (1.0f, 0.0f, 0.0f);
  glBegin (GL_POINTS);
    for (i = 0; i < numjoints; ++i)
      glVertex3fv (skeleton[i].getPosition()->getArray());
  glEnd ();
  glPointSize (1.0f);

  /* Draw each bone */
  glColor3f (0.0f, 1.0f, 0.0f);
  glBegin (GL_LINES);
    for (i = 0; i < numjoints; ++i)
      {
	if (skeleton[i].getParent() != -1)
	  {
	    glVertex3fv (skeleton[skeleton[i].getParent()].getPosition()->getArray());
	    glVertex3fv (skeleton[i].getPosition()->getArray());
	  }
      }
  glEnd();
}


void md5renderer::drawVertexArrayf(float*vertexArray, int *vertexIndices, int ntriangles)
{
    glVertexPointer (3, GL_FLOAT, 0, vertexArray);

    glDrawElements (GL_TRIANGLES, ntriangles * 3,
                    GL_UNSIGNED_INT, vertexIndices);
}

void md5renderer::display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//     glBegin(GL_POLYGON);
//     glVertex3f(0.25, 0.25, 0.0);
//     glVertex3f(0.75, 0.25, 0.0);
//     glVertex3f(0.75, 0.75, 0.0);
//     glVertex3f(0.25, 0.75, 0.0);
//     glEnd();
    glColor3f (1.0f, 1.0f, 1.0f);
    glEnableClientState (GL_VERTEX_ARRAY);
    //drawModel();
    glDisableClientState (GL_VERTEX_ARRAY);
    glutSwapBuffers ();
    glutPostRedisplay ();
    glFlush();
    glutPostRedisplay ();
}

void md5renderer::cleanup() {}
void md5renderer::init(void)
{
    /* select clearing (background) color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initialize viewing values */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void md5renderer::initGL (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "usage: %s <filename.md5mesh> "
                  << "[<filename.md5anim>]\n" << argv[0];
    }
    glutInit (&argc, argv);
//     glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//     glutInitWindowSize (640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("MD5 Model");

    //atexit (cleanup);


    glutReshapeFunc (reshape);
    glutDisplayFunc (display);
    glutKeyboardFunc (keyboard);
    init();
    glutMainLoop();
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(250, 250);
//     glutInitWindowPosition(100, 100);
//     glutCreateWindow("hello");
//     init();
//     glutDisplayFunc(display);
//     glutMainLoop();

    //return NULL;
}
