#pragma once

#include "vertex.hpp"
#include "submesh.hpp"

struct model
{
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<submesh>      submeshes;

    static model merge(const std::vector<model>& models, bool single);
};