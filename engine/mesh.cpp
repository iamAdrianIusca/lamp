#include "mesh.hpp"

#include <glad/glad.h>
#include <cstddef>

void Mesh::draw(const int index) const
{
    const auto& submesh = submeshes[index];

    glDrawElements(GL_TRIANGLES, submesh.count, GL_UNSIGNED_INT, (std::byte*)(submesh.index * sizeof(unsigned int)));
}

void Mesh::bind() const
{
    vao->bind();
}
