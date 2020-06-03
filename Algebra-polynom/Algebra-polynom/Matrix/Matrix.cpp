#include "Matrix.h"

namespace utils {
    long long inverse(long long number, long long prime);
}

long long Matrix::getElement(long long row, long long column) const {
    assert(row < _rows);
    assert(column < _columns);

    return _matrix[row][column];
}

void Matrix::setElement(long long row, long long column, long long key) {
    assert(row < _rows);
    assert(column < _columns);

    if (key < 0) {
        do {
            key = key + _prime;
        } while (key < 0);
    } else {
        key = key % _prime;
    }
    _matrix[row][column] = key;
}

void Matrix::swapRows(long long firstRow, long long secondRow, long long columnStart, long long columnEnd) {
    for (long long i = columnStart; i < columnEnd; i++) {
        long long temp = _matrix[firstRow][i];
        _matrix[firstRow][i] = _matrix[secondRow][i];
        _matrix[secondRow][i] = temp;
    }
}

std::pair<long long, Matrix> Matrix::rank() {
    long long rank = 0;
    Matrix matrixCopy(*this);

    for (long long row = 0, col = 0; row < _rows && col < _columns; col++) {
        if (matrixCopy.getElement(row, col) != 0) {
            /*converting element [row, col] to 1, changing other row's elements respectively*/
            long long inverse = utils::inverse(matrixCopy.getElement(row, col), _prime);
            for (long long i = 0; i < _columns; i++) {
                matrixCopy.setElement(row, i, (matrixCopy.getElement(row, i) * inverse) % _prime);
            }

            for (long long i = 0; i < _rows; i++) {
                if (i != row) {
                    long long multi = matrixCopy.getElement(i, col);

                    if (multi) {
                        for (long long j = col; j < _columns; j++) {
                            matrixCopy.setElement(i, j,
                                static_cast<long long>(matrixCopy.getElement(i, j) - multi * matrixCopy.getElement(row, j)));
                        }
                    }
                }
            }

            rank++;
            row++;
        } else {
            for (long long i = row + 1; i < _rows;  i++) {
                if (matrixCopy.getElement(i, col) != 0) {
                    /*we swap rows starting from col element, because on the left everything is 0 and swapping is useless*/
                    matrixCopy.swapRows(row, i, col, _columns);
                    col--;
                    break;
                }
            }
        }
    }
    return {rank, matrixCopy};
}

Matrix Matrix::transpose() const {
    Matrix result(_columns, _rows, _prime);
    for (long long i = 0; i < _rows; i++) {
        for (long long j = 0; j < _columns; j++) {
            result.setElement(i, j, _matrix[j][i]);
        }
    }
    return result;
}

std::vector<long long> Matrix::findNonConvertedColumns(long long kernel_dimension) const {
    std::vector<long long> result;
    std::vector<bool> converted(_rows, false);

    for (long long i = 0; result.size() < kernel_dimension; i++) {
        bool identity_spotted = false;
        long long identity_row_index = 0;

        for (long long j = 0; j < _rows; j++) {
            if (_matrix[j][i]) {
                if (!identity_spotted) {
                    identity_spotted = true;
                    identity_row_index = j;
                }
                else {
                    identity_spotted = false;
                    break;
                }
            }
        }

        if (!identity_spotted) {
            result.push_back(i);
        }
        else {
            if (!converted[identity_row_index]) {
                converted[identity_row_index] = true;
            }
            else {
                result.push_back(i);
            }
        }
    }

    return result;
}

std::vector<std::vector<long long>> Matrix::buildSolutionSpaceBasis() {
    Matrix converted_matrix(*this);
    converted_matrix = converted_matrix.transpose();
    auto rank_pair = converted_matrix.rank();
    long long kernel_dimension = _columns - rank_pair.first;
    converted_matrix = rank_pair.second;
    auto non_converted_columns = converted_matrix.findNonConvertedColumns(kernel_dimension);
    std::vector<std::vector<long long>> basis(kernel_dimension);

    for (long long i = 0; i < basis.size(); i++) {
        basis[i].resize(_columns);
        for (long long j = 0; j < _columns; j++) {
            basis[i][j] = 0;
        }
        basis[i][non_converted_columns[i]] = 1;
    }

    for (long long k = 0; k < basis.size(); k++) {
        long long corresponding_column = non_converted_columns[k];
        long long non_converted_columns_passed = 0;

        for (long long i = 0, j = 0; i < _rows && j < _columns; i++, j++) {
            if (converted_matrix.getElement(i, corresponding_column)) {
                if (j == non_converted_columns[non_converted_columns_passed]) {
                    non_converted_columns_passed++;
                    i--;
                }
                else {
                    basis[k][j] = _prime - converted_matrix.getElement(i, corresponding_column);
                }
            }
        }
    }

    return basis;
}