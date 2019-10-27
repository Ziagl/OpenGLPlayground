#pragma once

#include <GL/glew.h>

struct IndexBuffer 
{
	IndexBuffer(void* data, uint32_t numIndices, uint8_t elementSize) {
		// Buffer auf der Grafikkarte erstellen
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);
	}

	virtual ~IndexBuffer() {
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &bufferId);
	}

	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	}

	void unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

private:
	GLuint bufferId;
};