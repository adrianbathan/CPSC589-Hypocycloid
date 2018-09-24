#include "InputHandler.h"

RenderEngine* InputHandler::renderEngine;
int InputHandler::mouseOldX;
int InputHandler::mouseOldY;

// Must be called before processing any GLFW events
void InputHandler::setUp(RenderEngine* renderEngine) {
	InputHandler::renderEngine = renderEngine;
}

// Callback for key presses
void InputHandler::key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE) {
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(0);
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT) && !pause)
		if (speed < 1.0f)
			speed += 0.01f;
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT) && !pause)
		if (speed > 0.01f)
			speed -= 0.01f;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT) && !pause)
		if (cycles < 30)
			cycles++;
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT) && !pause)
		if (cycles > 1)
			cycles--;
	if (key == GLFW_KEY_C && action == GLFW_PRESS && !pause) {
		reverse = !reverse;
		if (reverse)
			std::cout << "CLOCKWISE" << std::endl;
		else
			std::cout << "COUNTERCLOCKWISE" << std::endl;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS) 
		pause = !pause;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) 
		animation = !animation;
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		smallr = 3.0f;
		larger = 9.0f;
		speed = 0.01f;
		cycles = 1;
		pause = false;
		animation = true;
		reverse = false;
		reset = true;
		zoomscale=100;
		angle = 0;
		std::cout << "RESET" << std::endl;
	}
	if (key == GLFW_KEY_KP_5 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (larger > 1.8)
			larger -= 0.3f;
	if (key == GLFW_KEY_KP_8 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (larger < 21.0)
			larger += 0.3f;
	if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
		larger = 9.0f;
	if (key == GLFW_KEY_KP_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (smallr > 0.9)
			smallr -= 0.3f;
	if (key == GLFW_KEY_KP_7 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (smallr < 21.0)
			smallr += 0.3f;
	if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS)
		smallr = 3.0f;
	if (key == GLFW_KEY_COMMA && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (angle < 360) 
			angle+=3;
	if (key == GLFW_KEY_PERIOD && (action == GLFW_PRESS || action == GLFW_REPEAT))
		if (angle > -360) 
			angle-=3;
	if (action == GLFW_RELEASE) {
		if (pause)
			std::cout << "PAUSED" << std::endl;
		else 		
			std::cout << "big radius: " << larger << " \tsmall radius: " << smallr << " \tn: "<< cycles << " \tk: " <<larger/smallr << std::endl;
		
	}
}

// Callback for mouse button presses
void InputHandler::mouse(GLFWwindow* window, int button, int action, int mods) {
}

// Callback for mouse motion
void InputHandler::motion(GLFWwindow* window, double x, double y) {
	mouseOldX = x;
	mouseOldY = y;
}

// Callback for mouse scroll
void InputHandler::scroll(GLFWwindow* window, double x, double y) {
	if (y>0 && zoomscale < 120) {
		zoom += 0.1;
		zoomscale++;
	}
	if (y<0 && zoomscale > 60) {
		zoom -= 0.1;
		zoomscale--;
	}
}

// Callback for window reshape/resize
void InputHandler::reshape(GLFWwindow* window, int width, int height) {
	renderEngine->setWindowSize(width, height);
}
