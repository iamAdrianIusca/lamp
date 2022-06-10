#pragma once

class ShaderStage
{
public:
    ShaderStage(const char* data, int type);
    ~ShaderStage() = default;

    void release();

    unsigned int getId() const;

private:
    unsigned int m_id;
};