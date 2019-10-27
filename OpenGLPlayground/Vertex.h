#pragma once

#include "libs/glm/glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoord;
};

struct SimpleVertex {
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};