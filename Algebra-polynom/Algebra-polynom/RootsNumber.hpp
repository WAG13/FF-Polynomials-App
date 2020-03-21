#pragma once

#include <vector>
#include <Polynom.h>
#include <Matrix.hpp>

long long rootsNumber (const Polynom& polynomial) {
    long long power = polynomial.getPower() - 1;
    Matrix AMatrix(power, power);

    for (long long i = 0, shift = 0; i < power; i++, shift++) {
        for (long long j = 0; j <= power; j++) {
            AMatrix.setElement(i,j,polynomial.getTerm((j+shift) % power)->key);
        }
    }

    long long matrixRank = AMatrix.rank();
    return (power - matrixRank);
}

