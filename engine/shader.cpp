#include "shader.hpp"
#include "shader_stage.hpp"
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // create vertex shader stage
    ShaderStage vertexShader(vertexPath, GL_VERTEX_SHADER);
    // create fragment shader stage
    ShaderStage fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader.getId());
    glAttachShader(m_program, fragmentShader.getId());
    glLinkProgram(m_program);

    int success;
    char infoLog[512];

    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shader stages
    vertexShader.release();
    fragmentShader.release();
}

Shader::~Shader()
{
}

void Shader::use() const
{
    glUseProgram(m_program);
}

void Shader::setBool(const std::string &name, bool value) const
{
}

void Shader::setInt(const std::string &name, int value) const
{
}

void Shader::setFloat(const std::string &name, float value) const
{
}

void Shader::setMat4(int index, float* data)
{
    glUniformMatrix4fv(index, 1, GL_FALSE, data);
}

