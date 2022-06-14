#pragma once

class VertexArray
{
public:
    VertexArray();
    ~VertexArray() = default;

    void bind() const;

private:
    unsigned int m_vao;
};