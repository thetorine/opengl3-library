#pragma once

#include <memory>
#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

namespace gl::engine {
    const int POSITION_UNIFORM { 0 };
    const int NORMAL_UNIFORM { 1 };
    const int UV_UNIFORM { 2 };

    class Shader {
    public:
        Shader(std::string vertexDir, std::string fragmentDir);
        ~Shader();

        void useShader();

        void setMat4(std::string var, const glm::mat4 &matrix) const;
        void setVec3(std::string var, const glm::vec3 &value) const;
        void setInt(std::string var, int value) const;
        void setFloat(std::string var, float value) const;
    protected:
        bool initShader(std::string vertexDir, std::string fragmentDir);
        bool compileShader(GLuint shaderID, std::string file);

        GLuint m_programID;
    };
}