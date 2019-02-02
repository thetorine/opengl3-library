#include "engine/shader_controller.hpp"

namespace gl::engine {

    ShaderController::ShaderController() {

    }

    ShaderController::~ShaderController() {

    }

    void ShaderController::setShader(const std::shared_ptr<Shader> &shader) {
        m_currentShader = shader;
        m_currentShader->useShader();
    }

    void ShaderController::setMat4(std::string var, const glm::mat4 &matrix) const {
        m_currentShader->setMat4(var, matrix);
    }

    void ShaderController::setVec3(std::string var, const glm::vec3 &value) const {
        m_currentShader->setVec3(var, value);
    }

    void ShaderController::setInt(std::string var, int value) const {
        m_currentShader->setInt(var, value);
    }

    void ShaderController::setFloat(std::string var, float value) const {
        m_currentShader->setFloat(var, value);
    }

    std::unique_ptr<ShaderController> &ShaderController::getInstance() {
        static std::unique_ptr<ShaderController> instance { std::unique_ptr<ShaderController>(new ShaderController) };
        return instance;
    }
}