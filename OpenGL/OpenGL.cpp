/**************************************************
* OpenGL.cpp - First project of OpenGL
*
* Create objects that mirror a digital photograph
* Authors: Matthew Shrider and James Uhe
* ************************************************/

#include "stdafx.h"	//for visual c++, just delete this if not on visual studio
#include "gl/glut.h"

//Functions
void keyboard(unsigned char key, int x, int y);
void render(void);
void createObjects();
void init();
void resize(int w, int h);


GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(800,650);
  glutCreateWindow("Castle by Matthew Shrider and James Uhe");

  init();
  createObjects();

  glutKeyboardFunc(&keyboard);
  glutDisplayFunc(&render);
  glutReshapeFunc(&resize);
  glutMainLoop();

  return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y){
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
  }
}

void init(){
   	glClearColor(0.0,0.0,0.0,1.0);
	glLineWidth(2.0);
	glPointSize(3.0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);

  //just a test
  glBegin(GL_QUAD_STRIP);
	glColor3f(0.0F,0.8F,0.8F);
	glVertex2f(-0.5,-.5);
	glVertex2f(.5,-.5);
	glVertex2f(-.5,.5);
	glVertex2f(.5,.5);
  glEnd();


  glFlush();
  glutSwapBuffers();
}

void resize (int w, int h){
	glViewport(0,0,(GLint) w, (GLint) h);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio;
	if (w <= h){
		ratio = static_cast<GLfloat> (h) / w;
	} else {
		ratio = static_cast<GLfloat> (w) / h;
	}
	gluPerspective(60, ratio,1,10);
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
	gluLookAt(0,0,2.5,0,0,0,0,1,0);
}



void createObjects(){
	GLuint list_fenceSpike;
	list_fenceSpike = glGenLists(1);




}

