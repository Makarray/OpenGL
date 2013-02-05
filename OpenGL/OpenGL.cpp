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
GLdouble turnspeedx = .1;			//how quickly the camera turns
GLdouble turnspeedy = .1;

//LISTS
GLuint list_pyramid, list_column, list_windowsemi, list_windowblock, list_crenn;
GLuint list_door, list_stairstep, list_stairside, list_tree, list_hill, list_fence;


void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);


 // glCallList(list_pyramid);
 // glCallList(list_column);
  glCallList(list_fence);

  glFlush();
  glutSwapBuffers();
}

void createObjects(){

	list_pyramid = glGenLists(1);
	glNewList(list_pyramid, GL_COMPILE);
		glColor3ub(85,90,90);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0F,3.0F,0.0F);
		glColor3ub(66,72,70);
		glVertex3f(-0.5F,0.0F,0.5F);
		glColor3ub(95,105,105);
		glVertex3f(.5F,0.0F,.5F);
		glVertex3f(.5F,0.0F,-.5F);
		glColor3ub(60,65,75);
		glVertex3f(-.5F,0.0F,-.5F);
		glVertex3f(-0.5F,0.0F,0.5F);
		glEnd();
	glEndList();

	list_column = glGenLists(1);
	glNewList(list_column, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);	//sides
			glColor3ub(160,160,160);
		glVertex3f(-1.0F,2.0F,1.0F);
		glVertex3f(-1.0F,0.0F,1.0F);
			glColor3ub(190,190,190);
		glVertex3f(1.0F,2.0F,1.0F);
		glVertex3f(1.0F,0.0F,1.0F);		//End of First
		glVertex3f(1.0F,2.0F,-1.0F);
		glVertex3f(1.0F,0.0F,-1.0F);	//end of second
			glColor3ub(160,160,160);
		glVertex3f(-1.0F,2.0F,-1.0F);
		glVertex3f(-1.0F,0.0F,-1.0F);	//end of third
		glVertex3f(-1.0F,2.0F,1.0F);
		glVertex3f(-1.0F,0.0F,1.0F);
	glEnd();
	glBegin(GL_QUADS);		//top and bot
			glColor3ub(190,190,190);
		glVertex3f(1.0F,2.0F,1.0F);
		glVertex3f(1.0F,2.0F,-1.0F);
			glColor3ub(160,160,160);
		glVertex3f(-1.0F,2.0F,-1.0F);	
		glVertex3f(-1.0F,2.0F,1.0F);//end of top
			glColor3ub(160,160,160);
		glVertex3f(1.0F,0.0F,-1.0F);
		glVertex3f(1.0F,0.0F,1.0F);
			glColor3ub(100,100,100);
		glVertex3f(-1.0F,0.0F,1.0F);
		glVertex3f(-1.0F,0.0F,-1.0F);	//end of bot
	glEnd();
	glEndList();

	list_fence = glGenLists(1);
	glNewList(list_fence, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);			//right post
		glColor3ub(0,10,0);
		glVertex3f(-0.04F,2.35F,0.00F);
		glVertex3f(-0.04F,0.0F,0.00F);
		glVertex3f(0.04F,2.35F,0.00F);
		glVertex3f(0.04F,0.0F,0.00F);
		glVertex3f(-0.04F,2.35F,0.00F);
		glVertex3f(-0.04F,0.0F,0.00F);
	glEnd();
	glBegin(GL_QUAD_STRIP);			//left post
		glVertex3f(-0.4F,2.0F,0.0F);
		glVertex3f(-0.4F,0.0F,0.0F);
		glVertex3f(-0.43F,2.0F,0.0F);
		glVertex3f(-0.43F,0.0F,0.0F);
		glVertex3f(-0.4F,2.0F,0.0F);
		glVertex3f(-0.4F,0.0F,0.0F);
	glEnd();
	glBegin(GL_QUAD_STRIP);			//top post
		glVertex3f(-0.8F,2.16F,0.0F);
		glVertex3f(-0.8F,2.0F,0.0F);
		glVertex3f(0.05F,2.16F,0.0F);
		glVertex3f(0.05F,2.0F,0.0F);
		glVertex3f(-0.8F,2.16F,0.0F);
		glVertex3f(-0.8F,2.0F,0.0F);
	glEnd();
	glBegin(GL_QUAD_STRIP);			//bot post
		glVertex3f(-0.8F,1.7F,0.0F);
		glVertex3f(-0.8F,1.56F,0.0F);
		glVertex3f(0.05F,1.7F,0.0F);
		glVertex3f(0.05F,1.56F,0.0F);
		glVertex3f(-0.8F,1.7F,0.0F);
		glVertex3f(-0.8F,1.56F,0.0F);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);		//Spike
		glVertex3f(0.0F,2.9F,0.0F);
		glVertex3f(-0.18F,2.35F,0.0F);
		glVertex3f(0.18F,2.35F,0.0F);
		glVertex3f(-0.18F,2.35F,0.0F);
	glEnd();
	glEndList();

}
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
		eyefocus[0] -= turnspeedx;
		break;
	case 5:		//turn right
		eyefocus[0] += turnspeedx;
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
   	glClearColor(89/255.F,115/255.0F,254/255.0F,1.0);
	glLineWidth(2.0);
	glPointSize(3.0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
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

