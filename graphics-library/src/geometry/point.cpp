#include "engine/shader.hpp"
#include "geometry/point.hpp"

namespace gl::geometry {

    Point::Point(const std::vector<float> &vertices)
        : m_vertexBuffer(GL_ARRAY_BUFFER) {
        m_vertexBuffer.addAll(vertices);
        m_vertexBuffer.transferBuffer();
    }

    Point::~Point() {}

    void Point::draw(const glm::mat4 &model) {
        engine::Shader::getInstance()->setModelMatrix(model);

        glPointSize(10.0f);

        glEnableVertexAttribArray(POSITION_LOCATION);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(m_vertexBuffer.size()));

        glDisableVertexAttribArray(POSITION_LOCATION);
    }
}