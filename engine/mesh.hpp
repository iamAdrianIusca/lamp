#pragma once

#include "vertex_array.hpp"

#include <vector>

struct submesh
{
    unsigned int start_index;
    unsigned int index_count;
};

struct Mesh
{
    std::vector<submesh> submeshes;
    VertexArray          vao;

    void bind() const;
    void draw(int index) const;
};