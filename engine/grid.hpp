#pragma once

template <typename T, std::size_t size> class Grid
{
public:
    Grid(int32_t rows, int32_t columns);

    [[nodiscard]] int32_t rows()    const { return _rows; }
    [[nodiscard]] int32_t columns() const { return _columns; }
    [[nodiscard]] int32_t length()  const { return  size; }

    T& operator[](int32_t index);

protected:
    int32_t _rows;
    int32_t _columns;

    T _items[size];
};

#pragma region definitions

template<typename T, std::size_t size> Grid<T, size>::Grid(const int32_t rows, const int32_t columns)
    : _rows    { rows }
    , _columns { columns }
{
}

template<typename T, std::size_t size> T& Grid<T, size>::operator[](const int32_t index)
{
    assert(index < size);
    return _items[index];
}

#pragma endregion