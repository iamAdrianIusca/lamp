#include "vertex_array.hpp"

#include <glad/glad.h>
#include <cassert>

void VertexArray::bind() const
{
    glBindVertexArray(_handle);
}

void VertexArray::init()
{
    glGenVertexArrays(1, &_handle);
    //glCreateVertexArrays(1, &_handle);
}

void VertexArray::release()
{
    #ifndef NDEBUG
    assert(glIsVertexArray(_handle));
    #endif

    glDeleteVertexArrays(1, &_handle);
}
