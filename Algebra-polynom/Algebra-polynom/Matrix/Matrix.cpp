#include "Matrix.h"

namespace utils {
    long long division_for_numbers(long long a, long long b, long long prime);
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

void Matrix::swapRows(long long firstRow, long long secondRow, long long column) {
    for (long long i = 0; i < column; i++) {
        long long temp = _matrix[firstRow][i];
        _matrix[firstRow][i] = _matrix[secondRow][i];
        _matrix[secondRow][i] = temp;
    }
}

std::pair<long long, Matrix> Matrix::rank() {
    long long rank = _columns;
    Matrix matrixCopy(*this);

    for (long long row = 0; row < rank; row++) {
        if (matrixCopy.getElement(row,row) != 0) {
            for (long long col = 0; col < _rows; col++) {
                if (col != row) {
                    long long multi = utils::division_for_numbers(matrixCopy.getElement(col,row),
                            matrixCopy.getElement(row,row), _prime);

                    for (long long i = 0; i < rank; i++) {
                        matrixCopy.setElement(col,i,
                                              static_cast<long long>(matrixCopy.getElement(col,i) - multi * matrixCopy.getElement(row,i)));
                    }
                }
            }
        } else {
            bool allZeros = true;
            for (long long i = row + 1; i < _rows;  i++) {
                if (matrixCopy.getElement(i,row) != 0) {
                    matrixCopy.swapRows(row, i, rank);
                    allZeros = false;
                    break;
                }
            }

            if (allZeros) {
                rank--;
                for (long long i = 0; i < _rows; i++) {
                    matrixCopy.setElement(i,row, matrixCopy.getElement(i,rank));
                }
            }
            row--;
        }
    }
    return {rank, matrixCopy};
}

std::vector<long long> Matrix::findZeroColumns() const {
    std::vector<long long> result;
    bool all_zero;

    for (long long i = 0; i < _columns; i++) {
        all_zero = true;
        for (long long j = 0; j < _rows; j++) {
            if (_matrix[j][i]) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) result.push_back(i);
    }

    return result;
}

std::vector<std::vector<long long>> Matrix::buildSolutionSpaceBasis() {
    auto rank_pair = rank();
    long long kernel_dimension = _columns - rank_pair.first;
    Matrix converted_matrix = rank_pair.second;
    auto zero_columns = findZeroColumns();
    std::vector<long long> coefficients;
    std::vector<std::vector<long long>> basis;

    for (long long i = 0; i < kernel_dimension; i++) {
        long long j = zero_columns[i];
        long long current_zero_column = 0;

        for (long long k = 0; k < _columns; k++) {
            if (current_zero_column < zero_columns.size() && zero_columns[current_zero_column] == k && k != j) {
                coefficients.push_back(0);
                current_zero_column++;
            }
            else if (k == j) {
                coefficients.push_back(-1);
                current_zero_column++;
            }
            else {
                if (k - current_zero_column < _rows) {
                    coefficients.push_back(_matrix[k - current_zero_column][j]);
                }
                else {
                    coefficients.push_back(0);
                }
            }
        }

        for (long long k = coefficients.size() - 1; k > 0; k--) {
            if (coefficients[k] == 0) {
                coefficients.erase(coefficients.begin() + k);
            }
            else break;
        }

        basis.push_back(coefficients);
    }

    return basis;
}