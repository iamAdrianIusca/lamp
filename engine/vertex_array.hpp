#pragma once

#include "object.hpp"

class VertexArray final : public Object
{
public:
    void init()    final;
    void release() final;
    void bind()    const;
};