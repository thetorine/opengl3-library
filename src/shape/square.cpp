#include "shape/square.h"
#include "shader.hpp"
#include "utilities.hpp"

square::square() {
	this->vertexBuffer = bufferData(vertices, sizeof(vertices), GL_ARRAY_BUFFER);
	this->indexBuffer = bufferData(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);
	this->uvBuffer = bufferData(uv, sizeof(uv), GL_ARRAY_BUFFER);
}

square::~square() {

}

void square::draw(glm::mat4 model) {
	setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(UV_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(UV_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	setInt("wireframe", false);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, (void *)0);
	glDisable(GL_POLYGON_OFFSET_FILL);

	setInt("wireframe", true);
	glDrawElements(GL_LINE_LOOP, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, (void *)0);

	glDisableVertexAttribArray(POSITION_LOCATION);
	glDisableVertexAttribArray(UV_LOCATION);
}