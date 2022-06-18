#include "shader.hpp"
#include "shader_stage.hpp"

#include <glad/glad.h>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    ShaderStage vertexShader(vertexPath,     GL_VERTEX_SHADER);
    ShaderStage fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);

    _handle = glCreateProgram();

    glAttachShader(_handle, vertexShader.handle());
    glAttachShader(_handle, fragmentShader.handle());

    glLinkProgram(_handle);

    int success;
    char infoLog[512];

    glGetProgramiv(_handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_handle, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    vertexShader.release();
    fragmentShader.release();
}

void Shader::use() const
{
    glUseProgram(_handle);
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

void Shader::setVec3(int index, float *data)
{
    glUniform3fv(index, 1, data);
}

