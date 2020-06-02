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

	Polynom getInverse(Polynom const& polynom) const {
		//Yasia&Natasha
	}

	Polynom divide(Polynom const& left, Polynom const& right) const {
		if (left.getPrime() != right.getPrime() || 
			left.getPrime() != irreducible.getPrime()) return Polynom();
		return (left * getInverse(right)) % irreducible;
	}

	Polynom derivative(Polynom const& polynom) const {
		return polynom.derivative() % irreducible;
	}
};