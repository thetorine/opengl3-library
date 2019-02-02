#include <memory>

#include "engine/shader_controller.hpp"
#include "geometry/line.hpp"

namespace gl::geometry {

    Line::Line(const glm::vec3 &p1, const glm::vec3 &p2)
        : m_vertexBuffer(GL_ARRAY_BUFFER) {
        m_vertexBuffer.addAll({ p1.x, p1.y, p1.z,
                                p2.x, p2.y, p2.z });
        m_vertexBuffer.transferBuffer();
    }

    Line::~Line() {

    }

    void Line::draw(const glm::mat4 &model) {
        engine::ShaderController::getInstance()->setMat4("modelMatrix", model);

        glEnableVertexAttribArray(engine::POSITION_UNIFORM);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(engine::POSITION_UNIFORM, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_vertexBuffer.size()));

        glDisableVertexAttribArray(engine::POSITION_UNIFORM);
    }
}