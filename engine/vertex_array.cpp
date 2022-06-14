#include "vertex_array.hpp"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_handle);
}

void VertexArray::bind() const
{
    glBindVertexArray(_handle);
}
