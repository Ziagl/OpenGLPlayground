#pragma once
#include "Shader.h"
#include "VertexBuffer.h"

class SimpleMesh
{
public:
	SimpleMesh() 
	{
		SimpleVertex vertices[] = {
			SimpleVertex{-0.5f, -0.5f, 0.0f,		// position
						 1.0f, 0.0f, 0.0f, 1.0f},	// color
			SimpleVertex{0.0f, 0.5f, 0.0f,
						 0.0, 1.0f, 0.0f, 1.0f},
			SimpleVertex{0.5f, -0.5f, 0.0f,
						 0.0f, 0.0f, 1.0f, 1.0f}
			};
		numVertices = 3;

		vertexBuffer = new SimpleVertexBuffer(vertices, numVertices);
		vertexBuffer->unbind();
#ifdef _WIN32							// nur für Windows
		shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
#else
		shader = new Shader("shaders/basic_raspi.vert", "shaders/basic_raspi.frag");
#endif
		modelViewProjMatrixLocation = glGetUniformLocation(shader->getShaderId(), "u_modelViewProj");
	}
	~SimpleMesh()
	{
		delete vertexBuffer;
		delete shader;
	}

	inline void render(glm::mat4 modelViewProj)
	{
		shader->bind();
		vertexBuffer->bind();
		GLCALL(glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]));
		GLCALL(glDrawArrays(GL_TRIANGLES, 0, numVertices));
		vertexBuffer->unbind();
		shader->unbind();
	}

private:
	SimpleVertexBuffer* vertexBuffer;
	Shader* shader;
	int modelViewProjMatrixLocation;
	uint32_t numVertices;
};