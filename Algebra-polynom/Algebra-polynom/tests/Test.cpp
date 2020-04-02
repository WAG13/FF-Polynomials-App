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
        REQUIRE(polynomial.getTerm(0)->key == 1);
        REQUIRE(polynomial.getTerm(1)->key == 2);
    }
    SECTION("Creating empty polynom") {
        Polynom polynomial(3, 2, { 3,6 });
        REQUIRE(polynomial.getHead() == nullptr);
    }
    SECTION("Adding polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2(3, 2, { 2,1 });
        REQUIRE((poly1 + poly2).getHead() == nullptr);
    }
    SECTION("Substract polynoms") {
        Polynom poly1(3, 2, { 1,2 });
        Polynom poly2(3, 2, { 1,2 });
        REQUIRE((poly1 - poly2).getHead() == nullptr);
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
