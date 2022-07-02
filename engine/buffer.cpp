#include "buffer.hpp"

Buffer::Buffer(uint32_t type, uint32_t usage, uint32_t size, void *data)
    : _type { type }
{
    glGenBuffers(1, &_handle);
    glBindBuffer(_type, _handle);
    glBufferData(_type, size, data, usage);
}

void Buffer::bind() const
{
    glBindBuffer(_type, _handle);
}

void Buffer::bind(uint32_t index) const
{
    assert(_type == GL_UNIFORM_BUFFER);

    glBindBufferBase(_type, index, _handle);
}
