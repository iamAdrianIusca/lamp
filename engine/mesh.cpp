#include "mesh.hpp"

#include <glad/glad.h>

void Mesh::draw(int index) const
{
    const submesh& submesh = submeshes[index];

    glDrawElements(GL_TRIANGLES, submesh.count, GL_UNSIGNED_INT, (void*)(submesh.index * sizeof(unsigned int)));
}

void Mesh::bind() const
{
    vao->bind();
}
