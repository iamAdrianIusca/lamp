#pragma once

#include "object.hpp"

class Shader final : public Object
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() = default;

    void use() const;

    void setBool(const std::string& name, bool value)   const;
    void setInt(const std::string& name, int value)     const;
    void setFloat(const std::string& name, float value) const;

    void setMat4(int index, float* data) const;
    void setVec3(int index, float* data) const;

    void init()    { }
    void release() { }

    #ifdef LAMP_WEB

    int attribute_location(const std::string& name)  const;
    int uniform_location(const std::string& name)    const;
    int uniform_block_index(const std::string& name) const;

    void block_binding(int index, int binding) const;

    #endif
};