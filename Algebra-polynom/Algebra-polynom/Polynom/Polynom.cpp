/*!
 * @file Polynom.cpp
 * @brief Implementation of class Polynom
 * @details Functional of polynomial
 */

#include "Polynom.h"
#include "utils.h"
#include <list>

using std::cout;
using std::cin;
using std::endl;

Polynom::Polynom() {
    head = nullptr;
    prime = 1;
}

Polynom::Polynom(long long _prime, std::vector<long long> keys) : prime(_prime) {
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(i, keys[i]));
    }
}

Polynom::Polynom(long long _prime, std::vector<std::vector<long long>> keys) : prime(_prime) {
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(keys[i][0], keys[i][1]));
    }
}

Polynom::PolyTerm *Polynom::makeItem(long long pow, long long value) {
    auto *el = new PolyTerm;
    el->key = value;
    el->pow = pow;
    el->next = nullptr;
    return el;
}

void Polynom::addItem(Polynom::PolyTerm *el) {
    el->key = el->key % prime;
    if (el->key < 0) el->key += prime;
    if (el->key != 0) {
        //checks if polinom is empty
        if (head == nullptr) {
            head = el;
            return;
        }
        PolyTerm *t = head;
        //checks if polinoms head
        if (t->pow == el->pow) {
            t->key = (t->key + el->key) % prime;
            if (t->key == 0) {
                head = t->next;
                //delete t;
            }
            return;
        } else if (t->pow > el->pow) {
            el->next = t;
            head = el;
            return;
        }
        //checks the rest terms of polinom
        PolyTerm *t1 = t->next;
        while (t1) {
            if (t1->pow == el->pow) {
                t1->key = (t1->key + el->key) % prime;
                if (t1->key == 0) {
                    //delete t->next;
                    t->next = t1->next;
                }
                return;
            } else if (t1->pow > el->pow) {
                t->next = el;
                el->next = t1;
                return;
            }
            t = t1;
            t1 = t1->next;
        }
        t->next = el;
        el->next = nullptr;

    }
}

std::string Polynom::show() const {
    std::string answer;
    PolyTerm *tmp = head;
    bool isFirst = true;
    if (!tmp) return "0";
    while (tmp) {
        if (!isFirst) { answer += " + "; }
        else { isFirst = false; }
        answer += std::to_string(tmp->key);
        if (tmp->pow != 0) 
            (tmp->pow == 1) 
            ? answer += "*x" 
            : answer += "*x^" + std::to_string(tmp->pow);
        tmp = tmp->next;
    }
    return answer;
}

/*1     operation +       */
Polynom Polynom::addPoly(Polynom const &pol1, Polynom const &pol2) {
    Polynom pol3 = pol1;
    PolyTerm *tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow, tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}

/*1     operation +       */
Polynom operator+(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.addPoly(pol1, pol2);
    return c;
}

/*1     operation -       */
Polynom Polynom::diffPoly(Polynom const &pol1, Polynom const &pol2) {
    Polynom pol3 = pol1;
    PolyTerm *tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow, -tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}

/*1     operation -       */
Polynom operator-(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.diffPoly(pol1, pol2);
    return c;
}

/*1     operation *       */
Polynom Polynom::multPoly(Polynom const &pol1, Polynom const &pol2) {

    //TODO: mult when power>1
    Polynom result = multSimple(pol1, pol2);
    // result % irredus pol with power of result pol
    return result;

}

/*1     operation * (for n=1)      */
Polynom Polynom::multSimple(Polynom const &pol1, Polynom const &pol2) {
    long long pow = pol1.getPolyPower() + pol2.getPolyPower() + 1;
    std::vector<long long> num(pow, 0);
    PolyTerm *tmp1 = pol1.getHead();
    PolyTerm *tmp2 = pol2.getHead();

    while (tmp1) {
        while (tmp2) {
            num[tmp1->pow + tmp2->pow] = num[tmp1->pow + tmp2->pow] + (tmp1->key * tmp2->key);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
        tmp2 = pol2.getHead();
    }

    return Polynom(pol1.getPrime(), num);
}

/*1     operation *       */
Polynom operator*(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.multPoly(pol1, pol2);
    return c;
}

/*1     operation * (number)      */
Polynom Polynom::multNumber(Polynom const &p, long long const &number) {
    Polynom result;
    result.setPrime(p.getPrime());
    PolyTerm *tmp = p.getHead();
    while (tmp) {
        result.addItem(makeItem(tmp->pow, (tmp->key * number)));
        tmp = tmp->next;
    }
    return result;
}

/*2    derivative */

Polynom Polynom::derivative() const {
    Polynom answer=*this;
    auto node = answer.getHead();
    if (node->pow == 0) {
        answer.setHead(node->next);
        auto tmp = node->next;
        node->next = nullptr;
        delete node;
        node = tmp;
    }
    while (node) {
        node->key *= node->pow;
        node->key %= answer.getPrime();
        --node->pow;
        node = node->next;
    }
    return answer;

}

/*2     Define value of polynom at a point */
long long Polynom::valueAtPoint(long long x) const {
    long long answer{0};
    auto node = this->head;
    while (node) {
        long long addition{node->key};
        for (int i = 0; i < node->pow; ++i) {
            addition *= x;
            addition %= this->prime;
        }
        answer += addition;
        answer %= this->prime;
        //std::cout << answer << std::endl;
        node = node->next;
    }
    return answer;
}

/* 2  normalization of polynomial*/

void Polynom::normalization() {
    auto node = this->head;
    while (node->next) node = node->next;
    long long inv = utils::euclideanAlgorithm(node->key, this->prime, this->prime)[2];
    node = this->head;
    while (node) {
        node->key *= inv;
        node->key %= prime;
        node = node->next;
    }
}

/*6 operation for division*/
Polynom Polynom::multPolyforDivide(Polynom const &pol1, Polynom const &pol2) {
    long long pow = pol1.getPolyPower() + pol2.getPolyPower() + 1;
    std::vector<long long> num(pow, 0);
    PolyTerm *tmp1 = pol1.getHead();
    PolyTerm *tmp2 = pol2.getHead();

    while (tmp1) {
        while (tmp2) {
            num[tmp1->pow + tmp2->pow] = num[tmp1->pow + tmp2->pow] + (tmp1->key * tmp2->key);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
        tmp2 = pol2.getHead();
    }

    return Polynom(pol1.getPrime(), num);
}

/*1     operation * (number)      */
Polynom operator*(Polynom const &p, long long const &number) {
    Polynom c = c.multNumber(p, number);
    return c;
}

/*1     operation * (number)      */
Polynom operator*(long long const &number, Polynom const &p) {
    Polynom c = c.multNumber(p, number);
    return c;
}

std::pair<Polynom, Polynom> Polynom::simple_division(Polynom const &p1, Polynom const &p2) const {
    Polynom result(p1.getPrime(), std::vector<long long>{0});
    Polynom rest;
    Polynom temp_1 = p1;
    Polynom temp_2 = p2;
    int count = 0;
    while (temp_1.getPolyPower() >= temp_2.getPolyPower()) {
        if (temp_1.getPolyPower() == 0) {
            if (count >= 1) {
                break;
            }
            count++;
        }
        Polynom multiply(p1.getPrime(), std::vector<long long>{0});
        multiply.addItem(multiply.makeItem(temp_1.getPolyPower() - temp_2.getPolyPower(),
                                           utils::division_for_numbers(temp_1.getTermKey(temp_1.getPolyPower()),
                                                                       temp_2.getTermKey(temp_2.getPolyPower()),
                                                                       p2.getPrime())));
        temp_2 = temp_2.multPolyforDivide(temp_2, multiply);
        temp_1 = temp_1 - temp_2;
        temp_2 = p2;
        result = result + multiply;
    }
    rest = temp_1;
    return std::pair<Polynom, Polynom>(result, rest);
}

/*1     operation / (number)      */
Polynom operator/(Polynom const &p1, Polynom const &p2) {
    return p1.simple_division(p1, p2).first;
}

/*1     operation % (number)      */
Polynom operator%(Polynom const &p1, Polynom const &p2) {
    return p1.simple_division(p1, p2).second;
}

/*9 Equal operator*/
bool operator==(Polynom const &p1, Polynom const &p2) {
    Polynom::PolyTerm *cur1 = p1.getHead();
    Polynom::PolyTerm *cur2 = p2.getHead();
    while (cur1 != nullptr && cur2 != nullptr) {
        if (cur1->key != cur2->key)
            return false;
	if (cur1->pow != cur2->pow)
	    return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur1 != nullptr || cur2 != nullptr)
	    return false;
    return true;
}


/**/

/*4     Number of roots       */
long long Polynom::rootsNumber() {
	long long pow = getPrime() - 1;
	Matrix AMatrix(pow, pow, pow + 1);

	for (long long i = 0, shift = 0; i < pow; i++, shift++) {
		for (long long j = 0; j < pow; j++) {
		    if ( (j + shift) % pow == 0) {
                AMatrix.setElement(i, j, (getTermKey(0) + getTermKey(pow)) % (pow + 1));
		    } else {
		        AMatrix.setElement(i, j, getTermKey((j + shift) % pow));
		    }
		}
	}

    long long matrixRank = AMatrix.rank().first;
    return (pow - matrixRank);
}

Polynom Polynom::gcd(Polynom p2) {
    Polynom p1(*this);
    while (p1.getHead() != nullptr && p2.getHead() != nullptr) {
        if (p1.getPolyPower() > p2.getPolyPower()) {
            p1 = p1 % p2;
        } else {
            p2 = p2 % p1;
        }
    }

    if (p1.getHead() == nullptr) {
        return p2;
    }

    return p1;
}

/*9 This method calculates nth Cyclotomic polynomial*/
Polynom Polynom::CyclotomicPolynomial(int prime, int n) {
    // if (n % prime == 0) return Polynom();
    std::vector<long long> keys{1};
    Polynom result(prime, keys);
    int mob;
    if (utils::isPrime(n))
        return Polynom(prime, std::vector<long long>(n, 1));
    for (int d = 1; d <= n; d++) {
        if (n % d == 0 && utils::mobius(n / d) == 1) {
            std::vector<long long> keys(d + 1, 0);
            keys[d] = 1;
            keys[0] = -1;
            Polynom multiplier(prime, keys);
            result = result * multiplier;
        }
    }
    for (int d = 1; d <= n; d++) {
        if (n % d == 0 && utils::mobius(n / d) == -1) {
            std::vector<long long> keys(d + 1, 0);
            keys[d] = 1;
            keys[0] = -1;
            Polynom divider(prime, keys);
            result = result / divider;
        }
    }
    return result;
}

/* 10 Factorization using Ri */
std::vector<Polynom> Polynom::factorizeCyclotomicRi(size_t n) {
	//std::cout << "Current: " << this->show() << std::endl;
	if (n == 1) {
		std::vector<Polynom> result { Polynom() };
		result[0]=*this;
		return result;
	}
	if (utils::gcd((long long)n, prime) > 1) {
		//Special case
		//Q(p^m)n (mod p) may be represented as Qn to some power
		
		size_t newN = n;
		while (newN % prime == 0)
			newN /= prime;

		Polynom newCyclotomic = Polynom::CyclotomicPolynomial(prime, newN);

		std::vector<Polynom> factors = newCyclotomic.factorizeCyclotomicRi(newN);
		size_t repeat = this->getPolyPower() / newCyclotomic.getPolyPower();
		size_t count = factors.size();

		for (size_t i = 1; i < repeat; i++) {
			for (size_t j = 0; j < count; j++) {
				factors.emplace_back();
				factors.back()=factors[j];
			}
		}
		return factors;
	}
	

	/* MAIN ALGORITHM (n and p are co-prime) */

	//Find number of factors
	size_t d = 0;
	size_t dPow = 1;
	do {
		d++;
		dPow = (dPow * prime) % n;
		//std::cout << "d = " << d << std::endl;
		//std::cout << dPow << std::endl;
	} while (dPow != 1);
	

	std::vector<Polynom> factors;
	std::list<Polynom> polysToFactorize;
	polysToFactorize.emplace_back();
	polysToFactorize.back()=*this;

	size_t factorsCount = utils::euler(n) / d;	
	size_t factorPower = getPolyPower() / factorsCount;		
	if (factorsCount == 1) {
		factors.emplace_back();
		factors[0]=*this;
		return factors;
	}
	//std::cout << "Factors count: " << factorsCount << std::endl;
	//std::cout << "Factors power: " << factorPower << std::endl;

	size_t i = 1;
	while (factors.size() < factorsCount) {
		//std::cout << "Trying R" << i << std::endl;
		Polynom riPolynomial = Polynom(prime, std::vector<long long>());
		long long j = 1;

		PolyTerm* currentTerm = makeItem(i, 1);
		riPolynomial.head = currentTerm;

		long long mod = n / utils::gcd(n, i);
		while ((long long)std::pow(prime, j) % mod != 1) {
			currentTerm->next = makeItem(i * (long long)std::pow(prime, j), 1);

			currentTerm = currentTerm->next;
			j++;
		}
		currentTerm->next = nullptr;

		bool factorized = false;
		j = 0;
		while (j < prime) {
			//std::cout << "====\n";
			//std::cout << polysToFactorize.front().show() << std::endl;
			//std::cout << riPolynomial.show() << std::endl;

			Polynom gcdRi = polysToFactorize.front().gcd(riPolynomial);

			//std::cout << gcdRi.show() << std::endl;
			//std::cout << "====\n";

			//check if Ri = 0 (mod Q)
			if (j == 0 && gcdRi == polysToFactorize.front()) {
				factorized = false;
				break;
			}

			long long gcdPower = gcdRi.getPolyPower();
			if (gcdPower == factorPower) {
				factorized = true;
				gcdRi.normalization();
				factors.push_back(gcdRi);
			} else if (gcdPower % factorPower == 0) {
				factorized = true;
				polysToFactorize.push_back(gcdRi);
			}

			riPolynomial = riPolynomial + Polynom(prime, std::vector<long long>(1, 1));
			j++;
		}
		if (factorized) {
			polysToFactorize.pop_front();
		}
		i++;

	}

	return factors;
}

/*5 Inverse of a polynomial in field
Знаходження оберненого многочлена*/
/*
{
  Polynom tar;
  Polynom irr;
  Polynom div;
  Polynom rem;
  Polynom res;
  int i = 1;
  tar.copy(pol1);
  irr.copy(pol2);
  while (rem == 1)
  {
    div = irr / tar;
    rem = irr % tar;
    irr.copy(tar);
    tar.copy(rem);
    if (i % 2)
      res = res + div;
    else
      res = res + 1;
  }
  return res;
}
*/
/*long long Polynom::gcdforinvers(long long a, long long b, long long* x, long long* y)
{
    if (a == 0)
    {
        *x = 0, * y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}*/

/*Polynom Polynom::inversPoly(long long number, Polynom const& pol1)
{
    int x, y;
    int g = gcdforinvers(number, pol1, int & x, int & y);

    if (g != 1)
        return -1;
    else
        return (x % pol1 + pol1) % pol1;
}*/

/* 12 Finds all irreducible polynomials of degree n */
std::vector<Polynom> Polynom::allIrreduciblePolynomials(long long prime, long long n)
{
    std::vector<Polynom> result, temp;
    Polynom cyclotomic;

    // 3.31 Lidl
    long long num = pow(prime, n) - 1;
    for (long long m = 1; m <= num; ++m) {
        if ((num % m) == 0) {
            cyclotomic = Polynom::CyclotomicPolynomial(prime, m);
            if (cyclotomic.getPolyPower() < n) continue;
            temp = cyclotomic.factorizeCyclotomicRi(m);
            result.insert(result.end(), temp.begin(), temp.end());
        }
    }
    /*// Output
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i].show() << std::endl;
    }*/
    return result;
}

/* 12 Finds one irreducible polynomial of degree n */
Polynom Polynom::findIrreduciblePolynomial(long long prime, long long n)
{
    std::vector<Polynom> temp;
    Polynom cyclotomic;

    // 3.31 Lidl
    long long num = pow(prime, n) - 1;
    for (long long m = 1; m <= num; ++m) {
        if ((num % m) == 0) {
            cyclotomic = Polynom::CyclotomicPolynomial(prime, m);
            if (cyclotomic.getPolyPower() < n) continue;
            temp = cyclotomic.factorizeCyclotomicRi(m);
            return temp[0];
        }
    }
    // Doesn't find
    return Polynom();
}
