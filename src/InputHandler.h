#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "RenderEngine.h"

class InputHandler {

public:
	static void setUp(RenderEngine* renderEngine);

	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse(GLFWwindow* window, int button, int action, int mods);
	static void motion(GLFWwindow* window, double x, double y);
	static void scroll(GLFWwindow* window, double x, double y);
	static void reshape(GLFWwindow* window, int width, int height);
	
	static float speed;
	static int cycles;
	static bool reverse;
	static bool pause;
	static bool animation;
	static bool reset;
	static float larger;
	static float smallr;
	static float zoom;
	static int zoomscale;
	static float angle;
	
private:
	static RenderEngine* renderEngine;

	static int mouseOldX;
	static int mouseOldY;
};
