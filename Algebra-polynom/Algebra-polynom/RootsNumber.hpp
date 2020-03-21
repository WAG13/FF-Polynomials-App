#pragma once

#include <vector>
#include <Polynom.h>
#include <Matrix.hpp>

/**
 * @brief This function implements algorithm  for finding number of roots for polynomial
 *      in accordance with Konig-Rados theorem
 */
long long rootsNumber (const Polynom& polynomial) {
    long long power = polynomial.getPower() - 1;
    Matrix AMatrix(power, power);

    for (long long i = 0, shift = 0; i < power; i++, shift++) {
        for (long long j = 0; j < power; j++) {
            auto currTerm = polynomial.getTerm((j+shift) % power);
            if (currTerm!= nullptr) {
                AMatrix.setElement(i,j,currTerm->key);
            } else {
                AMatrix.setElement(i,j,0);
            }
        }
    }

    long long matrixRank = AMatrix.rank();
    return (power - matrixRank);
}

