#pragma once

#include "vertex_array.hpp"
#include "submesh.hpp"

#include <vector>

struct Mesh
{
    std::vector<submesh> submeshes;
    VertexArray*         vao;

    void bind() const;
    void draw(int index) const;
};