#include "Polynom.h"

class GaloisField {
private:
	Polynom irreducible;
	long long prime;
	long long degree;
public:
	
	GaloisField() :prime(2), degree(2) {
		irreducible = Polynom::findIrreduciblePolynomial(2, 2);
	}
	
	GaloisField(long long prime, long long degree) :prime(prime), degree(degree){
		irreducible = Polynom::findIrreduciblePolynomial(prime, degree);
	}
	long long getPrime() const { return prime; }
	long long getDegree() const { return degree; }
	Polynom getIrreducible() const {
		return irreducible;
	}

	std::vector<Polynom> getNIrreducible(int n) const {
		return Polynom::nIrreduciblePolynomials(prime, degree, n);
	}

	void setIrreducible(int n, int index) {
		std::vector<Polynom> temp = getNIrreducible(n);
		irreducible = temp[index % n];
	}

	void setIrreducible(Polynom p) {
		irreducible = p;
	}

	Polynom add(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() || 
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left + right) % irreducible;
	}

	Polynom subtract(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() || 
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left - right) % irreducible;
	}

	Polynom multiply(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() || 
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left * right) % irreducible;
	}

    Polynom extendedEuclidianAlgorithm(Polynom a, Polynom b, Polynom *x, Polynom *y)const {
        long long prime=a.getPrime();

        if (a == Polynom(prime,std::vector<long long>{0}))
        {
            *x = Polynom(prime,std::vector<long long>{0});
            *y = Polynom(prime,std::vector<long long>{1});
            return b;
        }
        Polynom x1, y1;
        Polynom d = extendedEuclidianAlgorithm(b%a, a, &x1, &y1);
        *x = y1 - (b / a) * x1;
        *y = x1;
        return d;
    }

    Polynom getInverse(Polynom const& polynom) const {
        Polynom x;
        Polynom y;
        extendedEuclidianAlgorithm(polynom, irreducible, &x, &y);
        x = (x % irreducible + irreducible) % irreducible;
        return x;
    }

	Polynom divide(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() || 
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left * getInverse(right)) % irreducible;
	}

	Polynom mod(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() ||
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left % right) % irreducible;
	}

	Polynom derivative(Polynom const& polynom) const {
		return polynom.derivative() % irreducible;
	}
};