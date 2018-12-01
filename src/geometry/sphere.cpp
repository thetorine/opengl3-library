#include <vector>

#include "geometry/sphere.hpp"
#include "utilities.hpp"
#include "shader.hpp"

// x = r cos(t) y = r sin(t)

sphere::sphere(float radius) {
	static const float pi = (float)std::acos(-1);

	float sampleRate = 0.1f;
	int pointCount = (int)std::ceil(2.0f * pi / sampleRate);

	for (float yTheta = 0.0f; yTheta <= pi; yTheta += sampleRate) {
		float xzR = radius * std::sin(yTheta);
		float y = radius * std::cos(yTheta);

		for (float xzTheta = 0.0f; xzTheta <= 2 * pi; xzTheta += sampleRate) {
			float x = xzR * std::cos(xzTheta);
			float z = xzR * std::sin(xzTheta);

			vertexBuffer.addElement(x);
			vertexBuffer.addElement(y);
			vertexBuffer.addElement(z);

			glm::vec3 n = glm::normalize(glm::vec3(x, y, z));
			normalBuffer.addElement(n.x);
			normalBuffer.addElement(n.y);
			normalBuffer.addElement(n.z);

			int count = vertexBuffer.size() / 3;
			if (count > pointCount) {
				indexBuffer.addElement(count - 1);
				indexBuffer.addElement(count - 2);
				indexBuffer.addElement(count - pointCount);
			
				indexBuffer.addElement(count - 1);
				indexBuffer.addElement(count - pointCount);
				indexBuffer.addElement(count - pointCount + 1);
			}
		}
	}

	vertexBuffer.transferBuffer();
	indexBuffer.transferBuffer();
	normalBuffer.transferBuffer();
}

sphere::~sphere() {

}

void sphere::draw(glm::mat4 model) {
	setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	vertexBuffer.useBuffer();
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(NORMAL_POSITION);
	normalBuffer.useBuffer();
	glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	indexBuffer.useBuffer();
	glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, (void *)0);

	glDisableVertexAttribArray(POSITION_LOCATION);
}