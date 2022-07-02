#include "mesh.hpp"

Mesh::Mesh(const uint32_t primitive)
    : _primitive { primitive }
{
}

void Mesh::draw(const int index) const
{
    const auto& submesh = submeshes[index];

    glDrawElements(_primitive, submesh.count, GL_UNSIGNED_INT, reinterpret_cast<std::byte*>(submesh.index));
}

void Mesh::bind() const
{
    vao->bind();
}
