#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Polynom/Polynom.h"
#include "../Polynom/GaloisField.h"
#include <vector>
#include "utils.h"

TEST_CASE("Polynomial")
{
    SUBCASE("Creating polynom")
    {
        Polynom polynomial1(3, {{0, 1}, {2, 2}});
        REQUIRE(polynomial1.show() == "1 + 2*x^2");
        Polynom polynomial(3, {1, 2});
        REQUIRE(polynomial.show() == "1 + 2*x");
        Polynom polynomial2(3, "1 + 2*x", 'x');
        REQUIRE(polynomial2.show() == "1 + 2*x");
    }
    SUBCASE("Creating empty polynom")
    {
        Polynom polynomial(3, {3, 6});
        REQUIRE(polynomial.getHead() == nullptr);
    }
    SUBCASE("Creating copy of polynom")
    {
        Polynom polynomial(3, {1, 2});
        Polynom copy = polynomial;
        REQUIRE(polynomial.show() == copy.show());
        REQUIRE(polynomial.getPrime() == copy.getPrime());

        copy = copy + polynomial;
        REQUIRE(polynomial.show() != copy.show());
    }
    SUBCASE("Power of polynom")
    {
        Polynom poly1(3, {1, 3, 3});
        REQUIRE(poly1.getPolyPower() == 0);
        Polynom poly2(3, {1, 1});
        REQUIRE(poly2.getPolyPower() == 1);
        Polynom poly3(3, {1, 1, 1});
        REQUIRE(poly3.getPolyPower() == 2);
    }
    SUBCASE("Adding polynoms in Z[3]")
    {
        Polynom poly1(3, {1, 2});
        Polynom poly2 = poly1 + poly1;
        REQUIRE(poly1.show() == "1 + 2*x");
        REQUIRE(poly2.show() == "2 + 1*x");
        REQUIRE((poly1 + poly2).show() == "0");
    }
    SUBCASE("Substract polynoms in Z[3]")
    {
        Polynom poly1(3, {1, 2});
        Polynom poly2(3, {2, 2});
        REQUIRE((poly1 - poly1).show() == "0");
        REQUIRE((poly1 - poly2).show() == "2");
    }
    SUBCASE("Multiplicate polynoms in Z[3]")
    {
        Polynom poly1(3, {1, 2});
        REQUIRE(poly1.show() == "1 + 2*x");

        REQUIRE(poly1.getTermKey(0) == 1);
        REQUIRE(poly1.getTermKey(1) == 2);
        REQUIRE(poly1.getTermKey(2) == 0);

        Polynom polynomial = poly1 * poly1;
        REQUIRE(polynomial.show() == "1 + 1*x + 1*x^2");

        Polynom poly2(3, {1, 1});
        polynomial = poly1 * poly2;
        REQUIRE(polynomial.show() == "1 + 2*x^2");

        polynomial = poly1 * 3;
        REQUIRE(polynomial.show() == "0");
    }

    SUBCASE("GCD polynoms") {
		Polynom pol1(3, { 4,0,3,3,3,1 });
		Polynom pol2(3, { 1,2,0,1,1 });

		Polynom res = pol1.gcd(pol2);

		REQUIRE(res.getTermKey(0) == 1);
		REQUIRE(res.getPolyPower() == 0);

		pol1 = Polynom(5, { 4, 0, 7 });
		pol2 = Polynom(5, { 1, 2, 1 });

		res = pol1.gcd(pol2);

		REQUIRE(res.getTermKey(0) == 2);
		REQUIRE(res.getPolyPower() == 0);

		pol1 = Polynom(5, { 4, 0, 7 });
		pol2 = Polynom(5, { 4, 0, 7 });

		res = pol1.gcd(pol2);

		REQUIRE(res.getTermKey(0) == 4);
		REQUIRE(res.getTermKey(1) == 0);
		REQUIRE(res.getTermKey(2) == 2);
		REQUIRE(res.getPolyPower() == 2);
    }
}

TEST_CASE("Division") {
    SUBCASE("/ operation")
    {
        SUBCASE("example 1") {
            Polynom polynom1(3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, { 2,1,5 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "2 + 2*x^3 + 2*x^4");
        }

        SUBCASE("example 2") {
            Polynom polynom1(3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, { 2,1,5 });
            Polynom result = polynom2 / polynom1;
            REQUIRE(result.show() == "0");
        }
        SUBCASE("example 3") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53 });
            Polynom polynom2(17, { 37,56,67,27,14 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "5");
        }
        SUBCASE("example 4") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, { 37,56,67,27,14 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "14 + 10*x + 7*x^2 + 14*x^3");
        }
        SUBCASE("example 5") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, { 37,56,67,27,57,86,39 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "1 + 12*x");
        }
    }
    SUBCASE("% operation")
    {
        SUBCASE("example 1") {
            Polynom polynom1(3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, { 2,1,5 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "2 + 2*x");
        }

        SUBCASE("example 2") {
            Polynom polynom1(3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, { 2,1,5 });
            Polynom result = polynom2 % polynom1;
            REQUIRE(result.show() == "2 + 1*x + 2*x^2");
        }
        SUBCASE("example 3") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53 });
            Polynom polynom2(17, { 37,56,67,27,14 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "5 + 9*x + 2*x^2 + 10*x^3");
        }
        SUBCASE("example 4") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, { 37,56,67,27,14 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "12 + 2*x + 8*x^2 + 6*x^3");
        }
        SUBCASE("example 5") {
            Polynom polynom1(17, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, { 37,56,67,27,57,86,39 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "10*x + 6*x^2 + 11*x^3 + 12*x^4 + 4*x^5");
        }
    }
}
TEST_CASE("Derivation")
{
    SUBCASE("First example")
    {
        Polynom polynom(11, {3, 7, 10, 1, 0, 3, 4});
        REQUIRE(polynom.derivative().show() == "7 + 9*x + 3*x^2 + 4*x^4 + 2*x^5");
    }
    SUBCASE("Second example")
    {
        Polynom polynom(23, {1, 2, 3, 4, 5, 6, 7});
        REQUIRE(polynom.derivative().show() == "2 + 6*x + 12*x^2 + 20*x^3 + 7*x^4 + 19*x^5");
    }
    SUBCASE("Third example")
    {
        Polynom polynom(93, {1, 3, 7, 8, 2, 5, 0, 0, 7});
        REQUIRE(polynom.derivative().show() == "3 + 14*x + 24*x^2 + 8*x^3 + 25*x^4 + 56*x^7");
    }
    SUBCASE("Fourth example") {
        Polynom polynom(113, {5, 98, 23, 112, 1});
        REQUIRE(polynom.derivative().show() == "98 + 46*x + 110*x^2 + 4*x^3");
    }
}

TEST_CASE("Normalization")
{
    SUBCASE("First example")
    {
        Polynom polynom(29, {4, 5, 1, 3, 0, 9});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(5) == 1);
    }
    SUBCASE("Second example")
    {
        Polynom polynom(97, {4, 5, 1, 3, 0, 9, 8, 6, 2, 0, 0, 0, 1, 15, 96});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(14) == 1);
    }
    SUBCASE("Third example")
    {
        Polynom polynom(71, {4, 5, 1, 3, 0, 9, 72});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(6) == 1);
    }
    SUBCASE("Fourth example") {
        Polynom polynom(LLONG_MAX, {4, 2, 12321, 43452, 43928524, 1});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(5) == 1);
    }
    SUBCASE("Fivth example") {
        Polynom polynom(INT_MAX, {4, 2, 12321, 43452, 51965, 4});
        polynom.normalization();
                REQUIRE(polynom.getTermKey(5) == 1);
    }
}

TEST_CASE("Definition valua at a point")
{
    SUBCASE("First example")
    {
        Polynom polynom(17, {1, 2, 3, 4, 5});
        REQUIRE(polynom.valueAtPoint(1) == 15);
        REQUIRE(polynom.valueAtPoint(-1) == 3);
        REQUIRE(polynom.valueAtPoint(0) == 1);
    }
    SUBCASE("Second example")
    {
        Polynom polynom(97, {15, 2, 3, 4, 5, 87, 61, 8});
        REQUIRE(polynom.valueAtPoint(3) == 53);
    }
            SUBCASE("Third example")
    {
        Polynom polynom(2, {1, 0, 1, 1, 0, 0, 0, 1});
                REQUIRE(polynom.valueAtPoint(3) == 0);
    }
            SUBCASE("Fourth example")
    {
        Polynom polynom(INT_MAX, {15, 2, 61, INT_MAX});
                REQUIRE(polynom.valueAtPoint(3) == ((long long) 15 + 6 + 61*3*3 + (long long)INT_MAX*3*3*3)%INT_MAX);
    }
}

TEST_CASE("Roots amount")
{
    SUBCASE("First example")
    {
        Polynom polynomial(5, {1, 3, 0, 2});
        REQUIRE(polynomial.rootsNumber() == 0);
    }

    SUBCASE("Second example")
    {
        Polynom polynomial(5, {1, 1, 1, 1});
        REQUIRE(polynomial.rootsNumber() == 3);
    }

    SUBCASE("Third example")
    {
        Polynom polynomial(5, {1, 2, 2, 1});
        REQUIRE(polynomial.rootsNumber() == 1);
    }

    SUBCASE("Fourth example") {
        Polynom polynomial(17, {
                {0,-2},{1,-1},{2,4},{3,-7},{4,3},{5,-7},{6,1}
        });
        REQUIRE(polynomial.rootsNumber() == 4);
    }

    SUBCASE("Fifth example") {
        Polynom polynomial(5, {
                {0,-2},{1,-1}, {2,1},{3,2},{4,-1},{5,1}
        });
        REQUIRE(polynomial.rootsNumber() == 2);
    }

    SUBCASE("Sixth example") {
        Polynom polynomial(3, {0,1,1});
        REQUIRE(polynomial.rootsNumber() == 2);
    }
}

TEST_CASE("Polynom to the power of test") {
    SUBCASE("number") {
        Polynom x(10000, std::vector<long long>{ 2 });
        x = x.toThePower(13);
        REQUIRE(x.getTermKey(0) == 8192LL);
    }

    SUBCASE("(x-1)^3") {
        Polynom x(5, std::vector<long long>{-1, 1});
        x = x.toThePower(3);
        REQUIRE(x == Polynom(5, std::vector<long long>{-1, 3, -3, 1}));
    }

    SUBCASE("Something harder") {
        Polynom x(LLONG_MAX, std::vector<long long>{5, -5, -6, 2, 6, 1});
        x = x.toThePower(10);
        REQUIRE(x.getTermKey(0) == 9765625LL);
        REQUIRE(x.getTermKey(48) == 1640LL);
        REQUIRE(x.getTermKey(49) == 60LL);
        REQUIRE(x.getTermKey(50) == 1LL);
    }
}

TEST_CASE("Get polynom with other x") {
    SUBCASE("number") {
        Polynom x(100, std::vector<long long>{5});
        Polynom orig = x;
        x = x.getWithOtherParameter(4);
        REQUIRE(x == orig);
    }

    SUBCASE("x+5") {
        Polynom x(100, std::vector<long long>{5, 1});
        x = x.getWithOtherParameter(2);
        Polynom tocheck(100, std::vector<long long>{3, 1});
        REQUIRE(x == tocheck);
    }

    SUBCASE("x^4+x^3+4x^2+1") {
        Polynom x(100, std::vector<long long>{1, 0, 4, 1, 1});
        x = x.getWithOtherParameter(3);
        Polynom tocheck(100, std::vector<long long>{91, 95, 49, 89, 1});
    }
}

TEST_CASE("Roots of the polynomial") {
    Polynom x;

    SUBCASE("First example") {
        x = Polynom(17, {
            {0,-2},{1,-1},{2,4},{3,-7},{4,3},{5,-7},{6,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Second example") {
        x = Polynom(17, {
            {0,4},{1,2},{2,4},{3,-7},{4,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Third example") {
        x = Polynom(19, {
        {0,-8},{1,-8},{2,-6},{3,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Fourth example") {
        x = Polynom(19, {
        {0,-8},{1,-6},{2,4},{3,-3},{4,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Fifth example") {
        x = Polynom(17, {
        {0,5},{2,-6},{3,2},{4,3},{5,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Sixth example") {
        x = Polynom(11, {
       {0,5},{1,3}, {2,-5},{3,3},{4,-4},{6,-2},{7,1}
            });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Seventh example") {
        x = Polynom(19,
            { -7,6,8,1 }
        );

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }

    SUBCASE("Eights example") {
        x = Polynom(5, 
            { -2,-1,1,2,-1,1 });

        std::vector<Polynom> ans = x.findRoots();

        REQUIRE(ans.size() == x.rootsNumber());

        for (int i = 0, size = ans.size(); i < size; ++i) {
            REQUIRE(x.valueAtPoint(ans[i].getTermKey(0)) == 0);
        }
    }
}

TEST_CASE("Cyclotomic polynomials")
{
    SUBCASE("n=1")
    {
        Polynom polynomial(131, {130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 1) == polynomial);
    }
    SUBCASE("n=2")
    {
        Polynom polynomial(131, {1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 2) == polynomial);
    }
    SUBCASE("n=3")
    {
        Polynom polynomial(131, {1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 3) == polynomial);
    }
    SUBCASE("n=4")
    {
        Polynom polynomial(131, {1, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 4) == polynomial);
    }
    SUBCASE("n=5")
    {
        Polynom polynomial(131, {1, 1, 1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 5) == polynomial);
    }
    SUBCASE("n=6")
    {
        Polynom polynomial(131, {1, 130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 6) == polynomial);
    }
    SUBCASE("n=7")
    {
        Polynom polynomial(131, {1, 1, 1, 1, 1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 7) == polynomial);
    }
    SUBCASE("n=8")
    {
        Polynom polynomial(131, {1, 0, 0, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 8) == polynomial);
    }
    SUBCASE("n=9")
    {
        Polynom polynomial(131, {1, 0, 0, 1, 0, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 9) == polynomial);
    }
    SUBCASE("n=10")
    {
        Polynom polynomial(131, {1, 130, 1, 130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 10) == polynomial);
    }
    SUBCASE("n=105")
    {
        std::vector<long long> keys(49, 0);
        keys[0] = 1;
        keys[1] = 1;
        keys[2] = 1;
        keys[5] = 130;
        keys[6] = 130;
        keys[7] = 129;
        keys[8] = 130;
        keys[9] = 130;
        for (int i = 12; i <= 17; i++)
        {
            keys[i] = 1;
        }
        for (int i = 20; i <= 28; i += 2)
        {
            keys[i] = 130;
        }
        for (int i = 31; i <= 36; i++)
        {
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
        Polynom polynomial(131, keys);
        REQUIRE(Polynom::CyclotomicPolynomial(131, 105) == polynomial);
    }
    SUBCASE("n=30")
    {
        Polynom polynomial(131, { 1, 1, 0 , 130, 130, 130, 0, 1, 1 });
        REQUIRE(Polynom::CyclotomicPolynomial(131, 30) == polynomial);
    }
}

TEST_CASE("Factorization of cyclotomic using Ri")
{
	SUBCASE("n < q")
	{
		int n = 5;
		int q = 7;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);
		REQUIRE(factors.size() == 1);
		REQUIRE(factors[0] == cyclotomic);
	}
	SUBCASE("n = 52, q = 3")
	{
		int n = 52;
		int q = 3;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);

		Polynom product = Polynom(q, std::vector<long long>{ 1 });
		for (Polynom& factor : factors) {
			product = product * factor;
		}
		REQUIRE(product == cyclotomic);
	}
	SUBCASE("n = 45, q = 3")
	{
		int n = 45;
		int newN = 5;
		int q = 3;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);

		Polynom newCyclotomic = Polynom::CyclotomicPolynomial(q, newN);
		REQUIRE(factors.size() == 6);
		for (auto factor : factors)
			REQUIRE(factor == newCyclotomic);
	}
	SUBCASE("n = 18, q = 7")
	{
		int n = 18;
		int q = 7;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);

		Polynom product = Polynom(q, std::vector<long long>{ 1 });
		for (Polynom& factor : factors) {
			product = product * factor;
		}
		REQUIRE(product == cyclotomic);
	}
}

TEST_CASE("Finding all irreducible polynomials of degree n")
{
            SUBCASE("prime = 2, n = 2")
    {
        int prime = 2;
        int n = 2;

        std::vector<Polynom> result = Polynom::allIrreduciblePolynomials(prime, n);
        std::vector<Polynom> required;
        required.push_back(Polynom(prime, { 1, 1, 1 }));

                REQUIRE(result == required);
    }
            SUBCASE("prime = 2, n = 3")
    {
        int prime = 2;
        int n = 3;

        std::vector<Polynom> result = Polynom::allIrreduciblePolynomials(prime, n);
        std::vector<Polynom> required;
        required.push_back(Polynom(prime, { 1, 1, 0, 1 }));
        required.push_back(Polynom(prime, { 1, 0, 1, 1 }));

                REQUIRE(result == required);
    }
            SUBCASE("prime = 3, n = 3")
    {
        int prime = 3;
        int n = 3;

        std::vector<Polynom> result = Polynom::allIrreduciblePolynomials(prime, n);
        std::vector<Polynom> required;
        required.push_back(Polynom(prime, { 2, 2, 0, 1 }));
        required.push_back(Polynom(prime, { 2, 2, 2, 1 }));
        required.push_back(Polynom(prime, { 2, 1, 1, 1 }));
        required.push_back(Polynom(prime, { 2, 0, 1, 1 }));
        required.push_back(Polynom(prime, { 1, 2, 0, 1 }));
        required.push_back(Polynom(prime, { 1, 2, 1, 1 }));
        required.push_back(Polynom(prime, { 1, 1, 2, 1 }));
        required.push_back(Polynom(prime, { 1, 0, 2, 1 }));

                REQUIRE(result == required);
    }
}

TEST_CASE("Check if the polynomial is irreducible")
{
    SUBCASE("prime = 2, n = 2")
    {
        Polynom pol1(2, { 1, 1, 1 });

            REQUIRE(pol1.isIrreducible() == 1);
    }

    SUBCASE("prime = 2, n = 3")
    {
        Polynom pol1(2, { 1, 1, 0, 1 });
            REQUIRE(pol1.isIrreducible() == 1);

        Polynom pol2(2, { 1, 0, 1, 1 });
            REQUIRE(pol2.isIrreducible() == 1);

    }

    SUBCASE("prime = 3, n = 3")
    {
        Polynom pol1(3, { 2, 2, 0, 1 });
                REQUIRE(pol1.isIrreducible() == 1);
        Polynom pol2(3, { 2, 2, 2, 1 });
                REQUIRE(pol2.isIrreducible() == 1);
        Polynom pol3(3, { 2, 1, 1, 1 });
                REQUIRE(pol3.isIrreducible() == 1);
        Polynom pol4(3, { 2, 0, 1, 1 });
                REQUIRE(pol4.isIrreducible() == 1);
        Polynom pol5(3, { 1, 2, 0, 1 });
                REQUIRE(pol5.isIrreducible() == 1);
        Polynom pol6(3, { 1, 2, 1, 1 });
                REQUIRE(pol6.isIrreducible() == 1);
        Polynom pol7(3, { 1, 1, 2, 1 });
                REQUIRE(pol7.isIrreducible() == 1);
        Polynom pol8(3, { 1, 0, 2, 1 });
                REQUIRE(pol8.isIrreducible() == 1);
    }
}


TEST_CASE("Testing polynomial field [3^2]")
{
    GaloisField field(3, 2);
    Polynom a(3, { 1, 2 });
    Polynom b(3, { 1, 1 });

    SUBCASE("Irreducible")
    {
        REQUIRE(field.getIrreducible().show() == "1 + 1*x^2");
    }
    SUBCASE("Addition")
    {
        REQUIRE(field.add(a, b).show() == "2");
    }
    SUBCASE("Subtraction")
    {
        REQUIRE(field.subtract(a, b).show() == "1*x");
        REQUIRE(field.subtract(b, a).show() == "2*x");
        REQUIRE(field.subtract(a, a).show() == "0");
    }
    SUBCASE("Multiplication")
    {
        REQUIRE(field.multiply(a, b).show() == "2");
    }
    SUBCASE("Derivative")
    {
        REQUIRE(field.derivative(a).show() == "2");
    }
}

TEST_CASE("Testing polynomial field [5^3]")
{
    GaloisField field(5, 3);
    Polynom a(5, { 2, 3, 1, 4, 0, 1 });
    Polynom b(5, { 4, 0, 3, 4, 2, 0, 2 });


    SUBCASE("Irreducible")
    {
        REQUIRE(field.getIrreducible().show() == "4 + 3*x^2 + 1*x^3");
    }
    SUBCASE("Addition")
    {
        REQUIRE(field.add(a, b).show() == "2*x^2");
    }
    SUBCASE("Subtraction")
    {
        REQUIRE(field.subtract(a, b).show() == "4*x^2");
        REQUIRE(field.subtract(b, a).show() == "1*x^2");
    }
    SUBCASE("Multiplication")
    {
        REQUIRE(field.multiply(a, b).show() == "4 + 2*x + 3*x^2");
    }
    SUBCASE("Derivative")
    {
        REQUIRE(field.derivative(a).show() == "3 + 2*x + 2*x^2");
    }
}
TEST_CASE("Testing Berlekamp factorization algorithm")
{
    std::vector<std::vector<long long>> polyVector = {{0,1}, {3,1}, {4,1}, {6,1}, {8,1}};
    Polynom polynom(2, polyVector);

    SUBCASE("Building Berlekamp matrix")
    {
        Matrix matrix = polynom.buildBerlekampMatrix();

        REQUIRE(matrix.getElement(0,0) == 0);
        REQUIRE(matrix.getElement(1,1) == 1);
        REQUIRE(matrix.getElement(1,2) == 1);
    }

    SUBCASE("Testing Berlekamp factorization") {
        REQUIRE(polynom.berlekampAlgorithm() == "(1 + 1*x + 1*x^4 + 1*x^5 + 1*x^6) * (1 + 1*x + 1*x^2)");
    }
}

TEST_CASE("Inverse polynom") {
    SUBCASE("Double Inversing 1") {
        GaloisField field(3, 4);

        Polynom x(3, std::vector<long long>{1,1,1});
        Polynom origin = x;

        x = field.getInverse(x);
        x = field.getInverse(x);

        REQUIRE(x == origin);
    }

    SUBCASE("Double Inversing 2") {
        GaloisField field(2, 4);

        Polynom x(2, std::vector<long long>{1, 1});
        Polynom origin = x;

        x = field.getInverse(x);
        x = field.getInverse(x);

        REQUIRE(x == origin);
    }

    SUBCASE("Double Inversing 3") {
        GaloisField field(2, 3);

        Polynom x(2, std::vector<long long>{1, 0, 1});
        Polynom origin = x;

        x = field.getInverse(x);
        x = field.getInverse(x);
        REQUIRE(x == origin);
    }
}
