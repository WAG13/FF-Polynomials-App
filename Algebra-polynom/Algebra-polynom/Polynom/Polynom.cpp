/*!
 * @file Polynom.cpp
 * @brief Implementation of class Polynom
 * @details Functional of polynomial
 */

#include "Polynom.h"
#include "../utils.h"
#include <list>
#include <stack>

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

Polynom::Polynom(long long _prime, std::string polynom, char X) : prime(_prime) {
    head = nullptr;
    std::vector<std::vector<long long>> keys = utils::coefStr(polynom, X);
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
    x %= this->prime;
    if (x < 0) x += this->prime;
    auto node = this->head;
    while (node) {
        long long addition{node->key};
        for (int i = 0; i < node->pow; ++i) {
            addition *= x;
            addition %= this->prime;
        }
        answer += addition;
        answer %= this->prime;
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

//f(x)^pow
Polynom Polynom::toThePower(long long pow) const {
	Polynom ans;
	ans = Polynom(prime, std::vector<long long>{ 1 });

	Polynom cur = *this;

	while (pow) {
		if (pow & 1) {
			ans = ans * cur;
			--pow;
		}
		else {
			cur = cur * cur;
			pow >>= 1;
		}
	}

	return ans;
}

//get instead of polynom f(x) - polynom f(x-b)
Polynom Polynom::getWithOtherParameter(long long b) const {
	if (b == 0) {
		return *this;
	}

	Polynom temp;
	temp = *this;

	PolyTerm* node = temp.head;

	if (!node) {
		return Polynom();
	}


	Polynom ans(prime, {
		{0,0}, {1,0}
		});

	do {
		ans = ans + Polynom(prime, {
			{0,-b}, {1,1}
			}).toThePower(node->pow) * node->key;
			node = node->next;
	} while (node);

	return ans;
}

/* #3 find roots of the polynomial*/
std::vector<Polynom> Polynom::findRoots() {
	long long rootsNumber = this->rootsNumber();

	std::vector<Polynom> ans;

	if (rootsNumber == 0) {
		return std::vector<Polynom>();
	}
	else {
		struct polynomsStruct {
			Polynom current;
			Polynom g;
			long long b;

			polynomsStruct(Polynom current, Polynom g, long long b) {
				this->current = current;
				this->g = g;
				this->b = b;
			}
		};

		std::stack<polynomsStruct> polynoms;

		Polynom divider(prime, {
			{1,-1},{prime, 1}
			});

		Polynom g = this->gcd(divider);
		Polynom xp = Polynom(prime, {
			{1,0}, {(prime - 1) / 2,1}
			});

		Polynom one = Polynom(prime, {
			{0,1},{1,0}
			});

		polynoms.push(polynomsStruct(*this, g, 0));

		while (!polynoms.empty()) {
			polynomsStruct currentStruct = polynoms.top();
			polynoms.pop();
			Polynom current;
			current = currentStruct.current;
			if (current.getPolyPower() > 1) {
				if (current.rootsNumber()) {
					currentStruct.g = currentStruct.g.getWithOtherParameter(currentStruct.b);
					currentStruct.g.normalization();

					Polynom originalG;
					originalG = currentStruct.g;

					while (xp % currentStruct.g == one % currentStruct.g) {
						++currentStruct.b;
						currentStruct.g = originalG;
						currentStruct.g = g.getWithOtherParameter(currentStruct.b);
						currentStruct.g.normalization();
					}

					Polynom temp;
					Polynom tempG;
					temp = currentStruct.g.gcd(xp + one);
					temp.normalization();
					tempG = temp.getWithOtherParameter(-currentStruct.b);
					tempG.normalization();

					if (temp.getPolyPower() == 1) {
						temp = temp.getWithOtherParameter(-currentStruct.b);
					}

					polynoms.push(polynomsStruct(temp, tempG, currentStruct.b + 1));
					if (temp.getPolyPower() == 1) {
						temp = currentStruct.g.getWithOtherParameter(-currentStruct.b) / temp;
						temp.normalization();
					}
					else {
						temp = currentStruct.g.gcd(xp - one);
						temp.normalization();
					}
					tempG = temp.getWithOtherParameter(-currentStruct.b);
					tempG.normalization();
					if (!(temp == polynoms.top().current)) {
						polynoms.push(polynomsStruct(temp, tempG, currentStruct.b + 1));
					}
				}
			}
			else {
				if (current.getPolyPower() == 1) {
					ans.push_back(Polynom(prime,
						std::vector<long long>{-1LL * current.getTermKey(0)}
					));
				}
			}
		}
	}

	return ans;
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
    long long power2 = temp_2.getPolyPower();
    long long key = temp_2.getTermKey(power2);
    while (temp_1.getPolyPower() >= temp_2.getPolyPower()) {
        if (temp_1.getPolyPower() == 0) {
            if (count >= 1) {
                break;
            }
            count++;
        }
        Polynom multiply(p1.getPrime(), std::vector<long long>{0});
        multiply.addItem(multiply.makeItem(temp_1.getPolyPower() - power2,
                                           utils::division_for_numbers(temp_1.getTermKey(temp_1.getPolyPower()),
                                                                       key,
                                                                       p2.getPrime())));
        temp_2 = temp_2* multiply;
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
	long long pow = prime - 1;
	Matrix AMatrix(pow, pow, prime);
    std::vector<long long> coeffs(pow, 0);
    PolyTerm* term = getHead();
    while (term) {
        coeffs[term->pow % pow] += term->key;
        term = term->next;
    }
    delete term;

	for (long long i = 0, shift = 0; i < pow; i++, shift++) {
		for (long long j = 0; j < pow; j++) {
		    AMatrix.setElement(i, j, coeffs[(j + shift) % pow]);
		}
	}

    long long matrixRank = AMatrix.rank().first;
	if (valueAtPoint(0) == 0) {
	    return (pow - matrixRank + 1);
	} else {
        return (pow - matrixRank);
	}
}

Polynom Polynom::gcd(const Polynom& other) {
    Polynom* p1;
    Polynom* p2;
    if (other.getPolyPower() >= this->getPolyPower()) {
        p1 = new Polynom(other);
	p2 = new Polynom(*this);
    } else {
        p1 = new Polynom(*this);
	p2 = new Polynom(other);
    }
    //std::cout << "p1: " << p1->show() << std::endl;
    //std::cout << "p2: " << p2->show() << std::endl;

    while (p2->getHead() != nullptr) {
        Polynom* temp = p2;
	p2 = new Polynom(*p1 % *p2);
	delete p1;
	p1 = temp;

    	//std::cout << "p1: " << p1->show() << std::endl;
    	//std::cout << "p2: " << p2->show() << std::endl;
    }

    Polynom result;
    result = *p1;    

    delete p1;
    delete p2;

    return result;
}

/*9 This method calculates nth Cyclotomic polynomial*/
Polynom Polynom::CyclotomicPolynomial(int prime, int n) {
    // if (n % prime == 0) return Polynom();
    int m = n / 2;
    std::vector<long long> keys{ 1 };
    Polynom result(prime, keys);
    if (n % 2 == 0 && utils::isPrime(m) && m % 2 != 0 && m != 1) {
        int mob;
        if (utils::isPrime(m)) {
            std::vector<long long> keys(m, 1);
            for (int i = 0; i < m; i++) {
                if (i % 2 != 0)
                    keys[i] = -1;
            }
            return Polynom(prime, keys);
        }
        for (int d = 1; d <= m; d++) {
            if (m % d == 0 && utils::mobius(m / d) == 1) {
                std::vector<long long> keys(d + 1, 0);
                if (d % 2 != 0)
                    keys[d] = -1;
                else
                {
                    keys[d] = 1;
                }
                keys[0] = -1;
                Polynom multiplier(prime, keys);
                result = result * multiplier;
            }
        }
        for (int d = 1; d <= m; d++) {
            if (m % d == 0 && utils::mobius(m / d) == -1) {
                std::vector<long long> keys(d + 1, 0);
                keys[d] = 1;
                keys[0] = -1;
                Polynom divider(prime, keys);
                result = result / divider;
            }
        }
    }
    else {
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
    }
    return result;
}

/* 10 Factorization using Ri */
std::vector<Polynom> Polynom::factorizeCyclotomicRi(size_t n, size_t maxCount) {
    //std::cout << "Prime: " << prime << std::endl;
    //std::cout << "Current: " << this->show() << std::endl;
	if (n == 1) {
		return std::vector<Polynom> { Polynom(*this) };
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
				factors.emplace_back(factors[j]);
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
	polysToFactorize.emplace_back(*this);

	size_t factorsCount = utils::euler(n) / d;	
    long long factorPower = getPolyPower() / factorsCount;
	if (factorsCount == 1) {
		factors.emplace_back(*this);
		return factors;
	}
    //std::cout << "Factors count: " << factorsCount << "(max: " << maxCount << std::endl;
    if (maxCount > 0 && maxCount < factorsCount)
        factorsCount = maxCount;
    //std::cout << "Factors power: " << factorPower << std::endl;

	size_t i = 1;
	while (factors.size() < factorsCount) {
        //std::cout << "Trying R" << i << std::endl;
        //std::cout << "Found " << factors.size() << " out of " << factorsCount << std::endl;
		Polynom riPolynomial = Polynom(prime, std::vector<long long>());
		long long j = 1;

		PolyTerm* currentTerm = makeItem(i, 1);
		riPolynomial.head = currentTerm;

		long long mod = n / utils::gcd(n, i);
		while ((long long)std::pow(prime, j) % mod != 1) {
            //std::cout << "trying " << j << std::endl;
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
            if (j == 0 && (gcdRi == riPolynomial || gcdRi == polysToFactorize.front())) {
				factorized = false;
				break;
			}

			long long gcdPower = gcdRi.getPolyPower();
            if (gcdPower == factorPower) {
				factorized = true;
				gcdRi.normalization();
                //std::cout << "New factor " << gcdRi.show() << std::endl;
				factors.push_back(gcdRi);
			} else if (gcdPower > 0 && gcdPower % factorPower == 0) {
                //std::cout << "New poly to factorize" << std::endl;
				factorized = true;
				polysToFactorize.push_back(gcdRi);
			}

			riPolynomial = riPolynomial + Polynom(prime, std::vector<long long>(1, 1));
			j++;
		}
		if (factorized) {
            //std::cout << "Facrorized!" << std::endl;
			polysToFactorize.pop_front();
            //std::cout << "Polys to factorize: " << polysToFactorize.size() << std::endl;
            //std::cout << "Factors: " << factors.size() << std::endl;
            //std::cout << "===========================" << std::endl;
		}
		i++;

	}

	return factors;
}

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
            for (auto& ir : temp) {
                if (ir.getPolyPower() == n) {
                    result.push_back(ir);
                }
            }
        }
    }
    /*// Output
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i].show() << std::endl;
    }*/
    return result;
}

/* 12 Finds "size" irreducible polynomials of degree n */
std::vector<Polynom> Polynom::nIrreduciblePolynomials(long long prime, long long n, int size)
{
    std::vector<Polynom> result, temp;
    Polynom cyclotomic;

    // 3.31 Lidl
    long long num = pow(prime, n) - 1;
    for (long long m = 1; m <= num; ++m) {
        if ((num % m) == 0) {
            cyclotomic = Polynom::CyclotomicPolynomial(prime, m);
            if (cyclotomic.getPolyPower() < n) continue;

            temp = cyclotomic.factorizeCyclotomicRi(m, size - result.size());
            for (auto& ir : temp) {
                if (ir.getPolyPower() == n) {
                    if (result.size() < size) result.push_back(ir);
                    else return result;
                }
            }
            
        }
    }
    return result;
}

/* 12 Finds one irreducible polynomial of degree n */
Polynom Polynom::findIrreduciblePolynomial(long long prime, long long n)
{
    std::vector<Polynom> temp = nIrreduciblePolynomials(prime,n,1);
    if (temp.size() != 0) return temp[0];
    return Polynom();
}

/* 13 Irreducibility test */
bool Polynom::isIrreducible(){
    long long prime = this->getPrime();
    Polynom odd(prime, {0,1});
    Polynom one(prime, {1, 0});
    Polynom gcd_(prime, {0, 0});
    Polynom pol(*this);
    long long polPower(pol.getPolyPower());
    for(long long i = 1; i <= polPower/2; i++){
        long long power_ = pow(pol.getPrime(), i);
        Polynom x(prime, {{0, 0}, {power_, 1}});
        if((x-odd).getPolyPower() >= pol.getPolyPower()){
            gcd_= pol.gcd((x-odd)%pol);
        }else{
            gcd_=pol.gcd(x-odd);
        }
        if(gcd_.getPolyPower()!=0)
            return false;
    }
    return true;
}

Polynom Polynom::pthRoot(Polynom f) {
    int p = prime;
    std::vector<long long> roots;
    int power = f.getPolyPower();
    for (int i = 0; i <= power; i += p) {
        roots.push_back(f.getTermKey(i));
    }
    Polynom polynom(prime, roots);
    return polynom;
}

std::vector<std::pair<Polynom, long long>> Polynom::squareFreeDecomposition() const {
    std::vector<std::pair<Polynom, long long>> result;
    Polynom polynom(*this);
    Polynom one(prime, std::vector<long long>{1});
    long long s = 1;
    do {
        int j = 1;
        Polynom derivativePolynom = polynom.derivative();
        Polynom gcdPolynom = polynom.gcd(derivativePolynom);
        Polynom g = polynom / gcdPolynom;
        while (!(g == one)) {
            polynom = polynom / g;
            Polynom h = polynom.gcd(g);
            Polynom m = g / h;
            if (!(m == one)) {
                std::pair<Polynom, long long> polynomAndPower = { m,j * s };
                result.push_back(polynomAndPower);
            }
            g = h;
            j++;
        }
        if (!(polynom == one)) {
            polynom = polynom.pthRoot(polynom);
            s *= prime;
        }
    } while (!(polynom == one));
    return result;
}

/* build berlekamp matrix */
Matrix Polynom::buildBerlekampMatrix() const {
    std::vector<Polynom> M;
    Polynom one(prime, std::vector<long long>{1});
    M.push_back(one);
    Polynom current(*this);
    for (int i = 1; i < getPolyPower(); i++) {
        std::vector<std::vector<long long>> someVec = {{i * prime, 1}};
        Polynom polynomXPI(prime, someVec);
        Polynom remainder = polynomXPI % current;
        M.push_back(remainder);
    }

    Matrix matrix(getPolyPower(), getPolyPower(), prime);

    for (int i = 0; i < getPolyPower(); i++) {
        for (int j = 0; j < getPolyPower(); j++) {
            if(i != j){
                matrix.setElement(i, j, M[i].getTermKey(j));
            }
            else {
                matrix.setElement(i, j, M[i].getTermKey(j)-1);
            }
        }
    }
    return matrix;
}

std::vector<Polynom> Polynom::getComparisonSystemSolutionBasis() const {
    Matrix matrix = buildBerlekampMatrix();
    auto basis = matrix.buildSolutionSpaceBasis();
    std::vector<Polynom> polynomial_basis;
    for (size_t i = 0; i < basis.size(); i++) {
        polynomial_basis.push_back(Polynom{ prime, basis[i] });
    }
    return polynomial_basis;
}

std::vector<std::pair<std::vector<Polynom>, long long>> Polynom::berlekampAlgorithmMainCase(std::vector<std::pair<Polynom, long long>> const& unmultiple_factors) const {
    Polynom unmultiple_polynomial{ prime, { {0, 1}, {1, 0} } };
    for (size_t i = 0; i < unmultiple_factors.size(); i++) {
        unmultiple_polynomial = unmultiple_polynomial * unmultiple_factors[i].first;
    }
    auto polynomial_basis = unmultiple_polynomial.getComparisonSystemSolutionBasis();
    if (polynomial_basis.size() == 1) {
        return std::vector<std::pair<std::vector<Polynom>, long long>>{ { {*this}, 1} };
    }
    else {
        return factorizeByBasisPolynomials(unmultiple_factors, polynomial_basis);
    }
}

std::vector<std::pair<std::vector<Polynom>, long long>> Polynom::factorizeByBasisPolynomials(std::vector<std::pair<Polynom, long long>> const& unmultiple_factors, 
    std::vector<Polynom> const& basis) const {
    long long total_num_of_factors = basis.size();
    long long current_num_of_factors = unmultiple_factors.size();
    std::vector<std::pair<std::vector<Polynom>, long long>> result;

    for (size_t i = 0; i < unmultiple_factors.size(); i++) {
        result.push_back({ std::vector<Polynom>{ unmultiple_factors[i].first }, unmultiple_factors[i].second });
    }

    size_t basis_element_index = 1;
    while (current_num_of_factors != total_num_of_factors) {
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].first.size(); j++) {

                std::vector<Polynom> replacement;
                Polynom temp;

                if (result[i].first[j].getPolyPower() > 1) {
                    for (long long k = 0; k < prime; k++) {
                        temp = result[i].first[j].gcd(basis[basis_element_index] - Polynom{ prime, {k, 0} });
                        if (temp.getPolyPower() > 0) {
                            replacement.push_back(temp);
                            current_num_of_factors++;
                        }
                    }
                }

                if (!replacement.empty()) {
                    current_num_of_factors--;
                    result[i].first.insert(result[i].first.begin() + j, replacement.begin(), replacement.end());
                    j += replacement.size();
                    result[i].first.erase(result[i].first.begin() + j);
                    if (current_num_of_factors == total_num_of_factors) break;
                }
            }

            if (current_num_of_factors == total_num_of_factors) break;
            basis_element_index++;
        }
    }

    return result;
}

std::string Polynom::berlekampAlgorithm() const {
    auto unmultipled_polynomial = squareFreeDecomposition();
    auto result = berlekampAlgorithmMainCase(unmultipled_polynomial);
    std::string result_to_string;

    for (size_t i = 0; i < result.size(); i++) {
        long long power = result[i].second;
        for (size_t j = 0; j < result[i].first.size(); j++) {
            result_to_string.push_back('(');
            result_to_string += result[i].first[j].show();
            result_to_string.push_back(')');
            if (power > 1) result_to_string += "^" + std::to_string(power);
            if (j != result[i].first.size() - 1) result_to_string += " * ";
        }
        if (i != result.size() - 1) result_to_string += " * ";
    }

    return result_to_string;
}
