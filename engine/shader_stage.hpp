#pragma once

class ShaderStage
{
public:
    ShaderStage(const char* data, int type);
    ~ShaderStage();

    void release();

    unsigned int getId() const;

private:
    unsigned int m_id;
};