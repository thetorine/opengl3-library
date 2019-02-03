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
        void resize(size_t space);
        void clear();
        size_t size();
        size_t capacity();
    private:
        GLuint m_bufferIndex;
        bool m_bufferCreated;
        GLuint m_mode;

        T *m_data;
        size_t m_size;
        size_t m_capacity;
    };
}