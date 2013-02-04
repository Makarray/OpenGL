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
void specialKeys(int key, int x, int y);
void render(void);
void createObjects();
void init();
void resize(int w, int h);
bool moveEye(int direction);


GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];
GLdouble eyepos[3] = {0,0,8};	//start backwards 8
GLdouble eyefocus[3] = {0,0,7};	//start directly fowards
GLdouble walkspeed = 0.25;	//how quickly the camera walks
int turnspeedx = 2;			//how quickly the camera turns
int turnspeedy = 2;

//LISTS
GLuint list_pyramid;


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(800,650);
  glutCreateWindow("Castle by Matthew Shrider and James Uhe");

  init();
  createObjects();

  glutKeyboardFunc(&keyboard);
  glutSpecialFunc(&specialKeys);
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
	case 'w':
		moveEye(0);
		break;
	case 's':
		moveEye(1);
		break;
	case 'a':
		moveEye(2);
		break;
	case 'd':
		moveEye(3);
		break;
	case 'r':
		moveEye(8);
		break;
	case 'f':
		moveEye(9);
		break;

  }
}

void specialKeys(int key, int x, int y){
	switch (key)
	{
	case GLUT_KEY_LEFT:
		moveEye(4);
		break;
	case GLUT_KEY_RIGHT:
		moveEye(5);
	case GLUT_KEY_UP:
		moveEye(6);
		break;
	case GLUT_KEY_DOWN:
		moveEye(7);
		break;
	}

}

bool moveEye(int direction){
	switch (direction){
	case 0:		//Forward
		eyepos[2] -= walkspeed;
		eyefocus[2] -= walkspeed;
		break;
	case 1:		//Backward
		eyepos[2] += walkspeed;
		eyefocus[2] += walkspeed;
		break;
	case 2:		//left
		eyepos[0] -= walkspeed;
		eyefocus[0] -= walkspeed;
		break;
	case 3:		//right
		eyepos[0] += walkspeed;
		eyefocus[0] += walkspeed;
		break;


	case 4:		//turn left
		break;
	case 5:		//turn right
		break;
	case 6:		//tilt up
		break;
	case 7:		//tilt down
		break;
	case 8:		//go up
		eyepos[1] += walkspeed;
		eyefocus[1] += walkspeed;
		break;
	case 9:		//go down
		eyepos[1] -= walkspeed;
		eyefocus[1] -= walkspeed;
		break;
	default:
		return false;
		break;
	}
	glLoadIdentity();
	gluLookAt(eyepos[0],eyepos[1],eyepos[2],
		eyefocus[0],eyefocus[1],eyefocus[2],
		0,1,0);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvMatrix);
	glutPostRedisplay();

	return true;
}

void init(){
   	glClearColor(0.0,0.0,0.0,1.0);
	glLineWidth(2.0);
	glPointSize(3.0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
}

void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);


  glCallList(list_pyramid);

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
	gluPerspective(60, ratio,1,20);
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyepos[0],eyepos[1],eyepos[2],
		eyefocus[0],eyefocus[1],eyefocus[2],
		0,1,0);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
}

void createObjects(){
	list_pyramid = glGenLists(1);

	glNewList(list_pyramid, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0F,4.0F,0.0F);
		glVertex3f(-0.5F,0.0F,0.5F);
		glVertex3f(.5F,0.0F,.5F);
		glVertex3f(.5F,0.0F,-.5F);
		glColor3f(0.8F,0.8F,0.0F);
		glVertex3f(-.5F,0.0F,-.5F);
		glVertex3f(-0.5F,0.0F,0.5F);
		glEnd();
	glEndList();

}