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
    std::string m_shaderName;           

    std::string loadShaderSource(const std::string& sourcePath);
    std::string getShaderType();     
    inline const char* getShaderSource() { return m_shaderSource.c_str(); }
    bool contains(const std::string& str, const std::string& sub);
};
