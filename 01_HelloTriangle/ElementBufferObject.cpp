#include "ElementBufferObject.h"

#include "glad/glad.h"
#include "Debug.h"


ElementBufferObject::ElementBufferObject(const void* data, unsigned int size)
{
	GLCall( glGenBuffers(1, &m_elementBufferObjectID) );
	bind();
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}


void ElementBufferObject::bind() const
{
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObjectID) );
}