#include "geometry/shape.hpp"
#include "engine/buffer.hpp"

namespace gl::geometry {

    class Curve : public Shape {
    public:
        Curve(const std::vector<float> &vertices);
        ~Curve();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        engine::Buffer<float> m_vertexBuffer;
    };
}