#pragma once

#include <vector>
#include <GL/glew.h>

namespace gl::engine {
    template <class T>
    class Buffer {
    public:
        Buffer(GLuint mode);
        Buffer(const std::vector<T> &data, GLuint mode);
        ~Buffer();
        void transferBuffer();
        void useBuffer();

        void addElement(T element);
        void addAll(const std::vector<T> &elements);
        size_t size();
    private:
        GLuint m_bufferIndex;
        std::vector<T> m_data;
        GLuint m_mode;
    };
}