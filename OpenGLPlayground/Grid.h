#pragma once
#include "Shader.h"
#include "VertexBuffer.h"

// renders coordinate origin with colored markers for x, y and z 
class Grid
{
public:
	Grid()
	{
		SimpleVertex vertices[] = {
			SimpleVertex{-10.0f, 0.0f, 0.0f,			// position
						 1.0f, 0.0f, 0.0f, 1.0f},		// color
			SimpleVertex{10.0f, 0.0f, 0.0f,
						 1.0, 0.0f, 0.0f, 1.0f},
			/*SimpleVertex{0.0f, 0.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 1.0f},
			SimpleVertex{0.0f, 1.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 1.0f},*/
			SimpleVertex{0.0f, 0.0f, -10.0f,
						 0.0f, 0.0f, 1.0f, 1.0f},
			SimpleVertex{0.0f, 0.0f, 10.0f,
						 0.0f, 0.0f, 1.0f, 1.0f},

			SimpleVertex{-10.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -9.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -9.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -8.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -8.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -7.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -7.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -6.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -6.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -5.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -5.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -4.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -4.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -3.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -3.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -2.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -2.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, -1.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, -1.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},

			SimpleVertex{-10.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 9.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 9.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 8.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 8.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 7.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 7.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 6.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 6.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 5.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 5.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 4.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 4.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 3.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 3.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 2.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 2.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 1.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 1.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},

			SimpleVertex{-10.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-10.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-9.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-9.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-8.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-8.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-7.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-7.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-6.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-6.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-5.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-5.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-4.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-4.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-3.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-3.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-2.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-2.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-1.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{-1.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},

			SimpleVertex{10.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{10.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{9.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{9.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{8.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{8.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{7.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{7.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{6.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{6.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{5.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{5.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{4.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{4.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{3.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{3.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{2.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{2.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{1.0f, 0.0f, -10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
			SimpleVertex{1.0f, 0.0f, 10.0f,
						 0.5f, 0.5f, 0.5f, 1.0f},
		};
		numVertices = 84;//86;

		vertexBuffer = new SimpleVertexBuffer(vertices, numVertices);
		vertexBuffer->unbind();

		shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
		modelViewProjMatrixLocation = glGetUniformLocation(shader->getShaderId(), "u_modelViewProj");
	}

	~Grid()
	{
		delete vertexBuffer;
		delete shader;
	}

	inline void render(glm::mat4 modelViewProj)
	{
		shader->bind();
		vertexBuffer->bind();
		GLCALL(glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]));
		GLCALL(glDrawArrays(GL_LINES, 0, numVertices));
		vertexBuffer->unbind();
		shader->unbind();
	}

private:
	SimpleVertexBuffer* vertexBuffer;
	Shader* shader;
	int modelViewProjMatrixLocation;
	uint32_t numVertices;
};