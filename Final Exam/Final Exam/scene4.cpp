
/*
 *
 * Dante Zitello
 *
 * Program 4:
 *
 * Texture loading sources from book experiments
 * Fog code also sources from book experiments
 *
 * I used  a different transparency method from the book
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
#include "getbmp.h"
#pragma comment(lib, "glew32.lib")
#endif


using namespace std;

float rotateAngle = 0.0f;
static unsigned int texture[1]; // Array of texture indices.

static int fogMode = GL_EXP; // Fog mode.
static float fogDensity = 0.1; // Fog density.
static float fogStart = 0.0; // Fog start z value.
static float fogEnd = 20.0; // Fog end z value.

/*Load a texture. Sources from book experiments.*/
void loadTexture(void) {
	BitMapFile* bmpf = getbmp("snow.bmp");
	
	// Bind can label image to texture index[0]. 
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmpf->sizeX, bmpf->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, bmpf->data);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

}

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

   //only enable floor light
   //glEnable(GL_LIGHT0);
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
  // glDisable(GL_LIGHT0);
}

void drawSnowman(void) {
	float cubeSize = 2.0f;
	float sphereBaseSize = 1.25f;
	float sphereBodySize = sphereBaseSize - 0.25f;
	float sphereHeadSize = sphereBodySize - 0.25f;
	
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
		
		glPushMatrix();
			glColor3f(102.0f / 255.0f, 102.0f / 255.0f, 102.0f / 255.0f);
			glScalef(2.0, 1.0, 2.0);
			glTranslatef(0.0, cubeSize / 2, 0.0);
			glutSolidCube(cubeSize);
		glPopMatrix();
		

		
		//Draw base
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereBaseSize, 64, 64);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		
		//Draw body
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize + sphereBaseSize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereBodySize, 64, 64);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//Draw head
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, cubeSize + sphereBaseSize + sphereBodySize, 0.0);
			glScalef(1.2f, 0.9f, 1.2f);
			glutSolidSphere(sphereHeadSize, 64, 64);
			glDisable(GL_TEXTURE_2D);
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

void drawGlassBox(void) {


	glPushMatrix();
		glTranslatef(0.0, 0.0, 5.0);
		glBegin(GL_POLYGON);
			glColor4f(1.0, 0.0, 0.0, 0.5);
			glVertex3f(5.0, 0.0, 0.0);
			glVertex3f(5.0, 6.0, 0.0);
			glVertex3f(-5.0, 6.0, 0.0);
			glVertex3f(-5.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, 5.0);
		glBegin(GL_POLYGON);
			glColor4f(0.0, 1.0, 1.0, 0.5);
			glVertex3f(5.0, 0.0, 0.0);
			glVertex3f(5.0, 6.0, 0.0);
			glVertex3f(-5.0, 6.0, 0.0);
			glVertex3f(-5.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -5.0);
		glBegin(GL_POLYGON);
			glColor4f(0.0, 1.0, 0.0, 0.5);
			glVertex3f(5.0, 0.0, 0.0);
			glVertex3f(5.0, 6.0, 0.0);
			glVertex3f(-5.0, 6.0, 0.0);
			glVertex3f(-5.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, -5.0);
		glBegin(GL_POLYGON);
			glColor4f(0.0, 0.0, 1.0, 0.5);
			glVertex3f(5.0, 0.0, 0.0);
			glVertex3f(5.0, 6.0, 0.0);
			glVertex3f(-5.0, 6.0, 0.0);
			glVertex3f(-5.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();


}

// Initialization routine.
void setup(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glEnable(GL_DEPTH_TEST); // Enable depth testing.

   // Turn on OpenGL lighting.
   glEnable(GL_LIGHTING);


   float lightAmb0[] = { 0.0, 0.0, 0.0, 1.0 };
   float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
   float lightPos0[] = { 0.0, 1.0, 0.0, 0.0 }; // Overhead directional light source (e.g., sun).
   float spotDirection0[] = { 0.0, 0.0, 1.0f };

   // Light properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection0);

   glEnable(GL_LIGHT0); // Enable particular light source.


   //Directional over shoulder light
   float lightAmb1[] = { 0.0, 0.0, 0.0, 1.0 };
   float lightDifAndSpec1[] = { 0.9, 1.0, 0.7, 1.0 };
   float lightPos1[] = { -1.0, -11.0, 5.0, 0.0 }; // Overhead directional light source (e.g., sun).
   float spotDirection1[] = { 0.0, 0.0, 1.0f };

   // Light properties.
   glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
   glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);

   glEnable(GL_LIGHT1); // Enable particular light source.

   // Light property vectors.
  
   float globAmb[] = { 0.4, 0.4, 0.42 , 1.0 };

   
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

   glEnable(GL_BLEND); // Enable blending.
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Specify blending parameters.
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   //glEnable(GL_POLYGON_SMOOTH);


   // Cull back faces.
 // glEnable(GL_CULL_FACE);
 // glCullFace(GL_BACK);

   loadTexture();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Material property vectors.
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// Enable color material mode.
	glEnable(GL_COLOR_MATERIAL);
	

	
	
	
	float fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, fogMode);
	glFogf(GL_FOG_START, fogStart);
	glFogf(GL_FOG_END, fogEnd);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glHint(GL_FOG_HINT, GL_NICEST);

   glLoadIdentity();
   gluLookAt(0.0, 11.0, 5.0, // eye location
		   0.0, 0.0, 0.0, 	// look at point
		   0.0, 1.0, 0.0);  // up vector


   
   //drawOriginMarkers();
   glRotatef(rotateAngle, 0.0, 1.0, 0.0);
   glTranslatef(0.0f, 0.0f, -6.0f);
   drawCheckeredFloor(); // Draw the floor first.
   drawSnowman();
   drawGlassBox();

   glLoadIdentity();
   glDisable(GL_FOG);
   

   

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

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		rotateAngle = (rotateAngle >= 360) ? 0 : rotateAngle + 1.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
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
   glutCreateWindow("final4");
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup();

   printf("Press R to rotate");

   glutMainLoop();
}
