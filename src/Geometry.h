#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

class Geometry {

public:
	Geometry();

	GLuint drawMode;

	GLuint vao;
	GLuint vertexBuffer;
	GLuint colourBuffer;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> colours;
	glm::mat4 modelMatrix;
	
	void makeCircle(float radius, float uInc, float t, float r);
	void makeLine(float smallr, float bigr, float t, bool straight);
	void clearBuffer();
};

