#include "Shader.h"
#include "Logger.hpp"

#include <fstream>
#include <glad/glad.h>
#include "Debug.h"
#include <stdexcept>

Shader::Shader(const char* sourcePath)
    : m_sourcePath(sourcePath)
{
    m_shaderName = getShaderType();                    // now std::string
    m_shaderSource = loadShaderSource(sourcePath);

    if (m_shaderName == "vertex")
    {
        m_shaderID = GLCall( glCreateShader(GL_VERTEX_SHADER) );
    }
    else if (m_shaderName == "fragment")
    {
        m_shaderID = GLCall( glCreateShader(GL_FRAGMENT_SHADER) );
    }
    else
    {
        LOG_FATAL << "Invalid Shader Type for file: " << sourcePath;
        throw std::runtime_error("Invalid shader type (must contain 'vertex' or 'fragment' in path).");
    }

    if (m_shaderID == 0)
    {
        LOG_FATAL << "Failed to create shader object for: " << sourcePath;
        throw std::runtime_error("glCreateShader failed");
    }

    const char* src = getShaderSource();
    GLCall( glShaderSource(m_shaderID, 1, &src, NULL) );
    GLCall( glCompileShader(m_shaderID) );

    int success = 0;
    char infoLog[1024];
    GLCall( glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success) );
    if (!success)
    {
        GLCall( glGetShaderInfoLog(m_shaderID, 1024, NULL, infoLog) );
        LOG_FATAL << m_shaderName << " Shader compilation failed\n" << infoLog
                  << "\n\nSource:\n" << m_shaderSource;
        throw std::runtime_error("Shader compilation failed");
    }
    else
    {
        LOG_INFO << m_shaderName << " Shader compilation succeeded";
    }
}

Shader::~Shader()
{
    if (m_shaderID != 0)
        GLCall( glDeleteShader(m_shaderID) );
}

std::string Shader::loadShaderSource(const std::string& sourcePath)
{
    std::ifstream file(sourcePath, std::ios::in | std::ios::binary);
    if (!file)
    {
        LOG_FATAL << "Failed to load shader: " << sourcePath;
        return "";
    }
    else LOG_INFO << "Loaded shader file: " << sourcePath;

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

std::string Shader::getShaderType()
{
    if (contains(m_sourcePath, "vertex")) return "vertex";
    if (contains(m_sourcePath, "fragment")) return "fragment";
    return ""; // unknown
}

bool Shader::contains(const std::string& str, const std::string& sub)
{
    return str.find(sub) != std::string::npos;
}
