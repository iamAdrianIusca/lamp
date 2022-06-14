#include "vertex_array.hpp"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_vao);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_vao);
}
