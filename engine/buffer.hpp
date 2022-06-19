#pragma once

#include "object.hpp"

#include <cstdint>

class Buffer final : public Object
{
public:
	Buffer(unsigned int type, unsigned int usage, unsigned int size, void* data);
	~Buffer() = default;

	void bind()               const;
	void bind(uint32_t index) const;

	void init()    { }
	void release() { }

private:
    unsigned int m_type;
};
