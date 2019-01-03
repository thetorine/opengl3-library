#include <memory>

#include "engine/shader.hpp"
#include "geometry/line.hpp"

namespace geometry {

    Line::Line(const glm::vec3 &p1, const glm::vec3 &p2)
        : startPoint(p1),
        endPoint(p2),
        m_vertexBuffer(engine::Buffer<float>(GL_ARRAY_BUFFER)) {

        m_vertexBuffer.addAll({ p1.x, p1.y, p1.z,
                                p2.x, p2.y, p2.z });
        m_vertexBuffer.transferBuffer();
    }

    Line::~Line() {

    }

    void Line::draw(const glm::mat4 &model) {
        engine::Shader::getInstance()->setModelMatrix(model);

        glEnableVertexAttribArray(POSITION_LOCATION);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_vertexBuffer.size()));

        glDisableVertexAttribArray(POSITION_LOCATION);
    }
}