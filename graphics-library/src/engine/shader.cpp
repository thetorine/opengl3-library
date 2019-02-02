#include <cstdio>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/shader.hpp"
#include "utilities.hpp"

namespace gl::engine {

    Shader::Shader(std::string vertexDir, std::string fragmentDir) {
        if (!initShader(vertexDir, fragmentDir)) {
            std::printf("Unable to compile shader\n");
            exit(-1);
        }
    }

    Shader::~Shader() {
        glDeleteProgram(m_programID);
    }

    bool Shader::initShader(std::string vertexDir, std::string fragmentDir) {
        GLuint vertexShaderID { glCreateShader(GL_VERTEX_SHADER) };
        GLuint fragmentShaderID { glCreateShader(GL_FRAGMENT_SHADER) };

        bool r1 { compileShader(vertexShaderID, vertexDir) };
        bool r2 { compileShader(fragmentShaderID, fragmentDir) };

        if (!r1 || !r2) {
            std::printf("Unable to compile shaders\n");
            glDeleteShader(fragmentShaderID);
            glDeleteShader(vertexShaderID);
            return false;
        }

        m_programID = glCreateProgram();
        glAttachShader(m_programID, vertexShaderID);
        glAttachShader(m_programID, fragmentShaderID);

        glBindAttribLocation(m_programID, POSITION_UNIFORM, "position");
        glBindAttribLocation(m_programID, NORMAL_UNIFORM, "normal");
        glBindAttribLocation(m_programID, UV_UNIFORM, "uv");
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
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);

            delete errorLog;

            return false;
        }

        glDetachShader(m_programID, vertexShaderID);
        glDetachShader(m_programID, fragmentShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

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

    void Shader::setMat4(std::string var, const glm::mat4 &matrix) const {
        GLint location { glGetUniformLocation(m_programID, var.c_str()) };
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
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
}
