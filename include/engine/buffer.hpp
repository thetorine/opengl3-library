#pragma once

#include <vector>
#include <GL/glew.h>

namespace engine {
	template <class T>
	class Buffer {
	public:
		Buffer(GLuint mode);
		Buffer(std::vector<T> &data, GLuint mode);
		~Buffer();
		void transferBuffer();
		void useBuffer();

		void addElement(T element);
		void addAll(std::vector<T> &elements);
		size_t size();
	private:
		GLuint m_bufferIndex;
		std::vector<T> m_data;
		GLuint m_mode;
	};
}