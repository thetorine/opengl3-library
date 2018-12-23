#include "engine/buffer.hpp"

namespace engine {

    template <class T>
    Buffer<T>::Buffer(GLuint mode)
        : m_mode(mode)
    {}

    template <class T>
    Buffer<T>::Buffer(const std::vector<T> &data, GLuint mode)
        : m_data(data), m_mode(mode)
    {
        transferBuffer();
    }

    template <class T>
    Buffer<T>::~Buffer() {
        glDeleteBuffers(1, &m_bufferIndex);
    }

    template <class T>
    void Buffer<T>::transferBuffer() {
        glGenBuffers(1, &m_bufferIndex);
        glBindBuffer(m_mode, m_bufferIndex);
        glBufferData(m_mode, m_data.size() * sizeof(T), &m_data[0], GL_STATIC_DRAW);
    }

    template <class T>
    void Buffer<T>::useBuffer() {
        glBindBuffer(m_mode, m_bufferIndex);
    }

    template <class T>
    void Buffer<T>::addElement(T element) {
        m_data.push_back(element);
    }

    template <class T>
    void Buffer<T>::addAll(const std::vector<T> &elements) {
        m_data.insert(std::end(m_data), std::begin(elements), std::end(elements));
    }

    template <class T>
    size_t Buffer<T>::size() {
        return m_data.size();
    }

    template class Buffer<int>;
    template class Buffer<float>;
}