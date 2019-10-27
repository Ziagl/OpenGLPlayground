#pragma once
#include "Shader.h"
#include "VertexBuffer.h"

// renders coordinate origin with colored markers for x, y and z 
class Origin
{
public:
	Origin()
	{
		SimpleVertex vertices[] = {
			SimpleVertex{0.0f, 0.0f, 0.0f,			// position
						 1.0f, 0.0f, 0.0f, 1.0f},	// color
			SimpleVertex{1.0f, 0.0f, 0.0f,
						 1.0, 0.0f, 0.0f, 1.0f},
			SimpleVertex{0.0f, 0.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 1.0f},
			SimpleVertex{0.0f, 1.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 1.0f},
			SimpleVertex{0.0f, 0.0f, 0.0f,
						 0.0f, 0.0f, 1.0f, 1.0f},
			SimpleVertex{0.0f, 0.0f, 1.0f,
						 0.0f, 0.0f, 1.0f, 1.0f}
		};
		numVertices = 6;

		vertexBuffer = new SimpleVertexBuffer(vertices, numVertices);
		vertexBuffer->unbind();

		shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
		modelViewProjMatrixLocation = glGetUniformLocation(shader->getShaderId(), "u_modelViewProj");
	}

	~Origin()
	{
		delete vertexBuffer;
		delete shader;
	}

	inline void render(glm::mat4 modelViewProj)
	{
		shader->bind();
		vertexBuffer->bind();
		GLCALL(glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]));
		GLCALL(glLineWidth(2.0f));				// set new line width
		GLCALL(glDrawArrays(GL_LINES, 0, numVertices));
		GLCALL(glLineWidth(1.0f));				// reset line width again
		vertexBuffer->unbind();
		shader->unbind();
	}

private:
	SimpleVertexBuffer* vertexBuffer;
	Shader* shader;
	int modelViewProjMatrixLocation;
	uint32_t numVertices;
};