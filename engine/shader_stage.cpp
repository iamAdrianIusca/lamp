#include "shader_stage.hpp"

#include <glad/glad.h>
#include <iostream>

ShaderStage::ShaderStage(const char *data, int type)
{
    m_id = glCreateShader(type);
    glShaderSource(m_id, 1, &data, nullptr);
    glCompileShader(m_id);
    int success;
    char infoLog[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

ShaderStage::~ShaderStage()
{

}

void ShaderStage::release()
{
    glDeleteShader(m_id);
}

unsigned int ShaderStage::getId() const
{
    return m_id;
}
