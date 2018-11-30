#include <vector>

#include "geometry/sphere.hpp"
#include "utilities.hpp"
#include "shader.hpp"

// x = r cos(t) y = r sin(t)

sphere::sphere(float radius) {
	std::vector<float> vertices;
	std::vector<int> indices;
	std::vector<float> normals;

	static const float pi = std::acos(-1);

	float sampleRate = 0.05f;
	int pointCount = std::ceil(2.0f * pi / sampleRate);

	for (float yTheta = 0.0f; yTheta <= pi; yTheta += sampleRate) {
		float xzR = radius * std::sin(yTheta);
		float y = radius * std::cos(yTheta);

		for (float xzTheta = 0.0f; xzTheta <= 2 * pi; xzTheta += sampleRate) {
			float x = xzR * std::cos(xzTheta);
			float z = xzR * std::sin(xzTheta);

			vertices.insert(vertices.end(), { x, y, z });
			
			glm::vec3 n = glm::normalize(glm::vec3(x, y, z));
			normals.insert(normals.end(), { n.x, n.y, n.z });

			int count = vertices.size() / 3;
			if (count > pointCount) {
				indices.push_back(count - 1);
				indices.push_back(count - 2);
				indices.push_back(count - pointCount);
			
				indices.push_back(count - 1);
				indices.push_back(count - pointCount);
				indices.push_back(count - pointCount + 1);
			}
		}
	}

	vertexBuffer = bufferData(&vertices[0], vertices.size() * sizeof(float), GL_ARRAY_BUFFER);
	indexBuffer = bufferData(&indices[0], indices.size() * sizeof(int), GL_ELEMENT_ARRAY_BUFFER);
	normalBuffer = bufferData(&normals[0], normals.size() * sizeof(int), GL_ARRAY_BUFFER);
	
	vertexCount = vertices.size();
	indexCount = indices.size();
	normalCount = normals.size();
}

sphere::~sphere() {

}

void sphere::draw(glm::mat4 model) {
	setModelMatrix(model);

	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(NORMAL_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void *)0);

	glDisableVertexAttribArray(POSITION_LOCATION);
}