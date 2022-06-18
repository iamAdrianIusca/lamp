#pragma once

#include "object.hpp"

class Buffer final : public Object
{
public:
	Buffer(unsigned int type, unsigned int usage, unsigned int size, void* data);
	~Buffer() = default;

	void bind() const;

	void init()    { }
	void release() { }

private:
    unsigned int m_type;
};
