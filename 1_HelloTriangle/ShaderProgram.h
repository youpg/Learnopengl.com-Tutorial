#pragma once

#include "Shader.h"

#include <memory>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use() const;


	void loadShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		m_vertexShader = std::make_unique<Shader>(vertexShaderPath);
		m_fragmentShader = std::make_unique<Shader>(fragmentShaderPath);
	}


private:
	unsigned int m_shaderProgramID;

	std::unique_ptr<Shader> m_vertexShader;
	std::unique_ptr<Shader> m_fragmentShader;

	void attachShaders(const char* vertexShaderPath, const char* fragmentShaderPath);


};

