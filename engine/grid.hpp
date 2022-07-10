#pragma once

template <typename Type, int32_t _rows, int32_t _columns>
class Grid
{
public:
    [[nodiscard]] int32_t rows()    const { return _rows; }
    [[nodiscard]] int32_t columns() const { return _columns; }

    Type& item(const int32_t row, const int32_t column)
    {
        assert(row    < _rows);
        assert(column < _columns);

        return _items[row][column];
    }

protected:
    Type _items[_rows][_columns];
};
