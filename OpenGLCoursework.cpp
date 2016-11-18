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
#include <stdlib.h>
#include "objloader.hpp"
#include "PointLight.h"

// Global variable for current rendering mode.
char rendermode;
std::vector<std::array<float, 3>> oldVertices;
std::vector<std::array<int, 3>> faces;
std::vector<glm::vec3> vertices;
float a = 1;
float b = 0;
float camRotX = 0, camRotY = 0;
float camDist = 5;

PointLight light;

// Scene initialisation.
void InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);               // Enable smooth shading.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background.
	glClearDepth(1.0f);                    // Depth buffer setup.
	glEnable(GL_DEPTH_TEST);               // Enables depth testing.
	glDepthFunc(GL_LEQUAL);                // The type of depth testing to do.
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void idle(void)
{
	glutPostRedisplay();  // Trigger display callback.
}


void drawTriangle(std::array<glm::vec3, 3> vertices, glm::vec3 colour) {
    //Calculate face position
    glm::vec3 facePos;
    for (glm::vec3 v : vertices) {
        facePos += v;
    }
    facePos /= 3;

    glm::vec3 faceNorm = glm::normalize(glm::cross(vertices[2]-vertices[0], vertices[2]-vertices[1]));

    //Diffuse
    glm::vec3 aoi = light.position - facePos;
    float diffuseBrightness = light.intensity * glm::dot(faceNorm, glm::normalize(aoi)) / pow(glm::length(aoi), 2);

    //Specular
    //http://learnopengl.com/#!Lighting/Basic-Lighting

    //Emmissive
    float emmissiveBrightness = 0.05;

    //Calculate face colour
    float brightness = diffuseBrightness + emmissiveBrightness;
    if (brightness > 1) brightness = 1;
    colour *= light.colour;
    glColor3f(colour.r*brightness, colour.g*brightness, colour.b*brightness);

    //Draw face
    for (glm::vec3 v : vertices) {
        glVertex3f(v.x, v.y, v.z);
    }
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Set the camera.
	//gluLookAt(5.0f, 5.0f, 10.0f,
	//	0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f);

    a += 0.01;
	b += 1;
    light.position.x = 3*cos(a);
    light.position.z = 3*sin(a);

    if (camDist < 1) camDist = 1;
    gluLookAt(camDist*cos(camRotX), camDist*sin(camRotY), camDist*sin(camRotX),
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

	// TO DO: Draw a full cube rather than a square.

	// Different render modes.
	switch(rendermode) {

		case 'f': // to display faces
		{

/*
			glRotatef(b, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
            //Face 1 + opposite
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

            glVertex3f(1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);

            //Face 2 + opposite
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);

            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);

            //Face 3 + opposite
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);

            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);

			glEnd();

            glRotatef(-b, 1.0f, 1.0f, 1.0f);
            //Draw axes
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(10.0f, 0.0f, 0.0f);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 10.0f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 10.0f);

            glEnd();
            */


            //Draw loaded model

            glBegin(GL_TRIANGLES);
            //Iterate over faces
            for (std::array<int, 3> face : faces) {
                //iterate over vertices
                drawTriangle({vertices[face[0] - 1], vertices[face[1] - 1], vertices[face[2] - 1]}, {1, 1, 1});
            }
            glEnd();

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
        case 'w': camDist -= 0.1; break;  // Zoom in
        case 's': camDist += 0.1; break;  // Zoom out

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
    camRotX += (x-oldX)*0.01;
    camRotY += (y-oldY)*0.01;
    if (camRotY > 1.5) camRotY = 1.5;
    if (camRotY < -1.5) camRotY = -1.5;
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

    load_obj("/home/matt/ClionProjects/OpenGLCoursework/bunny.obj", oldVertices, faces);
    for (std::array<float, 3> vertex : oldVertices) {
        glm::vec3 v;
        v.x = vertex[0];
        v.y = vertex[1];
        v.z = vertex[2];
        vertices.push_back(v);
    }

    //Lighting
    light  = PointLight();
    light.position.y = 10;
    light.intensity = 80;

    // Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);  // For special keys
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutIdleFunc(idle);

	glutMainLoop();
}
