#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <RootsNumber.hpp>
#include <Polynom.h>
#include <vector>

TEST_CASE("Polynomial", "[Polynom]") {

}

TEST_CASE("Roots amount") {
    SECTION("First example") {
        Polynom polynomial(5, {1,3,0,2});
        REQUIRE(rootsNumber(polynomial) == 0);
    }

    SECTION("Second example") {
        Polynom polynomial(5, {1,1,1,1});
        REQUIRE(rootsNumber(polynomial) == 3);
    }

    SECTION("Third example") {
        Polynom polynomial(5, {1,2,2,1});
        REQUIRE(rootsNumber(polynomial) == 1);
    }
}

