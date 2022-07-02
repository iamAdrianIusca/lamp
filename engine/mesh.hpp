#pragma once

#include "vertex_array.hpp"
#include "submesh.hpp"

struct Mesh
{
    Mesh(uint32_t primitive);

    VertexArray*         vao;
    std::vector<submesh> submeshes;

    void bind()          const;
    void draw(int index) const;

    uint32_t _primitive;
};