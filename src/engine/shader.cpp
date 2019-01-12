#include <cstdio>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/shader.hpp"
#include "utilities.hpp"

namespace gl::engine {

    static std::unique_ptr<Shader> shaderObj;

    Shader::Shader(std::string shaderName)
        : m_shaderName(shaderName) {
        if (!compileShader()) {
            std::printf("Unable to compile shader\n");
            exit(-1);
        }
    }

    Shader::~Shader() {
        glDeleteProgram(m_programID);
    }

    bool Shader::compileShader() {
        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        bool r1 { compileShader(m_vertexShaderID, SHADER_DIR + m_shaderName + "/vertex.glsl") };
        bool r2 { compileShader(m_fragmentShaderID, SHADER_DIR + m_shaderName + "/fragment.glsl") };

        if (!r1 || !r2) {
            std::printf("Unable to compile shaders\n");
            glDeleteShader(m_fragmentShaderID);
            glDeleteShader(m_vertexShaderID);
            return false;
        }

        m_programID = glCreateProgram();
        glAttachShader(m_programID, m_vertexShaderID);
        glAttachShader(m_programID, m_fragmentShaderID);

        // Allows us to set these variables later on.
        glBindAttribLocation(m_programID, POSITION_LOCATION, "position");
        glBindAttribLocation(m_programID, NORMAL_POSITION, "normal");
        glBindAttribLocation(m_programID, UV_LOCATION, "uv");
        glLinkProgram(m_programID);

        GLint linkStatus { 0 };
        glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);

        if (linkStatus == GL_FALSE) {
            GLint maxLength { 0 };
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *errorLog { new GLchar[maxLength] };
            glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

            std::printf("%s\n", (char *)errorLog);

            glDeleteProgram(m_programID);
            glDeleteShader(m_vertexShaderID);
            glDeleteShader(m_fragmentShaderID);

            delete errorLog;

            return false;
        }

        glDetachShader(m_programID, m_vertexShaderID);
        glDetachShader(m_programID, m_fragmentShaderID);

        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);

        m_modelMatrixUniform = glGetUniformLocation(m_programID, "modelMatrix");
        m_viewMatrixUniform = glGetUniformLocation(m_programID, "viewMatrix");
        m_projMatrixUniform = glGetUniformLocation(m_programID, "projMatrix");

        return true;
    }

    bool Shader::compileShader(GLuint shaderID, std::string file) {
        GLint success { 0 };
        std::string shaderCode { readFile(file) };
        const GLchar *shaderString { shaderCode.c_str() };

        glShaderSource(shaderID, 1, &shaderString, NULL);
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLength { 0 };
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *errorLog { new GLchar[maxLength] };
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

            std::printf("%s\n", (char *)errorLog);

            glDeleteShader(shaderID);
            delete errorLog;

            return false;
        }

        return true;
    }

    void Shader::useShader() {
        glUseProgram(m_programID);
    }

    void Shader::setModelMatrix(const glm::mat4 &matrix) const {
        glUniformMatrix4fv(m_modelMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::setViewMatrix(const glm::mat4 &matrix) const {
        glUniformMatrix4fv(m_viewMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::setProjMatrix(const glm::mat4 &matrix) const {
        glUniformMatrix4fv(m_projMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::setVec3(std::string var, const glm::vec3 &value) const {
        GLint location { glGetUniformLocation(m_programID, var.c_str()) };
        glUniform3fv(location, 1, &value[0]);
    }

    void Shader::setInt(std::string var, int value) const {
        GLint location { glGetUniformLocation(m_programID, var.c_str()) };
        glUniform1i(location, value);
    }

    void Shader::setFloat(std::string var, float value) const {
        GLint location { glGetUniformLocation(m_programID, var.c_str()) };
        glUniform1f(location, value);
    }

    void Shader::createShader(std::string shaderName) {
        shaderObj = std::unique_ptr<Shader>(new Shader(shaderName));
    }

    const std::unique_ptr<Shader> &Shader::getInstance() {
        return shaderObj;
    }
}