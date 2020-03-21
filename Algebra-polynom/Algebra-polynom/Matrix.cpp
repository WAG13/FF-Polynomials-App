#include <Matrix.hpp>


long long Matrix::getElement(long long row, long long column) const {
    assert(row < _rows);
    assert(column < _columns);

    return _matrix[row][column];
}

void Matrix::setElement(long long row, long long column, long long key) {
    assert(row < _rows);
    assert(column < _columns);

    _matrix[row][column] = key;
}

void Matrix::swapRows(int firstRow, int secondRow, int column) {
    for (long long i = 0; i < column; i++) {
        long long temp = _matrix[firstRow][i];
        _matrix[firstRow][i] = _matrix[secondRow][i];
        _matrix[secondRow][i] = temp;
    }
}

long long Matrix::rank() {
    long long rank = _columns;
    Matrix matrixCopy(*this);

    for (int row = 0; row < rank; row++) {
        if (matrixCopy.getElement(row,row)!= 0) {
            for (int col = 0; col < _rows; col++) {
                if (col != row) {
                    double multi = (double)matrixCopy.getElement(col,row) /
                                   matrixCopy.getElement(row,row);
                    for (int i = 0; i < rank; i++) {
                        matrixCopy.setElement(col,i,
                                              static_cast<long long>(matrixCopy.getElement(col,i) - multi * matrixCopy.getElement(row,i)));
                    }
                }
            }
        } else {
            bool allZeros = true;
            for (int i = row + 1; i < _rows;  i++) {
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
    return rank;
}

