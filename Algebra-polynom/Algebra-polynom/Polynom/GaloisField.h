#include "Polynom.h"

class GaloisField {
private:
	Polynom irreducible;

public:
	GaloisField(long long prime, long long degree) {
		irreducible = Polynom::findIrreduciblePolynomial(prime, degree);
	}

	Polynom getIrreducible() const {
		return irreducible;
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