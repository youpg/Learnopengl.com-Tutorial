#include "VertexBufferObject.h"

#include <glad/glad.h>


VertexBufferObject::VertexBufferObject(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_vertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_vertexBufferObjectID);
}

void VertexBufferObject::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectID);
}

void VertexBufferObject::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}