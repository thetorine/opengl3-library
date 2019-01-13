#pragma once

namespace gl::illumination {
    class LightType {
    public:
        virtual ~LightType() = default;
        virtual void setShaderParams(int index) = 0;
    };
}