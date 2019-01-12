#pragma once

#include <memory>
#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

#define SHADER_DIR "shaders/"

#define POSITION_LOCATION 0
#define NORMAL_POSITION 1
#define UV_LOCATION 2

namespace gl::engine {
    class Shader {
    public:
        ~Shader();

        void useShader();

        void setModelMatrix(const glm::mat4 &matrix) const;
        void setViewMatrix(const glm::mat4 &matrix) const;
        void setProjMatrix(const glm::mat4 &matrix) const;
        void setVec3(std::string var, const glm::vec3 &value) const;
        void setInt(std::string var, int value) const;
        void setFloat(std::string var, float value) const;

        static void createShader(std::string shaderName);
        static const std::unique_ptr<Shader> &getInstance();
    private:
        Shader(std::string shaderName);
        bool compileShader();
        bool compileShader(GLuint shaderID, std::string file);

        std::string m_shaderName;
        // TODO: Refactor to remove the following except for m_programId.
        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;
        GLuint m_programID;

        GLint m_modelMatrixUniform;
        GLint m_viewMatrixUniform;
        GLint m_projMatrixUniform;
    };
}