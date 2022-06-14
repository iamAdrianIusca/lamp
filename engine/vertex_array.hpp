#pragma once

#include "object.hpp"

class VertexArray final : public Object
{
public:
    VertexArray();
    ~VertexArray() = default;

    void bind() const;
};