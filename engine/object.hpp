#pragma once

class Object
{
public:
    virtual void init()    = 0;
    virtual void release() = 0;

    unsigned int handle() const;

protected:
    unsigned int _handle;
};
