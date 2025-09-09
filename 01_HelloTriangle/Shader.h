#pragma once

#include <string>

class Shader
{
public:
    Shader(const char* sourcePath);
    ~Shader();

    inline const unsigned int getShader() const { return m_shaderID; }

private:
    unsigned int m_shaderID = 0;
    std::string m_shaderSource;
    std::string m_sourcePath;
    std::string m_shaderName;             // <- changed from const char*

    std::string loadShaderSource(const std::string& sourcePath);
    std::string getShaderType();          // <- return std::string
    inline const char* getShaderSource() { return m_shaderSource.c_str(); }
    bool contains(const std::string& str, const std::string& sub);
};
