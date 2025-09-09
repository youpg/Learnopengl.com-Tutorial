#pragma once



class ElementBufferObject
{
public:
	ElementBufferObject(const void* data, unsigned int size);

	void bind() const;

private:
	unsigned int m_elementBufferObjectID;
};

