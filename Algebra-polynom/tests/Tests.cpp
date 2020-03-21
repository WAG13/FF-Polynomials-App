#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <RootsNumber.hpp>
#include <Polynom.h>
#include <vector>

TEST_CASE("Polynom", "[Polynom]") {

}

TEST_CASE("Roots amount") {
    SECTION("First example") {
        Polynom polynomial(5, {1,3,2});
        REQUIRE(rootsNumber(polynomial) == 0);
    }
}

