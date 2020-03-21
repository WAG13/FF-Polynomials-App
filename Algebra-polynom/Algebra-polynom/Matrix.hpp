#pragma once

#include <vector>
#include <cassert>

class Matrix {
    std::vector<std::vector <long long>> _matrix;

public:
    long long _rows;
    long long _columns;

    Matrix(long long rows, long long columns): _rows(rows), _columns(columns),
        _matrix(std::vector<std::vector<long long>>(rows, std::vector<long long>(columns, 0))) {}

    explicit Matrix(Matrix& matrix) : _rows(matrix._rows), _columns(matrix._columns), _matrix(matrix._matrix) {}

    long long getElement(long long row, long long column) const;

    void setElement(long long row, long long column, long long key);

    long long rank();

private:
    void swapRows(int firstRow, int secondRow, int column);
};
