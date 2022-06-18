#pragma once

#include "vertex_array.hpp"
#include "submesh.hpp"

#include <vector>

struct Mesh
{
    VertexArray*         vao;
    std::vector<submesh> submeshes;

    void bind()          const;
    void draw(int index) const;
};