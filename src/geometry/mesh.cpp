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
	
	for (size_t s = 0; s < shapes.size(); s++) {
		size_t indexOffset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];

				vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 0]);
				vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 1]);
				vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 2]);

				normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 0]);
				normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 1]);
				normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 2]);
			}
			indexOffset += fv;
		}
	}

	vertexBuffer.transferBuffer();
	normalBuffer.transferBuffer();
}

mesh::mesh(std::vector<float> &vertices, std::vector<float> &normals, std::vector<int> &indices) {
	vertexBuffer.addAll(vertices);
	normalBuffer.addAll(normals);
	indexBuffer.addAll(indices);

	vertexBuffer.transferBuffer();
	normalBuffer.transferBuffer();
	indexBuffer.transferBuffer();

	hasIndices = true;
}

mesh::~mesh() {

}

void mesh::draw(glm::mat4 &model) {
	shader::getInstance()->setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	vertexBuffer.useBuffer();
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(NORMAL_POSITION);
	normalBuffer.useBuffer();
	glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

	
	if (!hasIndices)
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexBuffer.size()));
	else {
		indexBuffer.useBuffer();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexBuffer.size()), GL_UNSIGNED_INT, (void *)0);
	}

	glDisableVertexAttribArray(POSITION_LOCATION);
	glDisableVertexAttribArray(UV_LOCATION);
}