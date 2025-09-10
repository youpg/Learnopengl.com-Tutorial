#include "ShaderProgram.h"

#include <glad/glad.h>

#include "Debug.h"
#include "Logger.hpp"

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	m_shaderProgramID = glCreateProgram();

	attachShaders(vertexShaderPath, fragmentShaderPath);
	GLCall( glLinkProgram(m_shaderProgramID) );

	int success;
	char infoLog[512];
	GLCall( glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success) );
	if (!success)
	{
		GLCall(glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog));
		LOG_FATAL << "Program linking failed\n" << infoLog;
	}
	else LOG_INFO << "Program linking succeeded";
}

void ShaderProgram::use() const
{
	GLCall( glUseProgram(m_shaderProgramID) );
}





void ShaderProgram::attachShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	loadShaders(vertexShaderPath, fragmentShaderPath);

	GLCall( glAttachShader(m_shaderProgramID, m_vertexShader.get()->getShader()) );
	GLCall( glAttachShader(m_shaderProgramID, m_fragmentShader.get()->getShader()) );
}