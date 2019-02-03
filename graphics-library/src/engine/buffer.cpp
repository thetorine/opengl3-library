#include <cstring>

#include "engine/buffer.hpp"

namespace gl::engine {

    const size_t DEFAULT_SIZE { 64 };

    template <class T>
    Buffer<T>::Buffer(GLuint mode)
        : Buffer({}, mode) {
    }

    template <class T>
    Buffer<T>::Buffer(const std::vector<T> &data, GLuint mode)
        : m_mode(mode) {
        addAll(data);
        transferBuffer();
    }

    template <class T>
    Buffer<T>::~Buffer() {
        if (m_bufferCreated) {
            glDeleteBuffers(1, &m_bufferIndex);
        }
        if (m_data != nullptr) {
            delete m_data;
        }
    }

    template <class T>
    void Buffer<T>::transferBuffer() {
        if (!m_bufferCreated) {
            glGenBuffers(1, &m_bufferIndex);
            m_bufferCreated = true;
        }
        glBindBuffer(m_mode, m_bufferIndex);
        if (m_size > 0) {
            glBufferData(m_mode, m_size * sizeof(T), m_data, GL_STREAM_DRAW);
        }
    }

    template <class T>
    void Buffer<T>::useBuffer() {
        if (m_bufferCreated) {
            glBindBuffer(m_mode, m_bufferIndex);
        }
    }

    template <class T>
    void Buffer<T>::addElement(T element) {
        if (m_size == m_capacity) {
            size_t newCapacity { m_size == 0 ? DEFAULT_SIZE : m_size * 2 };
            resize(newCapacity);
            m_capacity = newCapacity;
        }
        m_data[m_size++] = element;
    }

    template <class T>
    void Buffer<T>::addAll(const std::vector<T> &elements) {
        for (const auto &element : elements) {
            addElement(element);
        }
    }

    template <class T>
    void Buffer<T>::resize(size_t space) {
        if (space <= m_capacity) return;
        T *newBuffer { new T[space] };
        for (int i { 0 }; i < m_size; i++) {
            newBuffer[i] = m_data[i];
        }
        delete m_data;
        m_data = newBuffer;
    }

    template <class T>
    void Buffer<T>::clear() {
        m_size = 0;
    }

    template <class T>
    size_t Buffer<T>::size() {
        return m_size;
    }

    template <class T>
    size_t Buffer<T>::capacity() {
        return m_capacity;
    }

    template class Buffer<int>;
    template class Buffer<float>;
}