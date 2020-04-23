#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../Polynom/Polynom.h"
#include <vector>
#include <string>

TEST_CASE("Polynomial", "[Polynom]") {
    SECTION("Creating polynom") {
        Polynom polynomial(3, 2, { 1,2 });
        REQUIRE(polynomial.getHead() != nullptr);
        REQUIRE(polynomial.getTermKey(0) == 1);
        REQUIRE(polynomial.getTermKey(1) == 2);
    }
    SECTION("Creating empty polynom") {
        Polynom polynomial(3, 2, { 3,6 });
        REQUIRE(polynomial.getHead() == nullptr);
    }
    SECTION("Creating copy of polynom") {
        Polynom polynomial(3, 2, { 1,2 });
        Polynom copy;
        copy.copy(polynomial);

        REQUIRE(polynomial.getPower() == copy.getPower());
        REQUIRE(polynomial.getPrime() == copy.getPrime());
        REQUIRE(polynomial.getTermKey(0) == copy.getTermKey(0));
        REQUIRE(polynomial.getTermKey(1) == copy.getTermKey(1));
    }
    SECTION("Power of polynom") {
        Polynom poly1(3, 1, { 1,3,3 });
        REQUIRE(poly1.getPolyPower() == 0);
        Polynom poly2(3, 1, { 1,1 });
        REQUIRE(poly2.getPolyPower() == 1);
        Polynom poly3(3, 1, { 1,1,1 });
        REQUIRE(poly3.getPolyPower() == 2);
    }
    SECTION("Adding polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2 = poly1 + poly1;
        REQUIRE(poly2.getTermKey(0) == 2);
        REQUIRE(poly2.getTermKey(1) == 1);
        REQUIRE(poly1.getTermKey(0) == 1);
        REQUIRE(poly1.getTermKey(1) == 2);
        REQUIRE((poly1 + poly2).getHead() == nullptr);
    }
    SECTION("Substract polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2(3, 2, { 2,2 });
        REQUIRE((poly1 - poly1).getHead() == nullptr);
        REQUIRE((poly1 - poly2).getTermKey(0) == 2);
    }
    SECTION("Multiplicate polynoms") {
        Polynom poly1(3, 1, { 1,2 });
        
        REQUIRE(poly1.getTermKey(0) == 1);
        REQUIRE(poly1.getTermKey(1) == 2);
        REQUIRE(poly1.getTermKey(2) == 0);

        Polynom polynomial = poly1 * poly1;
        REQUIRE(polynomial.getTermKey(0) == 1);
        REQUIRE(polynomial.getTermKey(1) == 1);
        REQUIRE(polynomial.getTermKey(2) == 1);
        
        /*it`s wrong but just for test*/
        Polynom poly2(3, 2, { 1,2 });
        polynomial = poly2 * poly2;
        REQUIRE(polynomial.getTermKey(0) == 1);
        REQUIRE(polynomial.getTermKey(1) == 1);
        REQUIRE(polynomial.getTermKey(2) == 1);
        
        //Polynom poly3(3, 2, { 1,1 });
        //polynomial = poly2 * poly3;
        //REQUIRE(polynomial.getTerm(0)->key == 2);

        polynomial = poly1*3;
        polynomial.show();
        REQUIRE(polynomial.getHead()==nullptr);
    }

	SECTION("GCD polynoms") {
		Polynom pol1(3, 5, { 4,0,3,3,3,1 });
		Polynom pol2(3, 4, { 1,2,0,1,1 });

		Polynom res = pol1.gcd(pol2);

		REQUIRE(polynomial.getTermKey(0) == 1);
		REQUIRE(polynomial.getPolyPower() == 0);
	}

}

TEST_CASE("Roots amount") {
    SECTION("First example") {
        Polynom polynomial(5, 1, { 1,3,0,2 });
        REQUIRE(polynomial.rootsNumber() == 0);
    }

    SECTION("Second example") {
        Polynom polynomial(5, 1, { 1,1,1,1 });
        REQUIRE(polynomial.rootsNumber() == 3);
    }

    SECTION("Third example") {
        Polynom polynomial(5, 1, { 1,2,2,1 });
        REQUIRE(polynomial.rootsNumber() == 1);
    }
}
