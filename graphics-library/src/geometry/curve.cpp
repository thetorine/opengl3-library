#include <memory>

#include "engine/shader.hpp"
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
        engine::Shader::getInstance()->setModelMatrix(model);

        glEnableVertexAttribArray(POSITION_LOCATION);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(m_vertexBuffer.size() / 3.0f));

        glDisableVertexAttribArray(POSITION_LOCATION);
    }
}