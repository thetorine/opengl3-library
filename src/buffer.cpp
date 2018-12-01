#include "buffer.hpp"

template <class T>
buffer<T>::buffer(GLuint mode) {
	this->mode = mode;
}

template <class T>
buffer<T>::buffer(std::vector<T> data, GLuint mode) {
	this->data = data;
	this->mode = mode;

	transferBuffer();
}

template <class T>
buffer<T>::~buffer() {

}

template <class T>
void buffer<T>::transferBuffer() {
	glGenBuffers(1, &bufferIndex);
	glBindBuffer(mode, bufferIndex);
	glBufferData(mode, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
}

template <class T>
void buffer<T>::useBuffer() {
	glBindBuffer(mode, bufferIndex);
}

template <class T>
void buffer<T>::addElement(T element) {
	data.push_back(element);
}

template <class T>
int buffer<T>::size() {
	return data.size();
}

template class buffer<int>;
template class buffer<float>;