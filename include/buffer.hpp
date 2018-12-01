#pragma once

#include <vector>
#include <GL/glew.h>

template <class T>
class buffer
{
public:
	buffer(GLuint mode);
	buffer(std::vector<T> &data, GLuint mode);
	~buffer();
	void transferBuffer();
	void useBuffer();
	
	void addElement(T element);
	void addAll(std::vector<T> &elements);
	size_t size();
private:
	GLuint bufferIndex;
	std::vector<T> data;
	GLuint mode;
};