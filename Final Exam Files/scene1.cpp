
/*
 * Dante Zitello
 * Program 1
 *
 *
 */

#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
//#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif


using namespace std;

//Draw origin markers
void drawOriginMarkers(void) {
	glPushMatrix();
	// This code is just to orient you in the scene and should be removed
	glTranslatef(0, 0.01, 0); // slight vertical offset to make sure lines are visible
	glColor3f(0, 1, 1); // cyan cone points toward pos-z
	glutWireCone(2, 5, 10, 20);
	glColor3f(0, 1, 0); // green cone points toward pos-x
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glutWireCone(2, 5, 10, 20);
	glPopMatrix();
	glColor3f(1, 0, 0); // red cone points toward pos-y
	glRotatef(270, 1, 0, 0);
	glutWireCone(5, 7, 10, 10);
	// End of orienting code to be removed
	glPopMatrix();
}

// Draw checkered floor.
void drawCheckeredFloor(void)
{
   glShadeModel(GL_FLAT); // Flat shading to get the checkered pattern.
   int i = 0;

   glPushMatrix();
	   for(float z = 50.0; z > -50.0; z -= 5.0)
	   {
		  glBegin(GL_TRIANGLE_STRIP);
		  for(float x = -50.0; x < 50.0; x += 5.0)
		  {
			 if (i % 2) glColor3f(0.0, 0.0, 0.0);
			 else glColor3f(1.0, 1.0, 1.0);
			 glNormal3f(0.0, 1.0, 0.0);
			 glVertex3f(x, 0.0, z - 5.0);
			 glVertex3f(x, 0.0, z);
			 i++;
		  }
		  glEnd();
		  i++;
	   }
   glPopMatrix();
}

void drawSnowman(void) {
	float cubeSize = 2.0f;
	float sphereBaseSize = 1.25f;
	float sphereBodySize = sphereBaseSize - 0.25f;
	float sphereHeadSize = sphereBodySize - 0.25f;
	
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -6.0f);
		glPushMatrix();
			glColor3f(102.0f / 255.0f, 102.0f / 255.0f, 102.0f / 255.0f);
			glScalef(2.0, 1.0, 2.0);
			glTranslatef(0.0, cubeSize / 2, 0.0);
			glutSolidCube(cubeSize);
		glPopMatrix();
	
		//Draw base
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereBaseSize, 64, 64);
		glPopMatrix();

		//Draw body
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize + sphereBaseSize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereBodySize, 64, 64);
		glPopMatrix();

		//Draw head
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize + sphereBaseSize + sphereBodySize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereHeadSize, 64, 64);
		glPopMatrix();

		//Draw carrot
		glPushMatrix();
			glColor3f(255.0f / 255.0f, 163.0f / 255.0f, 26.0f / 255.0f);
			glTranslatef(0.0, cubeSize + sphereBaseSize + sphereBodySize, sphereHeadSize);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidCone(sphereHeadSize / 5.0, sphereHeadSize / 2.0, 64, 64);
		glPopMatrix();

	glPopMatrix();
}

// Initialization routine.
void setup(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glEnable(GL_DEPTH_TEST); // Enable depth testing.

   // Turn on OpenGL lighting.
   glEnable(GL_LIGHTING);

   // Light property vectors.
  
   float globAmb[] = { 0.4, 0.4, 0.4, 1.0 };

   
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Material property vectors.
   float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };

   // Material properties.
   glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

   // Enable color material mode.
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

   // Cull back faces.
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
}

// Drawing routine.
void drawScene(void)
{
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.0, 0.0, 0.0 }; // Overhead directional light source (e.g., sun).
	
	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   gluLookAt(0.0, 11.0, 5.0, // eye location
		   0.0, 0.0, 0.0, 	// look at point
		   0.0, 1.0, 0.0);  // up vector

   //drawOriginMarkers();
   drawCheckeredFloor(); // Draw the floor first.
   drawSnowman();


   

   glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0, 1.0, 5.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv)
{
   glutInit(&argc, argv);

   glutInitContextVersion(4, 0);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("final1");
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);

   glewExperimental = GL_TRUE;
   glewInit();

   setup();

   glutMainLoop();
}
