/**************************************************
* OpenGL.cpp - First project of OpenGL
*
* Create objects that mirror a digital photograph
* Authors: Matthew Shrider and James Uhe
* ************************************************/
#include <GL/glut.h>	
//#include "stdafx.h"	//for visual c++, just delete this if not on visual studio

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
GLuint list_pyramid, list_column, list_windowsemi, list_windowblock, list_crenn, list_coord;
GLuint list_door, list_stairstep, list_stairside, list_tree, list_hill, list_fence;
GLdouble objectMatrix[16];


void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);

 glPushMatrix();
  glMultMatrixd(objectMatrix);
 /* glPushMatrix();
	glTranslatef(-5.0F,0.0F,0.0F);
	glCallList(list_pyramid);
  glPopMatrix();
  glPushMatrix();
	glTranslatef(-10.0F,0.0F,0.0F);
    glCallList(list_column);
  glPopMatrix();
  glPushMatrix();
	glTranslatef(5.0F,0.0F,0.0F);
  glCallList(list_fence);
  glPopMatrix();
  glPushMatrix();
	glTranslatef(0.0F,-5.0F,0.0F);
  glCallList(list_stairstep);
  glPopMatrix();
*/  glPushMatrix();
	glTranslatef(20.0F,-9.0F,-8.0F);
  glCallList(list_door);
  glPopMatrix();
 glPushMatrix();
	glTranslatef(-10.0F,4.0F,-1.0F);
 glCallList(list_hill);
  glPopMatrix();
  glPopMatrix();



  glFlush();
  glutSwapBuffers();
}

void createObjects(){


//coordinates
	list_coord = glGenLists(1);
	glNewList(list_coord, GL_COMPILE);
  glBegin(GL_LINES);
  glColor3ub(255,0,0);
     glVertex3f(0.0F,0.0F,0.0F);
	 glVertex3f(0.5F,0.0F,.0F);
  glColor3ub(0,255,0);
     glVertex3f(.0F,.0F,.0F);
	 glVertex3f(.0F,.5F,.0F);
  glColor3ub(0,0,255);
     glVertex3f(.0F,.0F,.0F);
	 glVertex3f(.0F,.0F,.5F);
  glEnd();
	glEnd();
	glEndList();
//Pyramid
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
//EndPyarmid
//Block
	list_column = glGenLists(1);
	glNewList(list_column, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);					//sides
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
//End Block

//Fence Begin
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
//Fence End

//Stair Begin
	//front
	list_stairstep=glGenLists(1);
	glNewList(list_stairstep, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.7,0.7,0.7);
	glVertex3f(.1,1.5,.1);
	glVertex3f(.1,.1,.1);
	glVertex3f(5.1,1.5,.1);
	glVertex3f(5.1,.1,.1);
	glEnd();

	//top
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.9,0.9,0.9);
	glVertex3f(.1,1.5,-1.1);
	glVertex3f(.1,1.5,.1);
	glVertex3f(5.1,1.5,-1.1);
	glVertex3f(5.1,1.5,.1);
	glEnd();

	//side A
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(.1,.1,-1.1);
	glVertex3f(.1,.1,.1);
	glVertex3f(.1,1.5,-1.1);
	glVertex3f(.1,1.5,.1);
	glEnd();

	//side B
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5.1,1.5,.1);
	glVertex3f(5.1,.1,.1);
	glVertex3f(5.1,1.5,-1.1);
	glVertex3f(5.1,.1,-1.1);
	glEnd();
glEndList();
//Stair End

//door start
list_door=glGenLists(1);
	glNewList(list_door, GL_COMPILE);

		GLfloat door_x=.3,door_y=.3,door_z=.1;
		for(int i=1; i<=20; i++){
			//brown box
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.5,0.4,0.4);
			glVertex3f(door_x,door_y,door_z+.01);
			glVertex3f(door_x+1.0,door_y,door_z+.01);
			glVertex3f(door_x,door_y+2.0,door_z+.01);
			glVertex3f(door_x+1.0,door_y+2.0,door_z+.01);
			glEnd();
			//black box
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,0.0,0.0);
			glVertex3f(door_x-.3,door_y-.3,door_z);
			glVertex3f(door_x+1.3,door_y-.3,door_z);
			glVertex3f(door_x-.3,door_y+2.3,door_z);
			glVertex3f(door_x+1.3,door_y+2.3,door_z);
			glEnd();
			if(i%5!=0){
				door_x+=1.3;
			}
			else{
				door_y+=2.3;
				door_x=.3;
			}
		}
	glEndList();
//door end

	//NOT DONE WITH THIS, but you can see where I'm headed with it.
//hill start
	list_hill=glGenLists(1);
		glNewList(list_hill, GL_COMPILE);
		//front
			glBegin(GL_TRIANGLE_STRIP);
				glColor3f(0.1,.7,0.0);
				glVertex3f(0.1,0.1,0.0);
				glVertex3f(15.0,0.1,0.0);
				glVertex3f(5.0,5.0,0.0);

			glEnd();

			//back
			glBegin(GL_TRIANGLE_STRIP);
				glColor3f(0.1,.7,0.0);
				glVertex3f(0.1,0.1,-20);
				glVertex3f(15.0,0.1,-20);
				glVertex3f(5.0,5.0,-20);

			glEnd();
			//Side A
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,.75,0.0);
			glVertex3f(5.0,5.0,0.0);
			glVertex3f(15.0,0.1,0.0);
			glVertex3f(5.0,5.0,-20);
			glVertex3f(15.0,0.1,-20);
			glEnd();

			//Side B
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,.7,0.0);
				glVertex3f(0.1,0.1,0.0);
				glVertex3f(5.0,5.0,0.0);
				glVertex3f(0.1,0.1,-20);
				glVertex3f(5.0,5.0,-20);
			glEnd();

			//Dirt side A
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.4,.2,.2);
			glVertex3f(15.0,0.1,-20);
			glVertex3f(15.0,0.1,0.0);
			glVertex3f(15.0,-10.0,-20);
			glVertex3f(15.0,-10.0,0.0);
			glEnd();

			//Dirt side B
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.4,.2,.2);
			glVertex3f(0.1,0.1,0.0);
			glVertex3f(0.1,0.1,-20);
			glVertex3f(-8.0,-10.0,0.0);
			glVertex3f(-8.0,-10.0,-20);
			glEnd();

			//point
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.0,.65,0.0);
			glVertex3f(7.5,0.1,10.0);
			glVertex3f(0.1,0.1,0.0);
			glVertex3f(15.0,0.1,0.0);
			glVertex3f(5.0,5.0,0.0);
			glVertex3f(0.1,0.1,0.0);
			glEnd();

			//slope to outcrop
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,.71,0.0);
				glVertex3f(15.0,0.1,0.0);
				glVertex3f(7.5,0.1,10.0);
				glVertex3f(20.0,-7.5,0.0);
				glVertex3f(20,0.-8.5,12.0);
			glEnd();

			//outcrop
				glBegin(GL_QUAD_STRIP);
					glColor3f(0.0,.7,0.0);
					glVertex3f(20.0,-7.5,0.0);
					glVertex3f(20,0.-8.5,12.0);
					glVertex3f(25.0,-8.5,0.0);
					glVertex3f(25,0.-8.5,13.0);
				glEnd();
				//outcrop ramp
					glBegin(GL_QUAD_STRIP);
					glColor3f(0.0,.65,0.0);
						glVertex3f(20.0,-7.5,0.0);
						glVertex3f(25.0,-8.5,0.0);
						glVertex3f(20.0,-7.5,-.3);
						glVertex3f(25.0,-6.5,-1.0);
					glEnd();

					//outcrop ramp castle side drop (dirt)
						glBegin(GL_QUAD_STRIP);
						glColor3f(0.4,.2,.2);
							glVertex3f(20.0,-7.5,-.3);
							glVertex3f(25.0,-6.5,-1.0);
							glVertex3f(20.0,-10.0,-.3);
							glVertex3f(25.0,-10.0,-1.0);
						glEnd();

						//outcrop drop (dirt)
						glBegin(GL_QUAD_STRIP);
						glColor3f(0.4,.2,.2);
							glVertex3f(25.0,-8.5,0.0);
							glVertex3f(25,0.-8.5,13.0);
							glVertex3f(25.0,-10.0,0.0);
							glVertex3f(25,0.-10.0,13.0);
						glEnd();

						//outcrop ramp castle side drop (dirt)
							glBegin(GL_QUAD_STRIP);
							glColor3f(0.4,.2,.2);
								glVertex3f(25.0,-10.0,-1.0);
								glVertex3f(25.0,-6.5,-1.0);
								glVertex3f(25.0,-10.0,0.0);
								glVertex3f(25.0,-8.5,0.0);
							glEnd();

							//slope to outcrop drop (dirt)
							glBegin(GL_QUAD_STRIP);
							glColor3f(0.4,.2,.2);
								glVertex3f(15.0,0.1,0.0);
								glVertex3f(20.0,-7.5,0.0);
								glVertex3f(15.0,-10.0,0.0);
								glVertex3f(20.0,-10.0,0.0);
							glEnd();


			//outcrop
				glBegin(GL_QUAD_STRIP);
					glColor3f(0.0,.6,0.0);

					glVertex3f(20,0.-8.5,12.0);
					glVertex3f(25,0.-8.5,13.0);
					glVertex3f(20,0.-6.8,12.0);
					glVertex3f(25,0.-6.8,13.0);

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
	int modifiers = glutGetModifiers();
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if ( modifiers == GLUT_ACTIVE_SHIFT ){
			moveEye(10);
		}
		else if(modifiers == GLUT_ACTIVE_CTRL) {
			moveEye(13);
		} else {
		moveEye(4);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (modifiers == GLUT_ACTIVE_SHIFT ){
		moveEye(11);
		} else if(modifiers == GLUT_ACTIVE_CTRL) {
			moveEye(12);
		} else {
			moveEye(5);
		}
		break;
	case GLUT_KEY_UP:
		if (modifiers == GLUT_ACTIVE_CTRL) {
			moveEye(14);
		} else {
		moveEye(6);
		}
		break;
	case GLUT_KEY_DOWN:
		if (modifiers == GLUT_ACTIVE_CTRL) {
			moveEye(15);
		} else {
		moveEye(7);
		}
		break;
	}

}

bool moveEye(int direction){
	switch (direction){
	case 0:		//Forward
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0,0,1);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 1:		//Backward
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0,0,-1);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 2:		//left
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(1,0,0);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 3:		//right
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-1,0,0);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;


	case 4:		//turn left
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(-5,0,1,0);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 5:		//turn right
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(5,0,1,0);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 6:		//tilt up
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(-5,1,0,0);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 7:		//tilt down
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(5,1,0,0);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 8:		//go up
		
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0,-1.0,0.0);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 9:		//go down
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0,1.0,0);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 10:	//rotate left
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(5,0,0,1);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 11:	//rotate right
		glPushMatrix();
		glLoadIdentity();
		glTranslated(0.0F,0.0F,8.0F);
		glRotated(-5,0,0,1);
		glTranslated(0.0F,0.0F,-8.0F);
		glMultMatrixd(objectMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 12:	//TurnObject ccw
		glPushMatrix();
		glLoadMatrixd(objectMatrix);
		glRotated(5,0,1,0);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 13:	//TurnObject cw
		glPushMatrix();
		glLoadMatrixd(objectMatrix);
		glRotated(-5,0,1,0);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 14:	//TurnObject Over
		glPushMatrix();
		glLoadMatrixd(objectMatrix);
		glRotated(5,1,0,0);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;
	case 15:	//TurnObject Under
		glPushMatrix();
		glLoadMatrixd(objectMatrix);
		glRotated(-5,1,0,0);
		glGetDoublev(GL_MODELVIEW_MATRIX,objectMatrix);
		glPopMatrix();
		break;

	default:
		return false;
		break;
	}
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

	glPushMatrix();
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
	glPopMatrix();

	glPushMatrix();
    glLoadIdentity();                                   /* C = I     */
	glGetDoublev(GL_MODELVIEW_MATRIX, objectMatrix);   /* potCF = C */
    glPopMatrix();

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
	gluPerspective(60, ratio,1,60);
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyepos[0],eyepos[1],eyepos[2],
		eyefocus[0],eyefocus[1],eyefocus[2],
		0,1,0);
}

