#include "geometry/shape.hpp"
#include "engine/buffer.hpp"

namespace geometry {

    class Line : public Shape {
    public:
        Line(const glm::vec3 &p1, const glm::vec3 &p2);
        ~Line();
        void draw(const glm::mat4 &model);
    private:
        glm::vec3 startPoint;
        glm::vec3 endPoint;

        engine::Buffer<float> m_vertexBuffer;
    };
}