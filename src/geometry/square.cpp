#include "geometry/square.hpp"
#include "engine/shader.hpp"
#include "utilities.hpp"

namespace geometry {
    Square::Square() {
        this->m_vertexBuffer = engine::bufferData(m_vertices, sizeof(m_vertices), GL_ARRAY_BUFFER);
        this->m_normalBuffer = engine::bufferData(m_normals, sizeof(m_normals), GL_ARRAY_BUFFER);
        this->m_uvBuffer = engine::bufferData(m_uv, sizeof(m_uv), GL_ARRAY_BUFFER);
    }

    Square::~Square() {

    }

    void Square::draw(glm::mat4 &model) {
        engine::Shader::getInstance()->setModelMatrix(model);

        glEnableVertexAttribArray(POSITION_LOCATION);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_DOUBLE, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(NORMAL_POSITION);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
        glVertexAttribPointer(NORMAL_POSITION, 3, GL_DOUBLE, GL_TRUE, 0, nullptr);

        glEnableVertexAttribArray(UV_LOCATION);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
        glVertexAttribPointer(UV_LOCATION, 2, GL_DOUBLE, GL_FALSE, 0, nullptr);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertices) / sizeof(float));
        glDisable(GL_POLYGON_OFFSET_FILL);

        /*setInt("wireframe", true);
        glDrawArrays(GL_LINE_LOOP, 0, sizeof(vertices) / sizeof(float));
        setInt("wireframe", false);*/

        glDisableVertexAttribArray(POSITION_LOCATION);
        glDisableVertexAttribArray(UV_LOCATION);
    }
}