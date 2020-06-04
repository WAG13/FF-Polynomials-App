#include "Polynom/Polynom.h"
#include "Polynom/GaloisField.h"
#include <iostream>

int main() {
    Polynom p{ 5, { {0, 1}, {1, 2}, {2, 1}, {5, 2} } };
    std::cout << p.berlekampAlgorithm();
    return 1;
}
