#include "Program.h"

Program::Program() {
	window = nullptr;
	renderEngine = nullptr;
}

// Error callback for glfw errors
void Program::error(int error, const char* description) {
	std::cerr << description << std::endl;
}

// Called to start the program
void Program::start() {
	setupWindow();
	GLenum err = glewInit();
	if (glewInit() != GLEW_OK) {
		std::cerr << glewGetErrorString(err) << std::endl;
	}

	renderEngine = new RenderEngine(window);
	InputHandler::setUp(renderEngine);
	mainLoop();
}

// Creates GLFW window for the program and sets callbacks for input
void Program::setupWindow() {
	glfwSetErrorCallback(Program::error);
	if (glfwInit() == 0) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(512, 512, "589 Boilerplate", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // V-sync on

	glfwSetKeyCallback(window, InputHandler::key);
	glfwSetMouseButtonCallback(window, InputHandler::mouse);
	glfwSetCursorPosCallback(window, InputHandler::motion);
	glfwSetScrollCallback(window, InputHandler::scroll);
	glfwSetWindowSizeCallback(window, InputHandler::reshape);
}
float InputHandler::speed = 0.01f;
int InputHandler::cycles = 1;
bool InputHandler::reverse = false;
bool InputHandler::pause = false;
bool InputHandler::animation = true;
bool InputHandler::reset = false;
float InputHandler::zoom = 1.0f;
float InputHandler::smallr=3.0f;
float InputHandler::larger=9.0f;
int InputHandler::zoomscale = 100;
float InputHandler::angle = 0;
// Main loop
void Program::mainLoop() {
	
	float u = 0.0f;
	//	testObject = Geometry::makeCircle(2.0, 0.01);

	Geometry bigCircle, smallRadius, smallCircle, hypoLine;
	
		
	while(!glfwWindowShouldClose(window)) {
		if (InputHandler::reset) {
			u = 0.0f;
			InputHandler::reset = false;
		}
		InputHandler::smallr *= InputHandler::zoom;
		InputHandler::larger *= InputHandler::zoom;
		InputHandler::zoom=1.0f;
		if (InputHandler::animation) {
			if (!InputHandler::pause) {
				if (InputHandler::reverse) {
					u-=InputHandler::speed;
					if (u< -InputHandler::cycles*2*M_PI) {
						u = 0.0f;
						glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
					}
				}
				else {
					u+=InputHandler::speed;
					if (u> InputHandler::cycles*2*M_PI) {
						u = 0.0f;
						glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
					}
				}
			}
		}
		else {
			u = InputHandler::cycles*2*M_PI;
		}
		
		objects.clear();
		bigCircle.clearBuffer();
		bigCircle.makeCircle(InputHandler::larger, .01f, u, 0);
		renderEngine->assignBuffers(bigCircle);
		renderEngine->updateBuffers(bigCircle);
		objects.push_back(&bigCircle);
		smallRadius.clearBuffer();
		smallRadius.makeLine(InputHandler::smallr, InputHandler::larger, u, true);
		renderEngine->assignBuffers(smallRadius);
		renderEngine->updateBuffers(smallRadius);
		objects.push_back(&smallRadius);
		smallCircle.clearBuffer();
		smallCircle.makeCircle(InputHandler::smallr, .01f, u, InputHandler::larger);
		renderEngine->assignBuffers(smallCircle);
		renderEngine->updateBuffers(smallCircle);
		objects.push_back(&smallCircle);
		hypoLine.clearBuffer();
		hypoLine.makeLine(InputHandler::smallr, InputHandler::larger, u, false);
		renderEngine->assignBuffers(hypoLine);
		renderEngine->updateBuffers(hypoLine);
		objects.push_back(&hypoLine);
		for (Geometry* o : objects) 
			o->modelMatrix = glm::rotate(o->modelMatrix, glm::radians(InputHandler::angle), glm::vec3(0.0f,0.0f,1.0f));

		
		glfwPollEvents();

		renderEngine->render(objects, glm::mat4(1.f));
		glfwSwapBuffers(window);
	}

	// Clean up, program needs to exit
	glfwDestroyWindow(window);
	delete renderEngine;
	glfwTerminate();
}
