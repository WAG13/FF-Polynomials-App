/*!
 * @file Polynom.h
 * @brief Header file for class Polynom
 * @details Definition of the class Polynom
 */

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "../Matrix/Matrix.h"

/*!
  * @brief class Polynom that describes polynomial in a ring GF(p)[X]
  * @details 
  * polynomials over field GF(p) (p is prime)
  * coefficient             by (mod p)
  * power of the polynomial -         n
  * Every object consists of terms (PolyTerm)
  * Every structure "PolyTerm" has fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PolyTerm"
  */
class Polynom
{
private:
    long long prime; // p
    // Structure that describes a single term of the polynomial
    struct PolyTerm
    {
        long long key;  // Coefficient of the term
        long long pow;  // Power of the term
        PolyTerm *next; // Pointer to the next term

        /*destructor*/
        ~PolyTerm()
        {
            if (next)
                delete next;
        }
    };
    PolyTerm *head; // Pointer to the first term of polynom

public:
    /*constructors*/
    Polynom();
    Polynom(long long _prime, std::vector<long long> keys);              //for all terms
    Polynom(long long _prime, std::vector<std::vector<long long>> keys); //for some terms
    Polynom(long long _prime, std::string polynom, char X);
    Polynom(const Polynom &other)
    { // copy constructor
        this->prime = other.prime;
        head = nullptr;
        PolyTerm *tmp = other.getHead();
        while (tmp)
        {
            addItem(makeItem(tmp->pow, tmp->key));
            tmp = tmp->next;
        }
        tmp = nullptr;
    }
    Polynom(Polynom &&other) noexcept
    { // move constructor
        this->prime = other.prime;
        this->head = other.head;
        other.head = nullptr;
    }
    /*destructor*/
    ~Polynom()
    {
        if (head)
            delete head;
    }

    /*Getters and Setters*/
    PolyTerm *getHead() const { return head; }
    PolyTerm *getTerm(long long pow) const
    { //retuns term by its power
        PolyTerm *tmp = head;
        if (head == nullptr)
            return nullptr;
        while (tmp)
        {
            if (tmp->pow == pow)
                return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }
    long long getTermKey(long long pow) const
    { //retuns coef of the term by its power
        PolyTerm *term = getTerm(pow);
        if (term)
            return term->key;
        return 0;
    }
    // returns power of the field
    long long getPrime() const { return prime; }
    void setHead(PolyTerm *_head) { head = _head; }
    void setPrime(long long _prime) { prime = _prime; }
    void operator=(const Polynom &other)
    {
        prime = other.getPrime();
        if (head)
            delete head;
        head = nullptr;
        PolyTerm *tmp = other.getHead();
        while (tmp)
        {
            addItem(makeItem(tmp->pow, tmp->key));
            tmp = tmp->next;
        }
        tmp = nullptr;
    };

    /*!
     * @brief Returns string representation of the polynomial
     */
    std::string show() const;

    /*!
     * @brief Returns power of the polynomial
     */
    long long getPolyPower() const
    {
        long long pow = 0;
        PolyTerm *tmp = head;
        if (head == nullptr)
            return pow;
        while (tmp)
        {
            if (tmp->pow > pow)
            {
                pow = tmp->pow;
            }
            tmp = tmp->next;
        }
        return pow;
    }

    // Creates new term (PolyTerm) with coefficient val
    PolyTerm *makeItem(long long pow, long long val);
    // Adding term to the polynomial in non-descending order
    void addItem(PolyTerm *el);

    /*! #1
     * @author Daryna Bondarets
     * @brief Adds polynomials over the field
     */
    friend Polynom operator+(Polynom const &p1, Polynom const &p2);
    
    /*! #1
     * @author Daryna Bondarets
     * @brief Finds difference of polynomials over the field
     */
    friend Polynom operator-(Polynom const &p1, Polynom const &p2);
    
    /*! #1
     * @author Daryna Bondarets
     * @brief Multiplies polynomials over the field
     */
    friend Polynom operator*(Polynom const &p1, Polynom const &p2);
    
    /*! #1
     * @author Daryna Bondarets
     * @brief Multiplies a polynomial on an integer constant over the field
     */
    friend Polynom operator*(Polynom const &p, long long const &number);
    friend Polynom operator*(long long const &number, Polynom const &p);
    
    /*! #6
     * @author Daryna Bondarets
	 * @brief Divides polynomials over the field
	 */
    friend Polynom operator/(Polynom const &p1, Polynom const &p2);
    
    /*! #6
     * @author Daryna Bondarets
	 * @brief Takes the remainder of a division of polynomials over the field
	 */
    friend Polynom operator%(Polynom const &p1, Polynom const &p2);
    
    /*! #2
     * @author Darik Ivashyn
	 * @brief Takes the derivative of the polynomial
	 */
    Polynom derivative() const;
    
    /*! #2
     * @author Darik Ivashyn
	 * @brief Calculates the value of the polynomial at a given point
	 */
    long long valueAtPoint(long long x) const;
    
    /*! #2
     * @author Darik Ivashyn
	 * @brief Normalization of the polynomial
	 */
    void normalization();

    /*! #3
     * @author Karina Masol & Yuriy Momotenko
	 * @brief Finds roots of the polynomial
	 */
    std::vector<Polynom> findRoots();
    
    /*! #3
     * @author Karina Masol & Yuriy Momotenko
	 * @brief Raises the polynomial to a given power
	 */
    Polynom toThePower(long long pow) const;
    
    /*! #3
     * @author Karina Masol & Yuriy Momotenko
	 * @brief Gets a polynomial of the form f(x-b)
	 */
    Polynom getWithOtherParameter(long long b) const;

    /*! #4
     * @author Yana Skyrda 
     * @brief Implements an algorithm for finding number of roots for polynomial
     *        in accordance with Konig-Rados theorem
     */
    long long rootsNumber();

    /*! #7
     * @author Nikita Pupov
	 * @brief Calculates the greatest common divisor of two polynomials
	 */
    Polynom gcd(const Polynom& other);

    /* #9
     * @author Nikita Pupov
     * @brief Equality operator
     */
    friend bool operator==(Polynom const &p1, Polynom const &p2);

    /*! #9
     * @author Rostyslav Mochulskyi
     * @brief Calculates n-th cyclotomic polynomial
     */
    static Polynom CyclotomicPolynomial(int prime, int n);

    /*! #10
     * @author Hryshchenko Yurii
     * @brief Gets irreducible factors of nth cyclomotic polynomial using Ri polynomials
     * @param amount If maxCount > 0, finds "maxCount" factors at most, otherwise finds all factors
     */
    std::vector<Polynom> factorizeCyclotomicRi(size_t n, size_t maxCount = 0);

    /*! #12
     * @author Vladyslav Prokopchuk
     * @brief Finds all irreducible polynomials of degree n
     * @return Vector of all irreducible polynomials of degree n
     */
    static std::vector<Polynom> allIrreduciblePolynomials(long long prime, long long n);

    /*! #12
     * @brief Finds "size" irreducible polynomials of degree n
     * @return Vector of all irreducible polynomials of degree n
     */
    static std::vector<Polynom> nIrreduciblePolynomials(long long prime, long long n, int size);

    /*! #12
     * @author Vladyslav Prokopchuk
     * @brief Finds one irreducible polynomial of degree n
     * @return Irreducible polynomial of degree n
     */
    static Polynom findIrreduciblePolynomial(long long prime, long long n);

    /*! #13
     * @author Totskyi Alexander
     * @brief Checks if the polynomial is irreducible
     * @return 1 - if irreducible, 0 - reducible
     */
    bool isIrreducible();

    /*! @author Medynskyi Mykola, Pashchenko Dmytro
     * @brief Finds Berlekamp matrix
     * @return Berlekamp matrix
     */
    Matrix buildBerlekampMatrix() const;

    /*! @author Medynskyi Mykola, Pashchenko Dmytro
     * @brief Factorizes the polynomial via Berlekamp algorithm
     * @return String representation of the factorized polynomial
     */
    std::string berlekampAlgorithm() const;

protected:
    /* #1
     * @brief Adds polynomials over the field
     */
    Polynom addPoly(Polynom const &p1, Polynom const &p2);
    
    /* #1
     * @brief Finds difference of polynomials over the field
     */
    Polynom diffPoly(Polynom const &p1, Polynom const &p2);
    
    /* #1
     * @brief Multiplies polynomials over the field
     */
    Polynom multPoly(Polynom const &p1, Polynom const &p2);
    
    /* #1
     * @brief Multiplies polynomials over the field with power=1
     */
    Polynom multSimple(Polynom const &p1, Polynom const &p2);
    
    /* #1
     * @brief Multiplies polynomial on an integer constant over the field
     */
    Polynom multNumber(Polynom const &p, long long const &number);

    /* #6
	 * @brief Multiplies polynomials over the field 
	 */
    Polynom multPolyforDivide(Polynom const &p1, Polynom const &p2);
    
    /*! #6
	 * @brief Divides polynomials over the field
	 */
    std::pair<Polynom, Polynom> simple_division(Polynom const &p1, Polynom const &p2) const;

    /*! @author  Datsiuk Vitaliy, Medynskyi Mykola
     * @brief Computes the square free decomposition of the given polynomial
     * list of pairs. The first element of the pair is a factor of the given
     * polynomial, and the second, its multiplicity.
     * @return std:vector of pairs<Polynom, int>
     */
    std::vector<std::pair<Polynom, long long>> squareFreeDecomposition() const;

    /*! @author Medynskyi Mykola
     * @brief Finds pth root of a given polynomial
     * @return Polynomial
     */
    Polynom pthRoot(Polynom f);

    std::vector<std::pair<std::vector<Polynom>, long long>> berlekampAlgorithmMainCase(std::vector<std::pair<Polynom, long long>> const& unmultiple_factors) const;

    /*! @author Pashchenko Dmytro
     * @brief Builds polynomial basis of solution space of comparison system h^p = h (mod f)
     * @return Basis polynomials
     */
    std::vector<Polynom> getComparisonSystemSolutionBasis() const;

    std::vector<std::pair<Polynom, long long>> sort_polynomials_by_power(std::vector<std::pair<std::vector<Polynom>, long long>> const& polynomials) const;

    /*! @author Pashchenko Dmytro
     * @brief Factorizes unmultiple factors using basis polynomials (f = �(gcd(f, h - a)))
     * @return std::vector of pairs "polynomials, their multiplicity"
     */
    std::vector<std::pair<std::vector<Polynom>, long long>> factorizeByBasisPolynomials(std::vector<std::pair<Polynom, long long>> const &unmultiple_factors, 
        std::vector<Polynom> const &basis) const;
};
