#include "shader.hpp"
#include "shader_stage.hpp"

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

void Shader::setMat4(const int index, float* data) const
{
    glUniformMatrix4fv(index, 1, GL_FALSE, data);
}

void Shader::setVec3(const int index, float* data) const
{
    glUniform3fv(index, 1, data);
}

#ifdef LAMP_WEB

int Shader::attribute_location(const std::string& name) const
{
    return glGetAttribLocation(_handle, name.c_str());
}

int Shader::uniform_location(const std::string& name) const
{
    return glGetUniformLocation(_handle, name.c_str());
}

int Shader::uniform_block_index(const std::string& name) const
{
    return glGetUniformBlockIndex(_handle, name.c_str());
}

void Shader::block_binding(int index, int binding) const
{
    glUniformBlockBinding(_handle, index, binding);
}

#endif
