#include "VertexArrayObject.h"

#include <glad/glad.h>

#include "Debug.h"

#include <cstdint>


VertexArrayObject::VertexArrayObject()
{
	GLCall( glGenVertexArrays(1, &m_vertexArrayObjectID) );
	bind();
}

VertexArrayObject::~VertexArrayObject()
{
    GLCall( glDeleteVertexArrays(1, &m_vertexArrayObjectID) );
}

void VertexArrayObject::bind() const
{
	GLCall( glBindVertexArray(m_vertexArrayObjectID) );
}


void VertexArrayObject::addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& layout)
{
    bind();
    vbo.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& e = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(
            i,
            e.count,
            e.type,
            e.normalized,
            layout.getStride(),
            (const void*)(uintptr_t)offset
        ));
        offset += e.count * VertexBufferLayout::getSizeOfType(e.type);
    }
}


void VertexArrayObject::draw(unsigned int count, unsigned int mode) const
{
    bind();
    GLCall( glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr) );
}