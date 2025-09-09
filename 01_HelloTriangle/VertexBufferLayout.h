#pragma once
#include <vector>
#include <type_traits>

#include <glad/glad.h>
#include "Logger.hpp"


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_stride(0) {}

	template<typename T>
	void push(unsigned int count)
	{
		unsigned int type = 0;
		unsigned char normalized = GL_FALSE;

		if constexpr (std::is_same<T, float>::value)
		{
			type = GL_FLOAT;
			normalized = GL_FALSE;
		}
		else if constexpr (std::is_same<T, unsigned int>::value)
		{
			type = GL_UNSIGNED_INT;
			normalized = GL_FALSE;
		}
		else if constexpr (std::is_same<T, unsigned char>::value)
		{
			type = GL_UNSIGNED_BYTE;
			normalized = GL_TRUE;
		}
		else
		{
			if (sizeof(T) == 0)
				LOG_FATAL << "Unsupported type in VertexBufferLayout::push";
			else
				LOG_FATAL << "Uknown error in VertexBufferLayout::push";
		}

		m_elements.push_back({ type, count, normalized });
		m_stride += count * getSizeOfType(type);
	}


	inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
	inline unsigned int getStride() const { return m_stride; }

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
			default: return 0;
		}
	}


private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};