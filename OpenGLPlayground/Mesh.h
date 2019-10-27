#pragma once
#include <vector>
#include <fstream>

#include "libs/glm/glm.hpp"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "libs/stb_image.h"

struct BMFMaterial {
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emissive;
	float shininess;
};

struct Material {
	BMFMaterial material;
	GLuint diffuseMap;
	GLuint normalMap;
};

class Mesh {
public:
	Mesh(std::vector<Vertex>& vertices, uint64_t numVertices, std::vector<uint32_t>& indices, uint64_t numIndices, Material material, Shader* shader) {
		this->material = material;
		this->shader = shader;
		this->numIndices = numIndices;

		vertexBuffer = new VertexBuffer(vertices.data(), numVertices);
		indexBuffer = new IndexBuffer(indices.data(), numIndices, sizeof(indices[0]));

		diffuseLocation = GLCALL(glGetUniformLocation(shader->getShaderId(), "u_material.diffuse"));
		specularLocation = GLCALL(glGetUniformLocation(shader->getShaderId(), "u_material.specular"));
		emissiveLocation = GLCALL(glGetUniformLocation(shader->getShaderId(), "u_material.emissive"));
		shininessLocation = GLCALL(glGetUniformLocation(shader->getShaderId(), "u_material.shininess"));
		diffuseMapLocation = GLCALL(glGetUniformLocation(shader->getShaderId(), "u_diffuse_map"));
	}
	~Mesh() {
		delete vertexBuffer;
		delete indexBuffer;
	}
	inline void render() {
		vertexBuffer->bind();
		indexBuffer->bind();
		glUniform3fv(diffuseLocation, 1, (float*)& material.material.diffuse[0]);
		glUniform3fv(specularLocation, 1, (float*)& material.material.specular[0]);
		glUniform3fv(emissiveLocation, 1, (float*)& material.material.emissive[0]);
		glUniform1f(shininessLocation, material.material.shininess);
		GLCALL(glBindTexture(GL_TEXTURE_2D, material.diffuseMap));
		GLCALL(glUniform1i(diffuseMapLocation, 0));
		GLCALL(glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0));
	}
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	Shader* shader;
	Material material;
	uint64_t numIndices = 0;
	int diffuseLocation;
	int specularLocation;
	int emissiveLocation;
	int shininessLocation;
	int diffuseMapLocation;
};

class Model {
public:
	void init(const char* filename, Shader* shader) {
		uint64_t numMeshes = 0;
		uint64_t numMaterials = 0;
		std::ifstream input = std::ifstream(filename, std::ios::in | std::ios::binary);
		if (!input.is_open()) {
			std::cout << "File not found" << std::endl;
			return;
		}

		// Materials
		input.read((char*)& numMaterials, sizeof(uint64_t));
		for (uint64_t i = 0; i < numMaterials; i++) {
			Material material = {};
			input.read((char*)& material, sizeof(BMFMaterial));

			uint64_t diffuseMapNameLength = 0;
			input.read((char*)& diffuseMapNameLength, sizeof(uint64_t));
			std::string diffuseMapName(diffuseMapNameLength, '\0');
			input.read((char*)& diffuseMapName[0], diffuseMapNameLength);

			uint64_t normalMapNameLength = 0;
			input.read((char*)& normalMapNameLength, sizeof(uint64_t));
			std::string normalMapName(normalMapNameLength, '\0');
			input.read((char*)& normalMapName[0], normalMapNameLength);

			assert(diffuseMapNameLength > 0);
			assert(normalMapNameLength > 0);

			int32_t textureWidth = 0;
			int32_t textureHeight = 0;
			int32_t bitsPerPixel = 0;
			GLCALL(glGenTextures(2, &material.diffuseMap));
			stbi_set_flip_vertically_on_load(true);
			{
				auto textureBuffer = stbi_load(diffuseMapName.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);
				assert(textureBuffer);
				assert(material.diffuseMap);

				GLCALL(glBindTexture(GL_TEXTURE_2D, material.diffuseMap));

				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer));

				if (textureBuffer) {
					stbi_image_free(textureBuffer);
				}
			}

			{
				auto textureBuffer = stbi_load(normalMapName.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);
				assert(textureBuffer);
				assert(material.normalMap);

				GLCALL(glBindTexture(GL_TEXTURE_2D, material.normalMap));

				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer));

				if (textureBuffer) {
					stbi_image_free(textureBuffer);
				}
			}

			GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
			materials.push_back(material);
		}

		// Meshes
		input.read((char*)& numMeshes, sizeof(uint64_t));

		for (uint64_t i = 0; i < numMeshes; i++) {
			std::vector<Vertex> vertices;
			uint64_t numVertices = 0;
			std::vector<uint32_t> indices;
			uint64_t numIndices = 0;
			uint64_t materialIndex = 0;

			input.read((char*)& materialIndex, sizeof(uint64_t));
			input.read((char*)& numVertices, sizeof(uint64_t));
			input.read((char*)& numIndices, sizeof(uint64_t));

			for (uint64_t i = 0; i < numVertices; i++) {
				Vertex vertex;
				input.read((char*)& vertex.position.x, sizeof(float));
				input.read((char*)& vertex.position.y, sizeof(float));
				input.read((char*)& vertex.position.z, sizeof(float));
				input.read((char*)& vertex.normal.x, sizeof(float));
				input.read((char*)& vertex.normal.y, sizeof(float));
				input.read((char*)& vertex.normal.z, sizeof(float));
				input.read((char*)& vertex.textureCoord.x, sizeof(float));
				input.read((char*)& vertex.textureCoord.y, sizeof(float));
				vertices.push_back(vertex);
			}
			for (uint64_t i = 0; i < numIndices; i++) {
				uint32_t index;
				input.read((char*)& index, sizeof(uint32_t));
				indices.push_back(index);
			}

			Mesh* mesh = new Mesh(vertices, numVertices, indices, numIndices, materials[materialIndex], shader);
			meshes.push_back(mesh);
		}
	}

	void render() {
		for (Mesh* mesh : meshes) {
			mesh->render();
		}
	}

	~Model() {
		for (Mesh* mesh : meshes) {
			delete mesh;
		}
	}
private:
	std::vector<Mesh*> meshes;
	std::vector<Material> materials;
};