#include "buffer.hpp"

#include <glad/glad.h>

Buffer::Buffer(unsigned int type, unsigned int usage, unsigned int size, void *data)
    : m_type { type }
{
    glGenBuffers(1, &_handle);
    glBindBuffer(m_type, _handle);
    glBufferData(m_type, size, data, usage);
}

void Buffer::bind() const
{
    glBindBuffer(m_type, _handle);
}

void Buffer::bind(uint32_t index) const
{
    glBindBufferBase(m_type, index, _handle);
}
