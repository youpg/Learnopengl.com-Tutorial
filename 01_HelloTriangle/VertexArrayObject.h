#pragma once


//class VertexBufferObject;
//class VertexBufferLayout;
#include "VertexBufferObject.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>



class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();


	void bind() const;
	void addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& layout);

	void draw(unsigned int count, unsigned int mode = GL_TRIANGLES) const;

private:
	unsigned int m_vertexArrayObjectID;
};