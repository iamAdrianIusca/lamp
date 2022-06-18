#pragma once

#include "object.hpp"

#include <string>

class Shader final : public Object
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() = default;

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    void setMat4(int index, float* data);
    void setVec3(int index, float* data);

    void init()    { }
    void release() { }
};