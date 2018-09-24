#include "Geometry.h"
#include <cmath>

Geometry::Geometry() {
	drawMode = GL_TRIANGLES;
	vao = 0;
	vertexBuffer = 0;
	colourBuffer = 0;
	modelMatrix = glm::mat4(1.f);
}

void Geometry::makeCircle(float radius, float uInc, float t, float r) {
//	Geometry circle;
	for (double u=0.0; u<=2*M_PI; u+=uInc) {
		if (r==0) {
			verts.push_back(radius * glm::vec3(cos(u), sin(u), 0));
			colours.push_back(glm::vec3(0.f, 0.f, 0.f));
		}
		else {
			verts.push_back(glm::vec3(radius * cos(u) + ((r - radius) * cos(t)), radius * sin(u) + ((r - radius) * sin(t)), 0));
			colours.push_back(glm::vec3(0.f, 1.f, 0.f));
		}
	}
	drawMode = GL_LINE_STRIP;
//	return circle;
}

void Geometry::makeLine(float smallr, float bigr, float t, bool straight) {
	if (straight) {
		verts.push_back(glm::vec3((bigr - smallr) * cos(t), (bigr - smallr) * sin(t), 0));
		verts.push_back(glm::vec3((bigr - smallr)*cos(t) + (smallr*cos(((bigr - smallr) * t)/smallr)),(bigr - smallr)*sin(t) - (smallr*sin(((bigr - smallr) * t)/smallr)), 0));
		colours.push_back(glm::vec3(0.f, 1.f, 0.f));
		colours.push_back(glm::vec3(0.f, 1.f, 0.f));
	}
	else {
		if (t>=0) 
			for (float i = 0; i <= t; i += M_PI/100.f){
				verts.push_back(glm::vec3((bigr - smallr)*cos(i) + (smallr*cos(((bigr - smallr) * i)/smallr)),(bigr - smallr)*sin(i) - (smallr*sin(((bigr - smallr) * i)/smallr)), 0));
				colours.push_back(glm::vec3(1.f, 0.f, 0.f));
				colours.push_back(glm::vec3(1.f, 0.f, 0.f));
			}
		else
			for (float i = 0; i >= t; i -= M_PI/100.f){
				verts.push_back(glm::vec3((bigr - smallr)*cos(i) + (smallr*cos(((bigr - smallr) * i)/smallr)),(bigr - smallr)*sin(i) - (smallr*sin(((bigr - smallr) * i)/smallr)), 0));
				colours.push_back(glm::vec3(1.f, 0.f, 0.f));
				colours.push_back(glm::vec3(1.f, 0.f, 0.f));
			}
	}	
	drawMode = GL_LINE_STRIP;
}

void Geometry::clearBuffer() {
	verts.clear();
	colours.clear();
	modelMatrix = glm::mat4(1.f);
}
