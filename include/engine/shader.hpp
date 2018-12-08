#pragma once

#include <memory>
#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

#define SHADER_DIR "res/shaders/"

#define POSITION_LOCATION 0
#define NORMAL_POSITION 1
#define UV_LOCATION 2

namespace engine {
    class Shader {
    public:
        Shader(std::string shaderName);
        ~Shader();

        bool compileShader();
        void useShader();

        void setModelMatrix(glm::mat4 matrix);
        void setViewMatrix(glm::mat4 matrix);
        void setProjMatrix(glm::mat4 matrix);
        void setVec3(std::string var, glm::vec3 value);
        void setInt(std::string var, int value);
        void setFloat(std::string var, float value);

        static void createShader(std::string shaderName);
        static std::unique_ptr<Shader> &getInstance();
    private:
        bool compileShader(GLuint shaderID, std::string file);

        std::string m_shaderName;

        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;
        GLuint m_programID;

        GLint m_modelMatrixUniform;
        GLint m_viewMatrixUniform;
        GLint m_projMatrixUniform;
    };
}