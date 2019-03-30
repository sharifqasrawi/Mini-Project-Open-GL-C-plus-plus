#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


using namespace std;

float LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float LightDiffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float LightPosition[] = { 2.0f, 1.0f, 1.0f, 1.0f };

float move_x = -15, move_y = 0, 
	  angle_x = 0, angle_y = 0, angle_z = 0, 
	  camera_x = 0, camera_z = 0, 
	  ccpx = 0, ccpz = -1;

float default_move_x = move_x, default_move_y = move_y,
	  default_angle_x = angle_x, default_angle_y = angle_y, default_angle_z = angle_z,
	  default_camera_x = camera_x, default_camera_z = camera_z,
	  default_ccpx = ccpx, default_ccpz = ccpz;

#define TrunOnLight 111
#define TrunOffLight 222
#define ResetCamera 333


void init() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glEnable(GL_COLOR_MATERIAL);
	//Light source
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
}


//Forklift wheel
void Wheel(float x, float y, float z)
{
	glEnable(GL_DEPTH_TEST);
	GLUquadricObj *s;          	
	s = gluNewQuadric();
	gluQuadricDrawStyle(s, GLU_FILL);   

	glTranslatef(x, y, z);  //Position
	glColor3f(0.25f, 0.25f, 0.25f);
	gluPartialDisk(s, 4, 7, 220, 220, 90, 360);	//Wheel inner surface

	glColor3f(1.0f, 0, 0);
	gluPartialDisk(s, 1.5, 4, 220, 220, 90, 360);

	glColor3f(0.2f, 0.2f, 0.2f);
	gluCylinder(s, 7, 7, 7, 220, 220);  //Wheel cylinder

	glTranslatef(0.0f, 0.0f, 7.0f);
	glColor3f(0.25f, 0.25f, 0.25f);
	gluPartialDisk(s, 4, 7, 220, 220, 90, 360);	//Wheel outer surface

	glColor3f(1.0f, 0, 0);
	gluPartialDisk(s, 1.6, 4, 220, 220, 90, 360);

}

//Forklift body
void Body()
{
	glEnable(GL_DEPTH_TEST);
	glColor4f(0.8f, 0.9f, 0, 0); // Color

	//Floor
	glPushMatrix();
	glScalef(20.0f, 2.0f, 9.0f);
	glutSolidCube(2);
	glPopMatrix();

	//Sides
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 8.0f);
	glScalef(20.0f, 5.0f, 1.0f);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.0f, -8.0f);
	glScalef(20.0f, 5.0f, 1.0f);
	glutSolidCube(2);
	glPopMatrix();

	//Front
	glPushMatrix();
	glTranslatef(18.3f, 4.0f, 0.0f);
	glScalef(2.0f, 4.0f, 7.0f);
	glutSolidCube(2);
	glPopMatrix();
	
}

//Forklift back
void ForkliftBack()
{
	glEnable(GL_DEPTH_TEST);
	glColor4f(0.4f, 0.8f, 0, 0); //Color
	glScalef(2.5f, 8.0f, 15.0f); //Scaling
	glutSolidCube(2); // Draw solid cube with size of 2

	//Forklift back bottom
	glBegin(GL_QUADS);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -2.3f, 0.6f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -2.3f, -0.57f);

	glColor4f(0.3f, 0.7f, 0, 0);
	glVertex3f(1.0f, -0.99f, 1.00f);
	glVertex3f(-1.0f, -0.99f, 1.00f);
	glVertex3f(-1.0f, -2.4f, 0.6f);
	glVertex3f(1.0f, -2.4f, 0.6f);

	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -2.4f, -0.57f);
	glVertex3f(1.0f, -2.4, -0.57f);

	glVertex3f(-1.0f, -2.4f, 0.6f);
	glVertex3f(1.0f, -2.4f, 0.6f);
	glVertex3f(1.0f, -2.4f, -0.59f);
	glVertex3f(-1.0f, -2.4f, -0.59f);

	glVertex3f(-1.0f, -2.4f, -0.58f);
	glVertex3f(-1.0f, -2.4f, 0.6f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
	
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f); //Position
	glColor4f(0.3f, 0.7f, 0, 0);  //Color
	glScalef(0.1f, 1.0f, 1.0f);
	glutSolidCube(2);
	glPopMatrix();
}

//Forklift front
void ForkLiftFront()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glColor4f(0.8f, 0.9f, 0, 0); //Color
	glScalef(2.0f, 1.0f, 14.9f); //Scaling
	glutSolidCube(2); // Draw solid cube with size of 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1); //Color
	glScalef(2.0f, 0.1f, 14.9f); //Scaling
	glutSolidCube(2); // Draw solid cube with size of 2
	glPopMatrix();
}


//Forklift body side
void BodySide()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0, 0); //Color
	glScalef(20.0f, 0.5f, 3.5f); //Scaling
	glutSolidCube(2);
	glPopMatrix();

	//Upper surface
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glColor3f(0,0 ,0); //Color
	glScalef(20.0f, 0.1f, 3.5f);
	glutSolidCube(2);
	glPopMatrix();
}


//Forklift Seat 
void Seat()
{
	//Seat back
	glPushMatrix();
	glColor4f(0.9f, 0.0f, 0, 1.0f); //Color
	glRotatef(90, 0, 0, 1);   // Rotation
	glTranslatef(4.0f, 3.5f, 0.0f);
	glScalef(10, 2.0, 6.0); //Scaling
	glutSolidCube(1); // Draw solid cube with size of 1
	glPopMatrix();

	//Seat
	glPushMatrix();
	glColor4f(0.9f, 0.0f, 0, 1.0f); //Color
	glEnable(GL_DEPTH_TEST);
	glScalef(8, 2.0, 6.0);	//Scaling
	glutSolidCube(1); // Draw solid cube with size of 1
	glPopMatrix();
}


//Forklift steering wheel
void SteeringWheel()
{
	glColor4f(0.8f, 0.0f, 0, 0); // Color
	glEnable(GL_DEPTH_TEST); 
	glScalef(0.8f, 7.0f, 1.0f); //Scaling
	glutSolidCylinder(0.5, 1, 50, 50); // // Draw solid cylinder
}



//Forklift roof
void Roof()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();// Front columns
	glColor4f(0.8f, 0.8f, 0.8f, 0); //Color
	glTranslatef(11.0f, 1.0f, -21.4f); //Position
	glRotatef(28, 0, 0, 1);  // Rotation
	glScalef(0.7f, 14.0, 0.6f); //Scaling
	glutSolidCube(2);

	glTranslatef(0.0f, 0.0f, 22.0f); //Position
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix(); //roof
	glColor4f(0.8f, 0.8f, 0.8f, 0); //color
	glTranslatef(-5.5f, 13.0f, -15.0f); //Position
	glScalef(10.5f, 1.0f, 7.5f); //Scaling
	glutSolidCube(2);
	glPopMatrix();
	
	glPushMatrix(); 

	glColor4f(0.8f, 0.8f, 0.8f, 0); //Color
	glTranslatef(5.0f, 13.0f, -14.9f); //Position
	glScalef(0.6f, 1.2f, 6.8f); //Scaling

	glTranslatef(-33.6f, 0.0f, 0.0f); //Position
	glutSolidCube(2);


	glTranslatef(-12.6f, -8.0f, 0.0f); //Position
	glScalef(1.5f, 1.5f, 0.9f); //Scaling
	glRotatef(30, 0, 0, 1); //Rotation
	glutSolidCube(2);

	glPopMatrix();
	
	
	glPushMatrix(); //Rear columns
	glColor4f(0.8f, 0.8f, 0.8f, 0); //Color
	glTranslatef(-19.0f, 8.0f, -21.5f); //Position
	glRotatef(320, 0, 0, 1);  // Rotation
	glScalef(0.8f, 7.0, 0.6f); //Scaling
	glutSolidCube(2);

	glTranslatef(0.0f, 0.0f, 20.9f); //Position
	glutSolidCube(2);
	glPopMatrix();
}

//Forklift fork lifter
void ForkLifter()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glPushMatrix();// Vertical columns

	//1st column
	glScalef(4, 60, 1.0); //Scaling
	glColor4f(0.7f, 0.7f, 0, 1); //Color
	glutSolidCube(1);

	//2nd column
	glTranslatef(-5.0f, 0.0f, 0.0f); //Position
	glutSolidCube(1);

	glPopMatrix();

	glTranslatef(-8.0f, 29.5f, 0.0f); //Position
	glPushMatrix(); //Horizontal columns
	//1st column	
	glScalef(20, 1.0, 1.0); //Scaling
	glutSolidCube(1);

	//2nd column
	glTranslatef(0, -19, 0); //Position
	glutSolidCube(1);

	//3rd column
	glTranslatef(0, -19, 0); //Position
	glutSolidCube(1);

	//4th column
	glTranslatef(0, -21, 0); //Position

	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	/////Front columns
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();// Vertical columns

	//1st column
	glScalef(2, 57, 1.5); //Scaling
	glColor4f(0.8f, 0.6f, 0, 1); //Color
	glTranslatef(-0.5f, 0.0f, 0.5f); //Position
	glutSolidCube(1);

	//2nd column
	glTranslatef(-9.0f, 0.0f, 0.5f); //Position
	glutSolidCube(1);

	glPopMatrix();

	glTranslatef(-9.8f, 29.0f, 0.5f); //Position
	glPushMatrix(); //Horizontal columns
	//1st column
	glScalef(20, 1.0, 1.5);
	glutSolidCube(1);

	//2nd column
	glTranslatef(0, -19, 0);
	glutSolidCube(1);

	//3rd column
	glTranslatef(0, -19, 0);
	glutSolidCube(1);

	//4th column
	glTranslatef(0, -20, 0);

	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}


// Fork
void Fork()
{
	glEnable(GL_DEPTH_TEST);
	//Fork Holder
	glPushMatrix();
	glPushMatrix();
	glScalef(1.0f, 10.0f, 25.0f); //Scaling
	glColor4f(0.3f, 0.3f, 0.3f, 1); //Color
	glTranslatef(11.0f, 0.5f, 0.5f); //Position
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11.8f, 9, 12.5); //Position
	glScalef(1.0f, 2.0f, 25.0f); //Scaling
	glColor4f(0.2f, 0.2f, 0.2f, 1); //Color
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11.8f, 1.5f, 12.5); //Position
	glScalef(1.0f, 2.0f, 25.0f); //Scaling
	glColor4f(0.2f, 0.2f, 0.2f, 1); //Color
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//Fork
	glColor4f(0.8f, 0.0f, 0, 0); //Color
	glPushMatrix();//Front fork
	glPushMatrix(); //Horizontal part
	glBegin(GL_QUADS);
	//Fork upper surface
	glColor4f(0.1f, 0.0f, 0, 0);
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork bottom surface
	glColor4f(0.8f, 0.0f, 0, 0);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork rear surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	//Fork right surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork left surface
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);

	glEnd();
	glPopMatrix();

	glPushMatrix(); //Vertical part
	glRotatef(90, 0, 0, 1);  // Rotation
	glTranslatef(-10.5f, -11.8f, 0.0f); //Position

	glBegin(GL_QUADS);
	//Fork upper surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork bottom surface
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork rear surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	//Fork right surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork left surface
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);

	glEnd();
	glPopMatrix();

	glPopMatrix();

	glTranslatef(0.0f, 0.0f, -18.0f);
	glPushMatrix();
	glPushMatrix(); 

	glBegin(GL_QUADS);
	//Fork upper surface
	glColor4f(0.1f, 0.0f, 0, 0);
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork bottom surface
	glColor4f(0.8f, 0.0f, 0, 0);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork rear surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	//Fork right surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	glVertex3f(31.0f, -0.5f, 22.0f);
	//Fork left surface
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);
	glVertex3f(31.0f, -0.5f, 20.0f);

	glEnd();
	glPopMatrix();

	glPushMatrix(); 
	glRotatef(90, 0, 0, 1);  
	glTranslatef(-10.5f, -11.8f, 0.0f);

	glBegin(GL_QUADS);
	//Fork upper surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork bottom surface
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork rear surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	//Fork right surface
	glVertex3f(11.0f, 0.0f, 22.0f);
	glVertex3f(11.0f, -1.0f, 22.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	glVertex3f(25.0f, -0.5f, 22.0f);
	//Fork left surface
	glVertex3f(11.0f, -1.0f, 20.0f);
	glVertex3f(11.0f, 0.0f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);
	glVertex3f(25.0f, -0.5f, 20.0f);

	glEnd();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}


//Drawing function
void Display()
{
	//Settings
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glMatrixMode(GL_MODELVIEW); 	
	glLoadIdentity();
	gluLookAt(camera_x, 1, camera_z, camera_x + ccpx, 1, camera_z + ccpz, 0, 5,0);//Set camera position
	
	

	glPushMatrix();
	glTranslatef(move_x, 0, -60.0f); //Position
	glRotatef(325, 0, 1, 0);
	glRotatef((GLfloat)angle_x, 1, 0, 0); //x
	glRotatef((GLfloat)angle_y, 0, 1, 0); //y
	glRotatef((GLfloat)angle_z, 0, 0, 1); //z

	//Forklift Body
	glPushMatrix();
	glTranslatef(-1.0f, -22.0f, -15.0f);
	Body(); 
	glPopMatrix();

	//Forklift back
	glPushMatrix();
	glTranslatef(-23.0f, -5.05f, -15.0f); //Position
	ForkliftBack();  
	glPopMatrix();

	//Forklift Front
	glPushMatrix();
	glTranslatef(17.0f, -13.0f, -15.0f);
	ForkLiftFront();
	glPopMatrix();

	//Forklift side
	glPushMatrix(); //Right side
	glTranslatef(-1.0f, -12.5f, -3.5f);
	BodySide();
	glPopMatrix();

	glPushMatrix(); //Left side
	glTranslatef(-1.0f, -12.5f, -26.3f);
	BodySide();
	glPopMatrix();

	//Wheels
	glPushMatrix();
	Wheel(-10.0, -23.0, -6.0);  //Wheel 1
	Wheel(18.0, 0.0, -7.0);  //Wheel 2
	glPopMatrix();

	glPushMatrix();
	Wheel(-10.0, -23.0, -31.0);  //Wheel 4  
	Wheel(18.0, 0.0, -7.0);  //Wheel 3
	glPopMatrix();

	//Forklift Seat 
	glPushMatrix();
	glTranslatef(-5.0f, -15.0f, -15.0f);
	Seat();
	glPopMatrix();

	//Forklift steer
	glPushMatrix();
	glTranslatef(5.0f, -13.0f, -15.5f);
	SteeringWheel();
	glPopMatrix();
	
	//Forklift Roof
	glPushMatrix();
	Roof();
	glPopMatrix();

	//Fork lifter
	glPushMatrix(); 
	glTranslatef(19.0f, 6.0f, -25.0f);
	ForkLifter();
	glPopMatrix();

	//Fork
	glPushMatrix(); 
	glTranslatef(10.5f, move_y - 27.0f, -27.0f);
	Fork();
	glPopMatrix();

	
	glutSwapBuffers();
}z

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);  //Set viewport
	glMatrixMode(GL_PROJECTION);  //Set projection mode
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	gluPerspective(80, (GLfloat)w / (GLfloat)h, 0.1f, 100); //Set perspective
	glMatrixMode(GL_MODELVIEW);
}

//Keyboard keys transformations
void Keyboard(unsigned char key, int x, int y)
{
	float f = 2.0f;
	//Rotation on axis
	switch (key)
	{
	case '4':
		angle_x += 3;
		break;
	case '6':
		angle_x -= 3;
		break;
	case '8':
		angle_y += 3;
		break;
	case '2':
		angle_y -= 3;
		break;
	case '1':
		angle_z += 3;
		break;
	case '9':
		angle_z -= 3;
		break;
	case '+': //Zooming in
		camera_x += ccpx * f;
		camera_z += ccpz * f;
		break;
	case '-': //Zooming out
		camera_x -= ccpx * f;
		camera_z -= ccpz * f;
		break;
	case 27: //Exiting
		exit(0);
		break;
	}

	glutPostRedisplay();
}

//Special keys transformations
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (move_y<50)
			move_y++;
		break;
	case GLUT_KEY_DOWN:
		if (move_y>0)
			move_y--;
		break;
	case GLUT_KEY_LEFT:
		if (move_x > -70)
			move_x--;
		break;
	case GLUT_KEY_RIGHT:
		if (move_x < 30)
			move_x++;
		break;
	}

	glutPostRedisplay();
}

void Mouse(int btn)
{
	switch (btn)
	{
	case TrunOnLight:
		glEnable(GL_LIGHTING);
		break;
	case TrunOffLight:
		glDisable(GL_LIGHTING);
		break;
	case ResetCamera:
		move_x = default_move_x;
		move_y = default_move_y;
		angle_x = default_angle_x;
		angle_y = default_angle_y;
		angle_z = default_angle_z;
		camera_x = default_camera_x;
		camera_z = default_camera_z;
		ccpx = default_ccpx;
		ccpz = default_ccpz;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}


void Menu()
{
	int menu = glutCreateMenu(Mouse);
	glutAddMenuEntry("Lights On", TrunOffLight);
	glutAddMenuEntry("Lights Off", TrunOnLight);
	glutAddMenuEntry("Reset Camera", ResetCamera);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(250, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Forklift - ISE CG S16 Project");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	Menu();

	//Reading instructions from a text file
	ifstream f;
	f.open("Instructions.txt");
	if (f.fail())
		cout << "Error open instructions file." << endl;
	else
	{
		while (f.good())
			cout << (char)f.get();
	}
	f.close();


	glutMainLoop();

	return 0;
}
