#include "shader_stage.hpp"

ShaderStage::ShaderStage(const char* data, const int type)
{
    _handle = glCreateShader(type);

    glShaderSource(_handle, 1, &data, nullptr);
    glCompileShader(_handle);

    int  success;
    char infoLog[512];

    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_handle, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderStage::release()
{
    glDeleteShader(_handle);
}
