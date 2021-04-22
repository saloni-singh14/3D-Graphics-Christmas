#include <iostream>
#include <math.h>
#include <string.h>

#include <GL/glut.h>
#include "src/chair.h"
#include "src/table.h"
#include "src/window.h"
#include "src/snowman.h"


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

using namespace std;

// angle of rotation for the camera direction
float angle = 0.0, yAngle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
//up vector for camera
float ux = 0.0f, uy = 1.0f, uz = 0.0f;
//left vector for camera
float camleftx = uy * lz - uz * ly, camlefty = lx * uz - ux * lz, camleftz = ux * ly - lx * uy;
// XYZ position of the camera
float x = -5.0f, z = 35.0f, y = 1.0f;;
float roll = 0.0f;

float yawangle = 0.0f;
float pitchangle = 0.0f;
float rollangle = 0.0f;

//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

float M_PI = 0;
void drawTree() {
	/// <summary>
	/// Draws the trunk of the pine tree using cylinder, the foliage using cone, and torus for decoration. We use built in Cylinder drawing and cone drawing functions for this.
	/// Uses matrix stack operations to scale and translate according to our needs.
	/// </summary>
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(160 / 255.0f, 82 / 255.0f, 45 / 255.0f);
	gluCylinder(gluNewQuadric(), 0.3, 0.2, 1, 20, 20);
	glTranslatef(0, 0, 1);
	glColor3f(50 / 255.0f, 205 / 255.0f, 50 / 255.0f);
	glutSolidCone(0.5, 2, 20, 20);


	glPopMatrix();

}
void drawSnow()
{
	/// Draws a white snow floor using a quadrilateral
	//draw snow
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
}
void drawFloor()
{
	/// <summary>
	/// Draws the floor of the house using quadrilateral and the tiles using lines
	/// </summary>
	glColor3f(76 / 255.0f, 140.0f / 255.0f, 20.0f / 255.0f);
	glPushMatrix();
	glTranslatef(0, 0.01f, 0);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glPopMatrix();
	glEnd();
	////Floor pattern
	glColor3f(0.149f, 0.149f, 0.149f);
	glLineWidth(3.0f);
	for (int i = 0; i < 20; i += 2)
	{
		glBegin(GL_LINES);
		glVertex3f(-10.0f + i, 0.001f, -10.01f);
		glVertex3f(-10.0f + i, 0.001f, 10.01f);
		glEnd();
	}
	for (int i = 0; i < 20; i += 2)
	{
		glBegin(GL_LINES);
		glVertex3f(-10.0f, 0.001f, -10.01f + i);
		glVertex3f(10.0f, 0.001f, -10.01f + i);
		glEnd();
	}

}
void drawWalls()
{
	///
	///We draw the walls using quadrilaterals
	/// 

	//   //wall
	glColor3f(226 / 255.0f, 42 / 255.0f, 41 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	////wall
	glColor3f(255 / 255.0f, 165 / 255.0f, 32 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();
	////wall
	glColor3f(255 / 255.0f, 165 / 255.0f, 32 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();


	////wall with door
	glColor3f(255 / 255.0f, 165 / 255.0f, 32 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();

	glColor3f(255 / 255.0f, 165 / 255.0f, 32 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	glColor3f(255 / 255.0f, 165 / 255.0f, 32 / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();

	glColor3f(128 / 255.0f, 0 / 255.0f, 0 / 255.0f);
	glLineWidth(30.0f);
	glBegin(GL_LINES);
	glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-6.0f, 0.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-3.0f, 0.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();
}
void drawTableset()
{
	///Here we draw a a set of chairs with a table and a teapot.
	/// For drawing the teapot, we used the inbuilt teapot function of GLUT
	/// We use drawChair() function of Chair class. We arrange according to our needs by using matrix stack operations and
	/// Rotate and translate functions of GLUT

	//Draw Table Set
	Chair chair;
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-5.0f, 0, 10.0f);
	
	glPushMatrix();
	glTranslatef(6.0f, 1.0f, -9.0f);
	glScalef(0.32f, 0.32f, 0.32f);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	chair.drawChair();//chair1
	glPopMatrix();

	//Chair studentChair1;
	glPushMatrix();
	glTranslatef(4.0f, 1.0f, -8.6f);
	glScalef(0.32f, 0.32f, 0.32f);
	glRotatef(60.0f, 0, 1, 0);
	chair.drawChair();//chair 2

	glTranslatef(0.0f, 0.0f, 12.0f);
	glRotatef(-180.0f, 0, 1, 0);
	chair.drawChair();//chair 3
	glPopMatrix();

	// Draw prof's table
	Table table;
	glPushMatrix();
	glTranslatef(6.0f, 1.4f, -7.6f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	table.drawTable();
	//glPopMatrix();

	//Draw Teapot
	//glPushMatrix();
	glColor3f(0, 204 / 255.0f, 163 / 255.0f);
	glTranslatef(-1.05f, 0.6f, 0);
	glutSolidTeapot(0.5f);
	glPopMatrix();
	glPopMatrix();
}
void drawWindows()
{
	///We draw windows using drawWindow1() and drawWindow2() of the Window class.
	///We translate, scale, and rotate according to our needs.
	/// Here, I have rotated the matrix by 90 degrees each time while drawing windows on opposite walls.



	//windows
	Window w;
	//left window 1
	w.drawWindow1();

	//right window 1
	glPushMatrix();
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	w.drawWindow1();
	glPopMatrix();

	//left window 2
	w.drawWindow2();

	//right window2
	glPushMatrix();
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	w.drawWindow2();
	glPopMatrix();

	//left window1 sill
	w.drawWindowSill();

	//right window sills
	glPushMatrix();
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	w.drawWindowSill();
	glTranslatef(0, 0, 8);
	w.drawWindowSill();
	glPopMatrix();

	//left window2 sill
	w.drawWindow2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 8.0f);
	w.drawWindowSill();
	glPopMatrix();
}
void drawsnowman()
{
	/// <summary>
	/// We call drawSnowMan() function from the Snowman class. We translate and scale according to our needs
	/// </summary>
	glPushMatrix();
	Snowman snowmanone;
	glTranslatef(5, 0, 20);
	glScalef(2.6, 2.6, 2.6);
	snowmanone.drawSnowMan();
	glPopMatrix();
}
void drawroof()
{
	/// <summary>
	/// We make a pyramid using 4 triangles to build a roof for the house.
	/// </summary>
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);  // Move left and into the screen

	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	   // Front
	glColor3f(179.0f/255.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(-12.0f, 0.0f, -12.0f);
	glVertex3f(12.0f, 0.0f, -12.0f);

	// Right
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(12.0f, 0.0f, -12.0f);
	glVertex3f(12.0f, 0.0f, 12.0f);

	// Back
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(-12.0f, 0.0f, 12.0f);
	glVertex3f(12.0f, 0.0f, 12.0f);

	// Left
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(-12.0f, 0.0f, 12.0f);
	glVertex3f(-12.0f, 0.0f, -12.0f);

	glEnd();   // Done drawing the pyramid
	glPopMatrix();
}
void WoodsbehindHouse()
{
	/// <summary>
	/// Uses a loop to draw a whole forest of trees. We vary the x position and y position in each
	/// iteration to make the forest look natural. @see drawTree();
	/// </summary>
	glPushMatrix();
	glTranslatef(0, 0, -10);
	for (int j = 0; j < 4; j++) {
		for (int i = -10; i < 10; i++) {
			//	glPopMatrix();
			glPushMatrix();
			glTranslatef(11 - 2 * j, 0, -44 - 2 * j);
			glTranslatef(i * 5, 0, 0);
			glScaled(3.5, 3.5, 3.5);
			drawTree();

			glPopMatrix();
		}
	}


	glPopMatrix();
}
void drawChristmasTree() {
	
	/// Christmas tree ith red decoration using torus. Uses matrix stack operations to scale and translate according to our needs.
	/// @see drawTree()
	/// 
	glPushMatrix();
	glTranslatef(-7, 0, -7);
	glRotatef(-90, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(51 / 255.0f, 0 * 0.7 / 255.0f, 0 * 0.7 / 255.0f);
	gluCylinder(gluNewQuadric(), 0.3, 0.2, 1, 20, 20);

	//green foliage using cone
	glTranslatef(0, 0, 1);
	glColor3f(50 / 255.0f, 255 / 255.0f, 50 / 255.0f);
	glutSolidCone(0.5, 2, 20, 20);
	glPopMatrix();

	//red decoration on top of the tree
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glTranslatef(-7, 1.5 * 3, -7);
	glutSolidTorus(0.1, 0.005, 20, 20);
	glPopMatrix();

}
void drawCarpet() {
	/// <summary>
	/// Draws a circular carpet.
	/// Uses matrix stack operations to scale, translate, and rotate according to our needs.
	/// </summary>
	glPushMatrix();
	glColor3f(0.5, 0, 0);
	glTranslatef(-1.2f, 0.15, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(4, 0.1, 100, 100);
	glPopMatrix();

}
void drawGifts() {
	/// <summary>
	/// Uses built in cube drawing function to draw the gifts. Uses matrix stack operations to scale and translate according to our needs.
	/// </summary>
	glColor3f(1, 0 / 255, 0 / 255);
	glPushMatrix();
	glTranslatef(-7, 0.25, -6.3);
	glutSolidCube(0.5);
	glTranslatef(1, 0, 0);
	glRotated(45, 0, 1, 0);
	glColor3f(1, 204.0f / 255, 0);
	glutSolidCube(0.75);
	glPopMatrix();
}
void drawMoon()
{
	/// <summary>
	/// Uses built in solid sphere function to draw the moon. Uses matrix stack operations to scale and translate according to our needs.
	/// </summary>
	glPushMatrix();
	glTranslated(-30, 20, -30);
	glColor3f(1, 1, 1);
	glutSolidSphere(7, 100, 100);
	glPopMatrix();
}
void treesbesideHouse()
{
	/// <summary>
	/// Draws a clump of trees besides the house. Uses matrix stack operations to scale and translate according to our needs. 
	/// @see drawTree()
	/// </summary>
	glPushMatrix();
	glTranslatef(-10, 0, 12);
	glScaled(3.5, 3.5, 3.5);
	glTranslatef(-2, 0, -2);
	drawTree();
	glTranslated(-1, 0, 1);
	drawTree();
	glTranslatef(1, 0, 1);
	drawTree();
	glPopMatrix();
}
void renderScene(void) {

	///Creates the entire scene using different functions. We first set the position of the eye point and the position of the reference point using gluLookAt function. 
	///We use different matrix stack and transformation operations operations to render the scene. Push matrix function creates a copy of the new matrix and pushes it to the stack. All operations, such as rotation, scaling, translation of matrix are performed on this matrix. 
	/// After that, the copy is popped and the original matrix is unaffected
	/// Every time the scene is rendered we set the position and perspective of camera
	/// Camera movements are triggered by mouse and keyboard movements using processSpecialKeys(), processNormalKeys() and processMouseMovement() functions 
	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 2.5f, z,
		x + lx, 2.5f + ly, z + lz,
		roll + 0.0f, 2.5f, 0.0f);

	//camera movements
	glRotatef(yawangle, ux, uy, uz);
	camleftx = uy * lz - uz * ly;
	camlefty = lx * uz - ux * lz;
	camleftz = ux * ly - lx * uy;
	glTranslated(x, y, z);
	glRotatef(pitchangle, camleftx, camlefty, camleftz);
	glTranslated(-x, -y, -z);
	glRotatef(rollangle, lx, ly, lz);

	//Creation of christmas scene
	drawSnow();
	drawFloor();
	drawroof();
	drawWalls();
	drawTableset();
	drawWindows();
	drawsnowman();
	WoodsbehindHouse();
	drawChristmasTree();
	drawCarpet();
	drawGifts();
	drawMoon();
	treesbesideHouse();


	if(abs(mouseX) > 0.3){
		angle -= (0.004f * mouseX);
		lx = sin(angle);
		lz = -cos(angle);
	}
	if(abs(mouseY) > 0.3){
		if(abs(yAngle) < (M_PI/2)){
			yAngle += (0.002f * mouseY);
		}
		ly = sin(yAngle);
	}

	glutSwapBuffers();

/// @see drawSnow();
///	@see drawFloor();
///	@see drawroof();
///	@see drawWalls();
///	@see drawTableset();
///	@see drawWindows();
///	@see drawsnowman();
///	@see WoodsbehindHouse();
///	@see drawChristmasTree();
///	@see drawCarpet();
///	@see drawGifts();
///	@see drawMoon();
///	@see treesbesideHouse();
}
void processSpecialKeys(int key, int xx, int yy) {
	///Handles the events triggered when certain keys on the keyboard are pressed.
///Specifically, handles left arrow key,right arrow key,up arrow key,down arrow key, pg up,pg dn.
/// Moves the camera forward, backward and sideways. We use a switch case for which key is pressed. On the basis of that 
/// 	we vary the coordinates of the camera and its direction.
/// 	Pg up and pg dn keys help in pitching camera movements.
/// 	Arrow keys help in moving in different directions
///@param key : key pressed
///@param xx : x coordinate of mouse position
///@param yy : y coordinate of mouse position

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		x += sin(angle - M_PI / 2.0) * fraction;
		z += -cos(angle - M_PI / 2.0) * fraction;
		break;
	case GLUT_KEY_RIGHT:
		x += sin(M_PI / 2.0 + angle) * fraction;
		z += -cos(M_PI / 2.0 + angle) * fraction;
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;

	case GLUT_KEY_PAGE_UP:
		pitchangle += 0.5f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		pitchangle -= 0.5f;
		break;
	}

}
void processNormalKeys(unsigned char key, int xx, int yy) {
	///Handles the events triggered when any key on the keyboard is pressed.
///Specifically, handles w,a,s,d,x,z.
/// Moves the camera forward, backward, sideways.  We use a switch case for which key is pressed. On the basis of that 
/// 	we vary the coordinates of the camera and its direction using trignometric functions.
/// 	z and x keys help in rolling camera movements
/// 	w: helps in zooming in
/// 	a: helps in panning left
///  	s: helps in zooming out
/// 	d: helps in panning right
///@param key : key pressed
///@param xx : x coordinate of mouse position
///@param yy : y coordinate of mouse position
	float fraction = 0.1f;
	camleftx = uy * lz - uz * ly;
	camlefty = lx * uz - ux * lz;
	camleftz = ux * ly - lx * uy;
	if (key == 'w') {
		x += lx * fraction;
		z += lz * fraction;
	}
	else if (key == 'd') {
		x -= camleftx * fraction;
		z -= camleftz * fraction;
	}
	else if (key == 's') {
		x -= lx * fraction;
		z -= lz * fraction;
	}
	else if (key == 'a') {
		x += camleftx * fraction;
		z += camleftz * fraction;
	}
	else if (key == 'x') {
		roll += 0.5f;
	}
	else if (key == 'z') {
		roll -= 0.5f;
	}

	if (key == 27)
		exit(0);
}
void processMouseMovement(int xx, int yy){
	/// <summary>
	/// Handles the events triggered when the mouse is moved in the window area. Changes the direction of the perspective
	/// Handles yaw of the camera.
	/// </summary>
	/// @param xx : x coordinate of mouse position
	/// @param yy : y coordinate of mouse position

	mouseX = (float)(halfWidth - xx)/halfWidth;
	mouseY = (float)(halfHeight - yy)/halfHeight;
	angle -= (0.005f * mouseX);
	lx = sin(angle);
	lz = -cos(angle);

	if(abs(yAngle) < (M_PI/2)){
		yAngle += (0.005f * mouseY);
	}
	ly = sin(yAngle);

}
void changeSize(int w, int h) {

	/// <summary>
	/// Adjusts the viewport size when the window size is changed and sets the projection accordingly.
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>

	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();
	

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	halfWidth = (float)(w/2.0);
	halfHeight = (float)(h/2.0);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
void animate () {
	///refreshes screen
    /* refresh screen */
    glutPostRedisplay();
}
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Christmas Scene");

	// register callbacks
	glutDisplayFunc(renderScene);
	//Adjusts the perspective of the camera according to the size of the window
	glutReshapeFunc(changeSize);
	glutIdleFunc(animate);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
    glutPassiveMotionFunc(processMouseMovement);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}