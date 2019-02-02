#include <memory>

#include "engine/shader_controller.hpp"
#include "geometry/curve.hpp"

namespace gl::geometry {

    Curve::Curve(const std::vector<float> &vertices)
        : m_vertexBuffer(GL_ARRAY_BUFFER) {
        m_vertexBuffer.addAll(vertices);
        m_vertexBuffer.transferBuffer();
    }

    Curve::~Curve() {

    }

    void Curve::draw(const glm::mat4 &model) {
        engine::ShaderController::getInstance()->setMat4("modelMatrix", model);

        glEnableVertexAttribArray(engine::POSITION_UNIFORM);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(engine::POSITION_UNIFORM, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_vertexBuffer.size() / 3.0f));

        glDisableVertexAttribArray(engine::POSITION_UNIFORM);
    }
}