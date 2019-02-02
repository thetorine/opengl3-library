#pragma once

#include <memory>

#include "engine/shader.hpp"

namespace gl::engine {

    class ShaderController {
    public:
        ~ShaderController();

        void setShader(const std::shared_ptr<Shader> &shader);

        void setMat4(std::string var, const glm::mat4 &matrix) const;
        void setVec3(std::string var, const glm::vec3 &value) const;
        void setInt(std::string var, int value) const;
        void setFloat(std::string var, float value) const;

        static std::unique_ptr<ShaderController> &getInstance();
    private:
        ShaderController();

        std::shared_ptr<Shader> m_currentShader;
    };
}