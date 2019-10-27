#pragma once

#include <GL/glew.h>
#include "Vertex.h"

struct VertexBuffer 
{
	VertexBuffer(void* data, uint32_t numVertices) {
		// vao einstellen
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Buffer auf der Grafikkarte erstellen
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(SimpleVertex), data, GL_STATIC_DRAW);

		// OpenGL Vertex Format angeben
		// wird im eingestellten vao gespeichert
		glEnableVertexAttribArray(0);	// erstes Attribut ist die Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position));
		glEnableVertexAttribArray(1);	// zweites Attribut ist die Farbe
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal));
		glEnableVertexAttribArray(2);	// drittes Attribut ist die Texturkoordinate
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, textureCoord));
		glBindVertexArray(0);
	}

	virtual ~VertexBuffer() {
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &bufferId);
	}

	void bind() {
		glBindVertexArray(vao);
	}

	void unbind() {
		glBindVertexArray(0);
	}

private:
	GLuint bufferId;
	GLuint vao;
};



struct SimpleVertexBuffer
{
	SimpleVertexBuffer(void* data, uint32_t numVertices) {
		// vao einstellen
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Buffer auf der Grafikkarte erstellen
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(SimpleVertex), data, GL_STATIC_DRAW);

		// OpenGL Vertex Format angeben
		// wird im eingestellten vao gespeichert
		glEnableVertexAttribArray(0);	// erstes Attribut ist die Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)offsetof(struct SimpleVertex, x));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)offsetof(struct SimpleVertex, r));
		glBindVertexArray(0);
	}

	virtual ~SimpleVertexBuffer() {
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &bufferId);
	}

	void bind() {
		glBindVertexArray(vao);
	}

	void unbind() {
		glBindVertexArray(0);
	}

private:
	GLuint bufferId;
	GLuint vao;
};