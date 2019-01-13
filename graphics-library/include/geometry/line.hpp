#include "geometry/shape.hpp"
#include "engine/buffer.hpp"

namespace gl::geometry {

    class Line : public Shape {
    public:
        Line(const glm::vec3 &p1, const glm::vec3 &p2);
        ~Line();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        engine::Buffer<float> m_vertexBuffer;
    };
}