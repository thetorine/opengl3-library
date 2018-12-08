#pragma once

namespace illumination {
    class LightType {
    public:
        virtual ~LightType() = default;
        virtual void setShaderParams(int index) = 0;
    };
}