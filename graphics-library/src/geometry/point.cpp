#include "engine/shader_controller.hpp"
#include "geometry/point.hpp"

namespace gl::geometry {

    Point::Point(const std::vector<float> &vertices)
        : m_vertexBuffer(GL_ARRAY_BUFFER) {
        m_vertexBuffer.addAll(vertices);
        m_vertexBuffer.transferBuffer();
    }

    Point::~Point() {}

    void Point::draw(const glm::mat4 &model) {
        engine::ShaderController::getInstance()->setMat4("modelMatrix", model);

        glPointSize(10.0f);

        glEnableVertexAttribArray(engine::POSITION_UNIFORM);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(engine::POSITION_UNIFORM, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(m_vertexBuffer.size()));

        glDisableVertexAttribArray(engine::POSITION_UNIFORM);
    }
}