#pragma once

#include "object.hpp"

class ShaderStage final : public Object
{
public:
    ShaderStage(const char* data, int type);
    ~ShaderStage() = default;

    void init() { }
    void release();
};