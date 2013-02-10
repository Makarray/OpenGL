/**************************************************
* OpenGL.cpp - First project of OpenGL
*
* Create objects that mirror a digital photograph
* Authors: Matthew Shrider and James Uhe
* ************************************************/
#if (defined(WIN32) | defined(_WIN32))
#define _USE_MATH_DEFINES
#endif
#include <GL/glut.h>
#include <math.h>
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
GLuint list_pyramid, list_column, list_windowsemi, list_windowblock, list_crenn, list_coord, list_roof;
GLuint list_door, list_stairstep, list_stairside, list_tree, list_hill, list_fence,list_tower;
GLuint list_wall,list_outer_wall,list_small_tower,list_full_castle;
GLdouble objectMatrix[16];


void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);

 glPushMatrix();
  glMultMatrixd(objectMatrix);

  /*glPushMatrix();
	glTranslatef(-5.0F,0.0F,0.0F);
	glCallList(list_pyramid);
  glPopMatrix();
  */

  glPushMatrix();
  	glTranslatef(-10,-5,-15);
  	glScaled(.5,.5,.5);
  	glCallList(list_full_castle);
    glPopMatrix();

    glPushMatrix();
   	glTranslatef(-30.0F,0,-10.0F);
   	glScaled(.8,.6,.5);
    glCallList(list_hill);
     glPopMatrix();

	 glPushMatrix();
	 glTranslatef(1.0F,0.0F,-13.0F);
	 glCallList(list_crenn);
	 //glCallList(list_roof);
	 glPopMatrix();

/*

     glPushMatrix();
    	glTranslatef(-25,0,-25);
    	glRotated(90,0,1,0);
    	glScaled(.8,.6,.5);
     glCallList(list_hill);
      glPopMatrix();
*/
  //  glPushMatrix();
//	glTranslatef(-5.0F,0.0F,0.0F);
//	glCallList(list_wall);
//  glPopMatrix();


//  glPushMatrix();
//	glTranslatef(10.0F,0.0F,0.0F);
//    glCallList(list_column);
//  glPopMatrix();


/*
  double stair_x=0,stair_y =-5.0, stair_z=0;
  for(int i =0; i<20;i++){

	  glPushMatrix();
	  glTranslatef(stair_x,stair_y,stair_z);
	  glCallList(list_stairstep);
	  glPopMatrix();
	  stair_y+=.1;
	  stair_z+=-.1;
	 }


  glPushMatrix();

	 glRotatef(15,1,0,0);
	glTranslatef(-.2,-4.4,1);
  glCallList(list_stairside);
   glPopMatrix();


  glPushMatrix();
	glTranslatef(20.0F,-9.0F,-8.0F);
  glCallList(list_door);
  glPopMatrix();

  glPushMatrix();
	glTranslatef(30,-10,0.0);
  glCallList(list_tree);
   glPopMatrix();


   glPushMatrix();
	glTranslatef(-5.0F,0.0F,0.0F);
   glCallList(list_windowblock);
    glPopMatrix();

    glPushMatrix();
 	glTranslatef(-0.0F,0.0F,0.0F);
    glCallList(list_windowsemi);
     glPopMatrix();
*/
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
		//	glColor3ub(160,160,160);
		glVertex3f(1.0F,0.0F,-1.0F);
		glVertex3f(1.0F,0.0F,1.0F);
		//	glColor3ub(100,100,100);
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
	glVertex3f(.1,.2,.1);
	glVertex3f(.1,.1,.1);
	glVertex3f(3.1,.2,.1);
	glVertex3f(3.1,.1,.1);
	glEnd();

	//top
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.9,0.9,0.9);
	glVertex3f(.1,.2,-.2);
	glVertex3f(.1,.2,.1);
	glVertex3f(3.1,.2,-.2);
	glVertex3f(3.1,.2,.1);
	glEnd();

	//side A
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(.1,.1,-.2);
	glVertex3f(.1,.1,.1);
	glVertex3f(.1,.2,-.2);
	glVertex3f(.1,.2,.1);
	glEnd();

	//side B
	glBegin(GL_QUAD_STRIP);
	glVertex3f(3.1,.2,.1);
	glVertex3f(3.1,.1,.1);
	glVertex3f(3.1,.2,-.2);
	glVertex3f(3.1,.1,-.2);
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
				glVertex3f(15.0,0.1,-20);
				glVertex3f(0.1,0.1,-20);
				glVertex3f(5.0,5.0,-20);

			glEnd();

			//back drop
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.325,.2,.2);
				glVertex3f(0.1,0.1,-20);
				glVertex3f(15.0,0.1,-20);
				glVertex3f(-8.0,-10.0,-20);
				glVertex3f(15.0,-10.0,-20);
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

			//Peak hump
			double front_x=5.0,front_y=5.0,front_z=-20.0;
			glBegin(GL_QUAD_STRIP);
				glColor3f(0.0,.65,0.0);
				glVertex3f(5.0,5.0,-20);

				for(int i=0; i<360;i++){
					double radius= (2*M_PI)*i/360;
					front_y= sin(radius)/9+4.9;
					front_x= cos(radius)/9+5;
					glVertex3f(front_x,front_y,front_z);
					glVertex3f(front_x,front_y,0);
				}
				glEnd();


			//Dirt side A
			glBegin(GL_QUAD_STRIP);
					glColor3ub(130,130,80);

					glVertex3f(15.0,0.1,-20);
					glVertex3f(15.0,0.1,0.0);
					glVertex3f(15.0,-10.0,-20);
					glVertex3f(15.0,-10.0,0.0);
			glEnd();
			//rounded side A
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,.65,0.0);
			double side_x=5.0,side_y=5.0,side_z=-20.0;
				for(int i=0; i<360;i++){
					double radius= (2*M_PI)*i/360;
					side_y= sin(radius)/4;
					side_x= cos(radius)/4+15;
					glVertex3f(side_x,side_y,side_z);
				glVertex3f(side_x,side_y,0);
			}
			glEnd();
			//Dirt side B
			glBegin(GL_QUAD_STRIP);
			glColor3ub(130,130,80);
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
				//outcrop hump

				double ramp_x=24.99,ramp_y=-8.2,ramp_z=0.0;

				glBegin(GL_TRIANGLE_FAN);
					glColor3f(0.0,.65,0.0);
					glVertex3f(20.0,-7.5,0.0);

					for(int i=0; i<180;i++){
						double radius= M_PI*i/180;
						ramp_y= sin(radius)-8.5;
						ramp_z= cos(radius);
						glVertex3f(ramp_x,ramp_y,ramp_z);
					}
					glEnd();

					//outcrop hump cover
					double cover_x=24.99,cover_y=-8.2,cover_z=0.0;
					glBegin(GL_TRIANGLE_FAN);
					glColor3ub(130,130,80);
					glVertex3f(25.0,-8.5,0.0);

						for(int i=0; i<300;i++){
							double radius= M_PI*i/300;
							cover_y= sin(radius)-8.5;
							cover_z= cos(radius);
							glVertex3f(cover_x,cover_y,cover_z);
						}
						glEnd();
					//outcrop ramp castle side drop (dirt)
						glBegin(GL_QUAD_STRIP);
						glColor3ub(130,130,80);
							glVertex3f(20.0,-7.5,-.001);
							glVertex3f(ramp_x,ramp_y,ramp_z);
							glVertex3f(20.0,-10.0,-.3);
							glVertex3f(25.0,-10.0,-1.0);
						glEnd();

						//outcrop drop (dirt)
						glBegin(GL_QUAD_STRIP);
						glColor3ub(130,130,80);
							glVertex3f(25.0,-8.5,-1.0);
							glVertex3f(25,0.-8.5,13.0);
							glVertex3f(25.0,-10.0,-1.0);
							glVertex3f(25,0.-10.0,13.0);
						glEnd();

							//slope to outcrop drop (dirt)
							glBegin(GL_QUAD_STRIP);
							glColor3ub(130,130,80);
								glVertex3f(15.0,0.1,0.0);
								glVertex3f(20.0,-7.5,0.0);
								glVertex3f(15.0,-10.0,0.0);
								glVertex3f(20.0,-10.0,0.0);
							glEnd();


			//outcrop rise (away from castle)
				glBegin(GL_QUAD_STRIP);
				glColor3ub(130,130,80);
					glVertex3f(25,0.-8.5,13.0);
					glVertex3f(20,0.-8.5,12.0);
					glVertex3f(27,0.-7.2,14.0);
					glVertex3f(7.5,0.1,10.0);
					//glVertex3f(20,0.-7.2,12.0);
				glEnd();

				//platform away from castle
				glBegin(GL_QUAD_STRIP);

				glColor3f(0.0,6.3,.0);
				glVertex3f(27,0.-7.2,14.0);
				glVertex3f(7.5,0.1,10.0);
				glVertex3f(27,0.-7.2,17.0);
				glVertex3f(7.5,0.1,17.0);
				glEnd();

				//platform away from castle drop
				glBegin(GL_QUAD_STRIP);
				glColor3ub(130,130,80);
				glVertex3f(27,-10,17.0);
				glVertex3f(27,0.-10.0,13.0);
				glVertex3f(27,0.-7.2,17.0);
				glVertex3f(27,0.-7.2,14.0);

				glEnd();
				//castle facing platform drop
				glBegin(GL_QUAD_STRIP);

				glColor3ub(130,130,80);
				glVertex3f(25,0.-8.5,13.0);
				glVertex3f(27,0.-7.2,14.0);
				glVertex3f(25,0.-10.0,13.0);
				glVertex3f(27,0.-10.0,13.0);

				glEnd();
				//front platform drop
				glBegin(GL_QUAD_STRIP);
				glVertex3f(27,0.-7.2,17.0);
				glVertex3f(7.5,0.1,17.0);
				glVertex3f(27,-10.0,17.0);
				glVertex3f(7.5,-10.0,17.0);
				glEnd();

				//left point drop
				glBegin(GL_QUAD_STRIP);
				glColor3ub(130,130,80);
				glVertex3f(7.5,0.1,10.0);
				glVertex3f(0.1,0.1,0.0);
				glVertex3f(7.5,-10.0,10.0);
				glVertex3f(-8.0,-10.0,0.0);
				glEnd();

				glBegin(GL_QUAD_STRIP);
				glColor3ub(130,130,80);
				glVertex3f(7.5,0.1,10.0);
				glVertex3f(7.5,-10.0,10.0);
				glVertex3f(7.5,0.1,17.0);
				glVertex3f(7.5,-10.0,17.0);

				glEnd();
			glEndList();

	//tree start
			list_tree=glGenLists(1);
			glNewList(list_tree, GL_COMPILE);
				glBegin(GL_QUAD_STRIP);

				glColor3f(0.36,.2,.2);
				double trunk_x=.1,trunk_y=.1;
				for(int i=0; i<360;i++){
					double radius= 2*M_PI*i/360;
					trunk_y= sin(radius)/3;
					trunk_x= cos(radius)/3;
					glVertex3f(trunk_x,5,trunk_y);
					glVertex3f(trunk_x,0,trunk_y);
				}
				glEnd();


				glBegin(GL_TRIANGLE_FAN);
				double leaves_x=0,leaves_y=0;
				glColor3f(0.0,6.3,.0);
				glVertex3f(0,6.5,sin(2*M_PI)/6);

				for(int i=0; i<720;i++){
					double radius = 2*M_PI*i/720;
					leaves_x=2*cos(radius);
					leaves_y=2*sin(radius);
					glVertex3f(leaves_x,2,leaves_y);
				}
				glEnd();
				glEndList();
	//end tree

	//stairside start
			list_stairside=glGenLists(1);
			glNewList(list_stairside, GL_COMPILE);

			//front
			glBegin(GL_QUAD_STRIP);
					glColor3f(0.7,0.7,0.7);
					glVertex3f(0,.2,.1);

					glVertex3f(0,0,.1);
					glVertex3f(.3,.2,.1);
					glVertex3f(.3,0,.1);

					glEnd();

			//Back
			glBegin(GL_QUAD_STRIP);
					glColor3f(0.7,0.7,0.7);

					glVertex3f(0,2.2,-3);
					glVertex3f(0,2,-3);
					glVertex3f(.3,2.2,-3);
					glVertex3f(.3,2,-3);

					glEnd();

					//top
					glBegin(GL_QUAD_STRIP);
					glColor3f(0.6,0.6,0.6);
					glVertex3f(.3,.2,.1);
					glVertex3f(.3,2.2,-3);
					glVertex3f(0,.2,.1);
					glVertex3f(0,2.2,-3);
					glEnd();

					//side A
					glBegin(GL_QUAD_STRIP);
					glColor3f(6.5,6.5,6.5);
					glVertex3f(.3,.2,.1);
					glVertex3f(.3,0,.1);
					glVertex3f(.3,2.2,-3);
					glVertex3f(.3,2,-3);
					glEnd();

					//side B
					glBegin(GL_QUAD_STRIP);
					glColor3f(6.5,6.5,6.5);
					glVertex3f(0,0,.1);
					glVertex3f(0,.2,.1);
					glVertex3f(0,2,-3);
					glVertex3f(0,2.2,-3);
					glEnd();
			glEndList();
		//stairside end

		//crennelations
			list_crenn = glGenLists(1);
			glNewList(list_crenn,GL_COMPILE);
			glBegin(GL_QUADS);
			glColor3ub(110,110,110);
			glVertex3f(-.07F,.2F,0.0F);
			glVertex3f(-.07F,0.0F,0.0F);
			glColor3ub(140,140,140);
			glVertex3f(.07F,0.0F,0.0F);
			glVertex3f(.07F,.2F,0.0F);
			
			glColor3ub(110,110,110);
			glVertex3f(.07F,.3F,0.0F);
			glVertex3f(.07F,0.0F,0.0F);
			glColor3ub(140,140,140);
			glVertex3f(.25F,0.0F,0.0F);
			glVertex3f(.25F,.3F,0.0F);
			
			glColor3ub(110,110,110);
			glVertex3f(.25F,.4F,0.0F);
			glVertex3f(.25F,0.0F,0.0F);
			glColor3ub(140,140,140);
			glVertex3f(.34F,0.0F,0.0F);
			glVertex3f(.34F,.4F,0.0F);
			glEnd();
			glEndList();

		//roof
			list_roof = glGenLists(1);
			glNewList(list_roof, GL_COMPILE);
			glBegin(GL_QUAD_STRIP);
			glColor3ub(160,160,160);
			glVertex3f(-0.5F,.25F,0.0F);
			glVertex3f(-0.5F,0.0F,0.0F);
			glVertex3f(.5F,.25F,0.0F);
			glVertex3f(.5F,0.0F,0.0F);

			glVertex3f(.5F,.25F,-.5F);
			glVertex3f(.5F,.0F,-.5F);
			glVertex3f(-.5F,.25F,-.5F);
			glVertex3f(-.5F,.0F,-.5F);
			glVertex3f(-.5F,.25F,.0F);
			glVertex3f(-.5F,.0F,.0F);
			glEnd();
			glBegin(GL_QUADS);
			glColor3ub(190,190,190);
			glVertex3f(-.5F,.2501F,-.5F);
			glVertex3f(-.5F,.2501F,0.0F);
			glVertex3f(.5F,.2501F,0.0F);
			glVertex3f(.5F,.2501F,-.5F);
			
			glColor3ub(80,80,80);
			glVertex3f(-.5F,0.0F,0.0F);
			glVertex3f(-.5F,0.0F,-.5F);
			glVertex3f(.5F,0.0F,-.5F);
			glVertex3f(.5F,0.0F,0.0F);
			glEnd();
			glEndList();

		//windowblock start
			list_windowblock=glGenLists(1);
			glNewList(list_windowblock, GL_COMPILE);
			glBegin(GL_QUAD_STRIP);
				glColor3f(0,0,0);
				glVertex3f(0,1.5,0);
				glVertex3f(0,0,0);
				glVertex3f(1,1.5,0);
				glVertex3f(1,0,0);
			glEnd();

		//bottom strip
			glBegin(GL_QUAD_STRIP);
				glColor3f(6,6,6);
				glVertex3f(0,1,0.01);
				glVertex3f(1,1,.01);
				glVertex3f(0,1.05,.01);
				glVertex3f(1,1.05,0.01);

		//top strip
			glEnd();
			glBegin(GL_QUAD_STRIP);
				glColor3f(6,6,6);
				glVertex3f(0,.5,0.01);
				glVertex3f(1,.5,.01);
				glVertex3f(0,.55,.01);
				glVertex3f(1,.55,0.01);

			glEnd();

		//vertical strip
			glBegin(GL_QUAD_STRIP);
				glColor3f(6,6,6);
				glVertex3f(.475,0,0.01);

				glVertex3f(.525,0,.01);
				glVertex3f(.475,1.5,.01);
				glVertex3f(.525,1.5,0.01);
			glEnd();
			glEndList();


		//windowblock start
			list_windowsemi=glGenLists(1);
			glNewList(list_windowsemi, GL_COMPILE);

		//semi black block
			glBegin(GL_TRIANGLE_FAN);
			double semi_x=0,semi_y=0;
			glColor3f(0.0,0,.0);
			glVertex3f(0,0,0);

			for(int i=0; i<=180;i++){
				double radius = M_PI*i/180;
				semi_x=2*cos(radius);
				semi_y=2*sin(radius)/2;
				glVertex3f(semi_x,semi_y,0);
			}
			glEnd();

		//black block
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.0,0,.0);
				glVertex3f(-2*(cos(M_PI)),-1*M_PI/2,0);
				glVertex3f(-2*(cos(M_PI)),0,0);
				glVertex3f(2*(cos(M_PI)),-1*M_PI/2,0);
				glVertex3f(2*(cos(M_PI)),0,0);

			glEnd();

			//semi block outline
				glBegin(GL_QUAD_STRIP);
				glColor3f(.2,.2,.2);
					glVertex3f(-2*(cos(M_PI))+.1,-1*M_PI/2-.1,-.01);
					glVertex3f(-2*(cos(M_PI))+.1,.1,-.01);
					glVertex3f(2*(cos(M_PI))-.1,-1*M_PI/2-.1,-.01);
					glVertex3f(2*(cos(M_PI))-.1,.1,-.01);
				glEnd();

			//semi outline
			glBegin(GL_TRIANGLE_FAN);
			double semi_outline_x=0,semi_outline_y=0;
			glColor3f(.2,.2,.2);
			glVertex3f(0,0,0);

			for(int i=0; i<=180;i++){
				double radius = M_PI*i/180;
				semi_outline_x=2*cos(radius);
				semi_outline_y=sin(radius)+.1;
				if(semi_outline_x<0){
					semi_outline_x-=.1;
				}
				else semi_outline_x+=.1;
				glVertex3f(semi_outline_x,semi_outline_y,-.01);
			}
			glEnd();

			//horizontal divide (top)
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.2,.20,.20);
				glVertex3f(2*(cos(M_PI)),-.2,.1);
				glVertex3f(-2*(cos(M_PI)),-.2,.1);
				glVertex3f(2*(cos(M_PI)),-.1,.1);
				glVertex3f(-2*(cos(M_PI)),-.1,.1);

			glEnd();


			//horizontal divide (bottom)
			glBegin(GL_QUAD_STRIP);
			glColor3f(0.2,.20,.20);
				glVertex3f(2*(cos(M_PI)),-.2-M_PI/4,.1);
				glVertex3f(-2*(cos(M_PI)),-.2-M_PI/4,.1);
				glVertex3f(2*(cos(M_PI)),-.1-M_PI/4,.1);
				glVertex3f(-2*(cos(M_PI)),-.1-M_PI/4,.1);

			glEnd();

			//vertical divide (center)
				glBegin(GL_QUAD_STRIP);
				glColor3f(.2,.2,.2);
				glVertex3f(-.1,-1*M_PI/2,.1);
				glVertex3f(.1,-1*M_PI/2,.1);
				glVertex3f(-.1,1,.1);
				glVertex3f(.1,1,.1);
				glEnd();


			//vertical divide (left)
				glBegin(GL_QUAD_STRIP);
				glColor3f(.2,.2,.2);
				glVertex3f(.1-M_PI/3,sin(2*M_PI/3),.1);
				glVertex3f(-.1-M_PI/3,sin(2*M_PI/3),.1);
				glVertex3f(.1-M_PI/3,-1*M_PI/2,.1);
				glVertex3f(-.1-M_PI/3,-1*M_PI/2,.1);
				glEnd();
			//vertical divide (left)
				glBegin(GL_QUAD_STRIP);
				glColor3f(.2,.2,.2);
				glVertex3f(.1+M_PI/3,sin(2*M_PI/3),.1);
				glVertex3f(-.1+M_PI/3,sin(2*M_PI/3),.1);
				glVertex3f(.1+M_PI/3,-1*M_PI/2,.1);
				glVertex3f(-.1+M_PI/3,-1*M_PI/2,.1);
				glEnd();

			glEndList();


			//tower start
				list_tower=glGenLists(1);
				glNewList(list_tower, GL_COMPILE);

			 for(int row=0; row<3;row++){
				  for(int col=0; col<12;col++){
					glPushMatrix();
						glRotated(72,0,1,0);
						glTranslatef(row,col,0.0F);
						glCallList(list_column);
					glPopMatrix();
					glPushMatrix();
						glRotated(144,0,1,0);
						glTranslatef(row+2,col,2);
						glCallList(list_column);
					glPopMatrix();
					glPushMatrix();
						glRotated(216,0,1,0);
						glTranslatef(row,col,5);
						glCallList(list_column);
					glPopMatrix();

					glPushMatrix();
						glRotated(288,0,1,0);
						glTranslatef(row-3,col,4);
						glCallList(list_column);
					glPopMatrix();

					glPushMatrix();
						glRotated(360,0,1,0);
						glTranslatef(row-3,col,1);
						glCallList(list_column);
					glPopMatrix();
				  }
			  }

			  	  	  glPushMatrix();
						glTranslatef(-3,10,2.12);
					   glCallList(list_windowblock);
					    glPopMatrix();
					    glPushMatrix();
						glTranslatef(-1.5,10,2.12);
					   glCallList(list_windowblock);
					    glPopMatrix();
					    glEndList();


			//begin  castle wall
						list_wall=glGenLists(1);
									glNewList(list_wall, GL_COMPILE);
					    int num =0;
					        for(int row=0; row<12;row+=2){
					    	  for(int col=0; col<10;col+=2){


					    		  //front left wall
					    		  	glPushMatrix();
					    		  	glTranslatef(row,col,0.0F);
					    		    glCallList(list_column);
					    		    glPopMatrix();

					    			//windows on front wall
					    			if(col ==8&&num <5){
					    			   glPushMatrix();
					    			   glScaled(.5,.8,1);
					    				glTranslatef(row*2.225,col,1.1);
					    			   glCallList(list_windowblock);
					    			    glPopMatrix();
					    			    num++;
					    			}
					    	  }
					        }
					  glEndList();


				//begin  castle wall
				list_outer_wall=glGenLists(1);
				glNewList(list_outer_wall, GL_COMPILE);
			  		glPushMatrix();
			  		glTranslatef(0,0,0);
			  		glScaled(.9,1,1);
					glCallList(list_wall);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(17.7,0,0);
			  		glScaled(.9,1,1);
					glCallList(list_wall);
					glPopMatrix();

					    	  for(int row=0; row>-20;row-=2){
					    		  for(int col=0; col<9;col+=2){
					    			  //left side wall
					    			  	glPushMatrix();
					    			  	glTranslatef(-4,col,row-4);
					    			    glCallList(list_column);
					    			    glPopMatrix();

					    			    //right side wall
					    			    glPushMatrix();
					    				glTranslatef(31.8,col,row-4);
					    				glCallList(list_column);
					    				glPopMatrix();
					      	  }
					    		  }
					    	  //back wall
					    	  for(int row=0; row<36;row+=2){
					    		  for(int col =0; col< 9; col+=2){
					    			glPushMatrix();
					    			glTranslatef(row-3.7,col,-24);
					    			glCallList(list_column);
					    			glPopMatrix();
					    		  }
					    	  }
					    	  glPushMatrix();
					    	  	glTranslatef(-2.7,0.0F,1);
					    	  	glCallList(list_tower);
					    	    glPopMatrix();

					    	  glPushMatrix();
					    		glTranslatef(33.6,0.0,1);
					    		glCallList(list_tower);
					    		glPopMatrix();

					    	  glPushMatrix();
					    		glTranslatef(10,0,0.0F);
					    	  glCallList(list_door);
					    	  glPopMatrix();

					 glEndList();
		//end castle wall

	  //Begin small tower

		 list_small_tower=glGenLists(1);
		glNewList(list_small_tower, GL_COMPILE);

					for(int i=0; i<2;i++){
					  glPushMatrix();
						glTranslatef(8,6*i,-6);
						glRotated(-90,0,1,0);
						glScaled(.3,.6,.5);
						glCallList(list_wall);
					  glPopMatrix();

					  glPushMatrix();
						glTranslatef(5,6*i,-3);
						glRotated(90,0,1,0);
						glScaled(.3,.6,.5);
						glCallList(list_wall);
					  glPopMatrix();

					  glPushMatrix();
						glTranslatef(8,6*i,-3);
						glRotated(180,0,1,0);
						glScaled(.3,.6,.5);
						glCallList(list_wall);
					  glPopMatrix();

					  glPushMatrix();
						glTranslatef(5,6*i,-6);
						glScaled(.3,.6,.5);
						glCallList(list_wall);
					  glPopMatrix();

					}
					  glPushMatrix();
						glTranslatef(6,11,-2.49);
						glScaled(.3,.3,.5);
						glCallList(list_windowsemi);
					  glPopMatrix();


					glEndList();

	  //Begin full castle
			 list_full_castle=glGenLists(1);
			glNewList(list_full_castle, GL_COMPILE);
					for(int row =0; row <2;row++){
						  for(int col=0;col<25;col++){

							  glPushMatrix();
								glTranslatef(14,col,-15-row);
								glCallList(list_column);
								glPopMatrix();

							  glPushMatrix();
								glTranslatef(16,col,-15-row);
								glCallList(list_column);
								glPopMatrix();

								//window on tallest tower
								if(col==22&&row==0){
									  glPushMatrix();
										glTranslatef(15,col+2,-13.9-row);
										glScaled(.5,.5,1);
										glCallList(list_windowsemi);
										glPopMatrix();
								}
						  }
					  }

					//peak of tallest tower
					  glPushMatrix();
						glTranslatef(15,25,-15.5);
						  glScaled(2.5,7,3);
						glCallList(list_pyramid);
					  glPopMatrix();
					  
					  glPushMatrix();
					    glTranslatef(15,22,-13.5);
						glScaled(4.6,1.3,6);
						glCallList(list_roof);
					  glPopMatrix();
					  
					  glPushMatrix();
					    glTranslatef(15,17,-13.5);
						glScaled(4.6,1.3,6);
						glCallList(list_roof);
					  glPopMatrix();



					  //wall around castle
					  glPushMatrix();
						glTranslatef(0,0,0);
						glCallList(list_outer_wall);
					  glPopMatrix();

					   glPushMatrix();
					    glTranslatef(13,9.9,1.4);
						glScaled(35,1.7,6);
						glCallList(list_roof);
					  glPopMatrix();

					  //Inner Wall
					  for(int width=0; width<3;width++){

							  glPushMatrix();
								glTranslatef(6*width+5,0,-6);
								glScaled(.5,1,.5);
								glCallList(list_wall);
							  glPopMatrix();

							  glPushMatrix();
								glTranslatef(23,0,-6-6*width);
								glRotated(90,0,1,0);
								glScaled(.5,1,.5);
								glCallList(list_wall);
							  glPopMatrix();


							  glPushMatrix();
								glTranslatef(5,0,-12-6*width);
								glRotated(-90,0,1,0);
								glScaled(.5,1,.5);
								glCallList(list_wall);
							  glPopMatrix();
					  }
					  //inner left small tower
					  glPushMatrix();
						glTranslatef(0,0,0);
						glCallList(list_small_tower);
					  glPopMatrix();

					  //inner left small tower peak
					glPushMatrix();
						glTranslatef(6.5,12,-4.5);
						glScaled(2,1,2);
						glCallList(list_pyramid);
					glPopMatrix();

					//inner right medium tower
					glPushMatrix();
						glTranslatef(10,0,0);
						glScaled(1.5,1.1,1);
						glCallList(list_small_tower);
					glPopMatrix();


					//inner right medium tower peak
					glPushMatrix();
						glTranslatef(20,13,-5);
						glScaled(3.5,4,3);
						glCallList(list_pyramid);
					glPopMatrix();
					  glPushMatrix();
					    glTranslatef(19.8,13,-2);
						glScaled(6.7,1.0,10.0);
						glCallList(list_roof);
					  glPopMatrix();

					//back left tower
					glPushMatrix();
						glTranslatef(-12,0,-15);
						glScaled(2,1.5,1.5);
						glCallList(list_small_tower);
					glPopMatrix();


					//back left tower peak
					glPushMatrix();
						glTranslatef(1,18,-22);
						glScaled(4,6,4);
						glCallList(list_pyramid);
					glPopMatrix();


					//inner left medium tower
					glPushMatrix();
						glTranslatef(-12,0,-3);
						glScaled(2,1.1,1);
						glCallList(list_small_tower);
					glPopMatrix();


					//inner left medium tower peak
					glPushMatrix();
						glTranslatef(1,13,-8);
						glScaled(8,1,3);
						glCallList(list_pyramid);
					glPopMatrix();


				    //fence
				    for(int i=0; i<30;i++){
						glPushMatrix();
						glTranslatef(18+i-.1*i,0,5);
						  glRotated(180,0,1,0);
						glCallList(list_fence);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(45,0,5-i+.1*i);
						  glRotated(270,0,1,0);
						glCallList(list_fence);
						glPopMatrix();
				    }

					//floor
					glBegin(GL_QUADS);
					glColor3ub(40,80,40);
					glVertex3f(-100,0.0F,5.5F);
					glVertex3f(100,0.0F,5.5F);
					glVertex3f(100,0.0F,-100);
					glVertex3f(-100,0.0F,-100);
					
					glColor3ub(130,130,80);
					glVertex3f(-100,-3.0F,7);
					glVertex3f(100,-3.0F,7);
					glVertex3f(100,0.0F,5.5F);
					glVertex3f(-100,0.0F,5.5F);

					glColor3ub(60,100,60);
					glVertex3f(100,-2.0F,7);
					glVertex3f(-100,-2.0F,7);
					glVertex3f(-100,-2.0F,100);
					glVertex3f(100,-2.0F,100);
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

