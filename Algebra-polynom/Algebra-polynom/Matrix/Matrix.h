#pragma once

#include <vector>
#include <cassert>
/**
 * @brief This class implements matrix representation and some useful methods as rank of matrix
 */
class Matrix {
    std::vector<std::vector <long long>> _matrix;

public:
    long long _rows;
    long long _columns;
    long long _prime;

    Matrix(long long rows, long long columns, long long prime): _rows(rows), _columns(columns), _prime(prime),
        _matrix(std::vector<std::vector<long long>>(rows, std::vector<long long>(columns, 0))) {}

     Matrix(const Matrix& matrix) : _rows(matrix._rows), _columns(matrix._columns),
        _prime(matrix._prime), _matrix(matrix._matrix) {}

    long long getElement(long long row, long long column) const;

    void setElement(long long row, long long column, long long key);

    Matrix transpose() const;

    std::pair<long long, Matrix> rank();

    /**
     * @brief Building a solution space basis of a system of linear equations with coefficients from the matrix
     */
    std::vector<std::vector<long long>> buildSolutionSpaceBasis();
private:
    /**
     * @brief Swapping two rows from 0 column to param column
     */
    void swapRows(long long firstRow, long long secondRow, long long columnStart, long long columnEnd);

    std::vector<long long> findNonConvertedColumns(long long kernel_dimension) const;
};
