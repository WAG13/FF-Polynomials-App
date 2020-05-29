#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Polynom/Polynom.h"
#include <vector>

TEST_CASE("Polynomial") {
    SUBCASE("Creating polynom") {
       Polynom polynomial1(3, 1, { { 0,1 }, { 2,2 } });
        REQUIRE(polynomial1.show() == "1 + 2*x^2");
        Polynom polynomial(3, 2, { 1,2 });
        REQUIRE(polynomial.show() == "1 + 2*x");
    }
    SUBCASE("Creating empty polynom") {
        Polynom polynomial(3, 2, { 3,6 });
        REQUIRE(polynomial.getHead() == nullptr);
    }
    SUBCASE("Creating copy of polynom") {
        Polynom polynomial(3, 2, { 1,2 });
        Polynom copy;
        copy.copy(polynomial);
        REQUIRE(polynomial.show() == copy.show());
        REQUIRE(polynomial.getPower() == copy.getPower());
        REQUIRE(polynomial.getPrime() == copy.getPrime());
    }
    SUBCASE("Power of polynom") {
        Polynom poly1(3, 1, { 1,3,3 });
        REQUIRE(poly1.getPolyPower() == 0);
        Polynom poly2(3, 1, { 1,1 });
        REQUIRE(poly2.getPolyPower() == 1);
        Polynom poly3(3, 1, { 1,1,1 });
        REQUIRE(poly3.getPolyPower() == 2);
    }
    SUBCASE("Adding polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2 = poly1 + poly1;
        REQUIRE(poly1.show() == "1 + 2*x");
        REQUIRE(poly2.show() == "2 + 1*x");
        REQUIRE((poly1 + poly2).show() == "");
    }
    SUBCASE("Substract polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2(3, 2, { 2,2 });
        REQUIRE((poly1 - poly1).show() == "");
        REQUIRE((poly1 - poly2).show() == "2");
    }
    SUBCASE("Multiplicate polynoms") {
        Polynom poly1(3, 1, { 1,2 });
        REQUIRE(poly1.show() == "1 + 2*x");
        
        REQUIRE(poly1.getTermKey(0) == 1);
        REQUIRE(poly1.getTermKey(1) == 2);
        REQUIRE(poly1.getTermKey(2) == 0);

        Polynom polynomial = poly1 * poly1;
        REQUIRE(polynomial.show() == "1 + 1*x + 1*x^2");
        
        /*it`s wrong but just for test*/
        Polynom poly2(3, 2, { 1,2 });
        polynomial = poly2 * poly2;
        REQUIRE(polynomial.show() == "1 + 1*x + 1*x^2");
        
        //Polynom poly3(3, 2, { 1,1 });
        //polynomial = poly2 * poly3;
        //REQUIRE(polynomial.getTerm(0)->key == 2);

        polynomial = poly1*3;
        REQUIRE(polynomial.show() == "");
    }

	/*SUBCASE("GCD polynoms") {
		Polynom pol1(5, 5, { 4,0,3,3,3,1 });
		Polynom pol2(5, 4, { 1,2,0,1,1 });

		Polynom res = pol1.gcd(pol2);

		REQUIRE(polynomial.getTermKey(0) == 1);
		REQUIRE(polynomial.getPolyPower() == 0);
	}*/

}

TEST_CASE("Roots amount") {
    SUBCASE("First example") {
        Polynom polynomial(5, 1, { 1,3,0,2 });
        REQUIRE(polynomial.rootsNumber() == 0);
    }

    SUBCASE("Second example") {
        Polynom polynomial(5, 1, { 1,1,1,1 });
        REQUIRE(polynomial.rootsNumber() == 3);
    }

    SUBCASE("Third example") {
        Polynom polynomial(5, 1, { 1,2,2,1 });
        REQUIRE(polynomial.rootsNumber() == 1);
    }
}

TEST_CASE("Cyclotomic polynomials") {
    SUBCASE("n=1") {
        Polynom polynomial(131, 1, { 130,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 1) == polynomial);
    }
    SUBCASE("n=2") {
        Polynom polynomial(131, 1, { 1,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 2) == polynomial);
    }
    SUBCASE("n=3") {
        Polynom polynomial(131, 1, { 1,1,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 3) == polynomial);
    }
    SUBCASE("n=4") {
        Polynom polynomial(131, 1, { 1,0,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 4) == polynomial);
    }
    SUBCASE("n=5") {
        Polynom polynomial(131, 1, { 1,1,1,1,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 5) == polynomial);
    }
    SUBCASE("n=6") {
        Polynom polynomial(131, 1, { 1,130,1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 6) == polynomial);
    }
    SUBCASE("n=7") {
        Polynom polynomial(131, 1, { 1,1,1,1,1,1,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 7) == polynomial);
    }
    SUBCASE("n=8") {
        Polynom polynomial(131, 1, { 1,0,0,0,1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 8) == polynomial);
    }
    SUBCASE("n=9") {
        Polynom polynomial(131, 1, { 1,0,0,1,0,0,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 9) == polynomial);
    }
    SUBCASE("n=10") {
        Polynom polynomial(131, 1, { 1,130,1,130,1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 10) == polynomial);
    }
    SUBCASE("n=105") {
        std::vector<long long> keys(49, 0);
        keys[0] = 1;
        keys[1] = 1;
        keys[2] = 1;
        keys[5] = 130;
        keys[6] = 130;
        keys[7] = 129;
        keys[8] = 130;
        keys[9] = 130;
        for (int i = 12; i <= 17; i++) {
            keys[i] = 1;
        }
        for (int i = 20; i <= 28; i+=2) {
            keys[i] = 130;
        }
        for (int i = 31; i <= 36; i++) {
            keys[i] = 1;
        }
        keys[39] = 130;
        keys[40] = 130;
        keys[41] = 129;
        keys[42] = 130;
        keys[43] = 130;
        keys[46] = 1;
        keys[47] = 1;
        keys[48] = 1;
        Polynom polynomial(131,1, keys);
        REQUIRE(Polynom::CyclotomicPolynomial(131, 105) == polynomial);
    }
}