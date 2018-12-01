#include "geometry/square.hpp"
#include "shader.hpp"
#include "utilities.hpp"

square::square() {
	this->vertexBuffer = bufferData(vertices, sizeof(vertices), GL_ARRAY_BUFFER);
	this->normalBuffer = bufferData(normals, sizeof(normals), GL_ARRAY_BUFFER);
	this->uvBuffer = bufferData(uv, sizeof(uv), GL_ARRAY_BUFFER);
}

square::~square() {

}

void square::draw(glm::mat4 &model) {
	setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(NORMAL_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

	glEnableVertexAttribArray(UV_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(UV_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
	glDisable(GL_POLYGON_OFFSET_FILL);

	/*setInt("wireframe", true);
	glDrawArrays(GL_LINE_LOOP, 0, sizeof(vertices) / sizeof(float));
	setInt("wireframe", false);*/

	glDisableVertexAttribArray(POSITION_LOCATION);
	glDisableVertexAttribArray(UV_LOCATION);
}