#ifdef __APPLE__
#include <OpenGL/gl.h>  // The GL header file.
#include <GLUT/glut.h>  // The GL Utility Toolkit (glut) header.
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>      // The GL header file.
#include <GL/glut.h>       // The GL Utility Toolkit (glut) header (boundled with this program).
#endif

#include <math.h>
#include "objloader.hpp"
#include "PointLight.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "Cube.h"

// Global variable for current rendering mode.
char rendermode;
std::vector<std::array<float, 3>> oldVertices;
std::vector<std::array<int, 3>> faces;
std::vector<glm::vec3> vertices;
float a = 1;
float camRotX = 0, camRotY = 0;
float camDist = 5;
float theta = 0, phi = 3.14f / 2;

PointLight light;
Camera camera;
Scene scene;

// Scene initialisation.
void InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);               // Enable smooth shading.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background.
	glClearDepth(1.0f);                    // Depth buffer setup.
	glEnable(GL_DEPTH_TEST);               // Enables depth testing.
	glDepthFunc(GL_LEQUAL);                // The type of depth testing to do.
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}


void idle(void)
{
	glutPostRedisplay();  // Trigger display callback.
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

    //Rotate light
    a += 0.01;
    light.position.x = 20 * cos(a);
    light.position.z = 20 * sin(a);

    //Control camera with mouse
    if (camDist < 1) camDist = 1;
    //camera.position = {camDist * cos(camRotX) * sin(camRotY), camDist * (cos(camRotY)), camDist * sin(camRotX) * sin(camRotY)};

	// Different render modes.
	switch(rendermode) {

		case 'f': // to display faces
		{
            scene.render();
			break;
		}

		case 'v': // to display points
		{
			glBegin(GL_POINTS);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glEnd();

			glPointSize(5);
			break;
		}

		case 'e': // to display edges
		{
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 1.0f);

			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);

			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);

			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);

			glEnd();
			break;
		}
	}

	// TO DO: Draw Cartesian coordinate system as lines.

	glutSwapBuffers();
}


// The reshape function sets up the viewport and projection.
void reshape(int width, int height)
{
	// Prevent a divide by zero error by making height equal to 1
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Need to calculate the aspect ratio of the window for gluPerspective.
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	// Return to ModelView mode for future operations.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// Callback for standard keyboard presses.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Exit the program when escape is pressed
		case 27:
			exit(0);
			break;

			// Switch render mode.
		case 'v': rendermode = 'v'; break;  // vertices
		case 'e': rendermode = 'e'; break;  // edges
		case 'f': rendermode = 'f'; break;  // faces
        case 'w':
            camera.position += camera.direction * 0.1f;
            break;  // Move forward
        case 's':
            camera.position -= camera.direction * 0.1f;
            break;  // Move backward
        case 'a':
            camera.position -= camera.right * 0.1f;
            break;  // Move left
        case 'd':
            camera.position += camera.right * 0.1f;
            break;  // Move right

		default:
			break;
	}

	glutPostRedisplay();
}


// Arrow keys need to be handled in a separate function from other keyboard presses.
void arrow_keys(int a_keys, int x, int y)
{
	switch (a_keys)
	{
		case GLUT_KEY_UP:
			glutFullScreen();
			break;

		case GLUT_KEY_DOWN:
			glutReshapeWindow(500, 500);
			break;

		default:
			break;
	}
}

// Handling mouse button event.
void mouseButton(int button, int state, int x, int y)
{
}

int oldX = -1, oldY = -1;
// Handling mouse move events.
void mouseMove(int x, int y)
{
    theta += (x - oldX) * 0.005;
    phi += (y - oldY) * 0.005;
    if (phi > 3.14) phi = 3.14;
    if (phi < 0.01) phi = 0.01;
    camera.direction = {sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta)};
    camera.right = -glm::cross(camera.up, camera.direction);
    oldX = x;
    oldY = y;
}


// Note: You may wish to add interactivity like clicking and dragging to move the camera.
//       In that case, please use the above functions.


// Entry point to the application.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CM20219 OpenGL Coursework");
	glutFullScreen();  // Uncomment to start in full screen.
	InitGL();
	rendermode = 'f';

    //Lighting
    light = PointLight();
    light.position.y = 2;
    light.intensity = 300;
    light.colour = {1, 0.5, 0.5};

    //Camera
    camera.center = {0, 0, 0};
    camera.up = {0, 1, 0};
    camera.position = {0, 0, 0};

    //Bunny
    Mesh bunny = Mesh("/home/matt/ClionProjects/OpenGLCoursework/bunny.obj");
    ObjectInstance bunnyInst = ObjectInstance(&bunny);
    bunnyInst.loadTexture("/home/matt/ClionProjects/OpenGLCoursework/textures/water.bmp");

    //Screwdriver
    Mesh screwdriver = Mesh("/home/matt/ClionProjects/OpenGLCoursework/screwdriver.obj");
    ObjectInstance screwdriverInst = ObjectInstance(&screwdriver);
    screwdriverInst.loadTexture("/home/matt/ClionProjects/OpenGLCoursework/textures/wood.bmp");

    //Cube
    Cube cube;
    ObjectInstance cubeInst = ObjectInstance(&cube);
    cubeInst.loadTexture("/home/matt/ClionProjects/OpenGLCoursework/textures/wood.bmp");

    //Scene
    scene.camera = &camera;
    scene.light = &light;
    scene.objectInstances.push_back(&screwdriverInst);
    scene.objectInstances.push_back(&cubeInst);

    // Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);  // For special keys
	glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);
	glutIdleFunc(idle);

	glutMainLoop();
}
