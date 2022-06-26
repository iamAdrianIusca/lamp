#pragma once

#include "object.hpp"

#include <cstdint>

class Buffer final : public Object
{
public:
	Buffer(uint32_t type, uint32_t usage, uint32_t size, void* data);
	~Buffer() = default;

	void bind()               const;
	void bind(uint32_t index) const;

	void init()    { }
	void release() { }

private:
    uint32_t _type;
};
