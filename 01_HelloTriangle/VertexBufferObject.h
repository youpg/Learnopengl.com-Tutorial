#pragma once




class VertexBufferObject
{
public:
	VertexBufferObject(const void* data, unsigned int size);
	~VertexBufferObject();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_vertexBufferObjectID;
};

