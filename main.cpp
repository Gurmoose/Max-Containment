//100624009
//Gurmukh Sandhu

#include "GameObject.h"

// Core Libraries (std::)
#include <iostream>
#include <string>
#include <math.h>

// 3rd Party Libraries
#include <GLUT/freeglut.h>
#include <TTK/GraphicsUtils.h>
#include <TTK/Camera.h>

// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Milliseconds per frame

// Window size
int windowWidth = 800;
int windowHeight = 600;

// Angle conversions conversions
const float degToRad = 3.14159f / 180.0f;
const float radToDeg = 180.0f / 3.14159f;

float deltaTime = 0.0f; // amount of time since last update (set every frame in timer callback)

float rotationSpeedModifier = 10.0f;

// Mouse position in pixels
glm::vec3 mousePosition; // x,y,0

TTK::Camera camera;

GameObject object1;
// TODO: create a second game object
GameObject object2;

GameObject* activeObject; // This is initialized to object1

// This is where we draw stuff
void DisplayCallbackFunction(void)
{
	// Set up scene
	TTK::Graphics::SetBackgroundColour(0.5f, 0.5f, 0.5f);
	TTK::Graphics::ClearScreen();
	TTK::Graphics::SetCameraMode3D(windowWidth, windowHeight);
	camera.update();
	TTK::Graphics::DrawGrid();

	// Update the activeObject's rotation
	float ang = activeObject->getRotationAngleY();
	ang += deltaTime * rotationSpeedModifier;
	activeObject->setRotationAngleY(ang);
	
	// TODO: update the activeObject's scale

		
	// Update the transformation
	object1.update(deltaTime);


	// Draw the object
	object1.draw();


	// Update the second game object
	// ...
	object2.update(deltaTime);
	
	// Draw the second game object
	// ...
	object2.draw();
	object2.colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	// Swap buffers
	// This is how we tell the program to put the things we just drew on the screen
	glutSwapBuffers();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	// TODO: move the x and z locations of the active game object when the appropriate key is pressed

	switch (key)
	{
	case 27: // the escape key
		glutExit();
		break;

	case 'w':
	case 'W':
	// TODO: update activeObject->position.x
		activeObject->setPosition(activeObject->getPosition() + (glm::vec3(0.0f, 0.0f, -1.0f)));
		break;

	case 'a':
	case 'A':
		// TODO: update activeObject->position.z		
		activeObject->setPosition(activeObject->getPosition() + (glm::vec3(-1.0f, 0.0f, 0.0f)));
		break;
	case 's':	
	case 'S':
		// TODO: update activeObject->position.x
		activeObject->setPosition(activeObject->getPosition() + (glm::vec3(0.0f, 0.0f, 1.0f)));
		break;

	case 'd':
	case 'D':
		// TODO: update activeObject->position.z		
		activeObject->setPosition(activeObject->getPosition() + (glm::vec3(1.0f, 0.0f, 0.0f)));
		break;


	case 'q': // the 'q' key
	case 'Q':
		// ...
		break;
	}
}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': // the 'q' key
	case 'Q':
		// ...
		break;

	case ' ':

		// TODO: Update logic to change 'activeObject' here
		if (activeObject == &object1) {
			activeObject = &object2;

		}
		else
			activeObject = &object1;

		break;
	default:
		break;
	}
}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	// Calculate the amount of time since the last frame
	static int elapsedTimeAtLastTick = 0;
	int totalElapsedTime = glutGet(GLUT_ELAPSED_TIME);

	deltaTime = (float)totalElapsedTime - elapsedTimeAtLastTick;
	deltaTime /= 1000.0f;
	elapsedTimeAtLastTick = totalElapsedTime;

	// Re-trigger the display event
	glutPostRedisplay();

	/* this call gives it a proper frame delay to hit our target FPS */
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	/* Update our Window Properties */
	windowWidth = w;
	windowHeight = h;
}

// This is called when a mouse button is clicked
void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void SpecialInputCallbackFunction(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		// ...
		break;
	case GLUT_KEY_DOWN:
		// ...
		break;
	case GLUT_KEY_LEFT:
		// ...
		break;
	case GLUT_KEY_RIGHT:
		// ...
		break;
	}
}

// Called when the mouse is clicked and moves
void MouseMotionCallbackFunction(int x, int y)
{
	if (mousePosition.length() > 0)
		camera.processMouseMotion(x, y, mousePosition.x, mousePosition.y, deltaTime);

	mousePosition.x = x;
	mousePosition.y = y;
}

// Called when the mouse is moved inside the window
void MousePassiveMotionCallbackFunction(int x, int y)
{
}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	// Memory Leak Detection
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/* initialize the window and OpenGL properly */

	// Request an OpenGL 4.4 compatibility
	// A compatibility context is needed to use the provided rendering utilities 
	// which are written in OpenGL 1.1
	glutInitContextVersion(4, 4); 
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Tutorial");

	auto s = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << s << std::endl;

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);
	glutSpecialFunc(SpecialInputCallbackFunction);

	// Init GL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* Start Game Loop */
	deltaTime = (float)glutGet(GLUT_ELAPSED_TIME);
	deltaTime /= 1000.0f;

	activeObject = &object1;

	glutMainLoop();

	return 0;
}