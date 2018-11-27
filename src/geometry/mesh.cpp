#pragma once

#include <vector>
#include <tiny_obj_loader.h>

#include "shader.hpp"
#include "utilities.hpp"
#include "geometry/mesh.hpp"

mesh::mesh(std::string file) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, file.c_str());

	if (!err.empty() || !ret) {
		printf("error loading model: %s", err.c_str());
		exit(1);
	}
	
	std::vector<float> vertices;
	std::vector<float> normals;

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t indexOffset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];

				vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
				vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
				vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

				normals.push_back(attrib.normals[3 * idx.normal_index + 0]);
				normals.push_back(attrib.normals[3 * idx.normal_index + 1]);
				normals.push_back(attrib.normals[3 * idx.normal_index + 2]);
			}
			indexOffset += fv;
		}
	}

	this->vertexCount = vertices.size() / 3;
	this->vertexBuffer = bufferData(&vertices[0], vertices.size() * sizeof(float), GL_ARRAY_BUFFER);
	this->normalBuffer = bufferData(&normals[0], normals.size() * sizeof(float), GL_ARRAY_BUFFER);
}

mesh::~mesh() {

}

void mesh::draw(glm::mat4 model) {
	setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(NORMAL_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_TRUE, 0, (void *)0);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glDisableVertexAttribArray(POSITION_LOCATION);
	glDisableVertexAttribArray(UV_LOCATION);
}