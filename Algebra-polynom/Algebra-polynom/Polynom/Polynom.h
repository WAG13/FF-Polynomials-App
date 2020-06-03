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
  * @brief class Polynom that describes polynomial
  * @details 
  * polynomials in field p (p - prime)
  * coefficient             by (mod p)
  * power of this polinom -         n
  * Every object contains with terms (PolyTerm)
  * Every structure "PolyTerm" have objects that contains fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PolyTerm"
  */
class Polynom
{
private:
    long long prime; // p
    // Structure that describes term of Polynom
    struct PolyTerm
    {
        long long key;  // Coefficient of terms of polynomial
        long long pow;  // Power of term
        PolyTerm *next; // Pointer to next term

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
    { //retuns coef of a term by its power
        PolyTerm *term = getTerm(pow);
        if (term)
            return term->key;
        return 0;
    }
    // return power of a field
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

    std::string show() const;
    // return power of a polinomial
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
    // Adding term to the polynom in non-descending order
    void addItem(PolyTerm *el);

    /** #1      @author Daryna Bondarets    **/
    /*! #1
    * @brief Adding two polynomials in field
    */
    friend Polynom operator+(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    friend Polynom operator-(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    friend Polynom operator*(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    friend Polynom operator*(Polynom const &p, long long const &number);
    friend Polynom operator*(long long const &number, Polynom const &p);

    /* #6
	* @brief Divides polynomial in field
	*/
    friend Polynom operator/(Polynom const &p1, Polynom const &p2);
    /* #6
	* @brief Get rest from the divison of polinomials
	*/
    friend Polynom operator%(Polynom const &p1, Polynom const &p2);
    /** #2      @author Darik Ivashyn    **/
    //...
    Polynom derivative() const;
    long long valueAtPoint(long long x) const;
    void normalization();

    /** #3      @author Karina Masol & Yuriy Momotenko     **/
    //Finding roots of the polynomial
    std::vector<Polynom> findRoots();
    //bringing polynomial to the power
    Polynom toThePower(long long pow) const;
    //get instead of polynom f(x) - polynom f(x-b)
    Polynom getWithOtherParameter(long long b) const;

    /** #4      @author Yana Skyrda    **/
    /*! #4
    * @brief This function implements algorithm  for finding number of roots for polynomial
    *        in accordance with Konig-Rados theorem
    */
    long long rootsNumber();

    /** #7      @author Nikita Pupov    **/
    /*! #7
	* @brief This method calculates greatest common divisor of two polynoms
	*/
    Polynom gcd(const Polynom& other);

    /* #9
    * @brief Equal operator
    */
    friend bool operator==(Polynom const &p1, Polynom const &p2);

    /** #9      @author Rostyslav Mochulskyi   **/
    /*! #9
    * @brief This method calculates nth cyclotomic polynomial
    */
    static Polynom CyclotomicPolynomial(int prime, int n);

    /*! #10
     * @author Hryshchenko Yurii
     * @brief Gets irreducible factors of nth cyclomotic polynomial using Ri polynomials
     * @param amount If maxCount > 0, finds "maxCount" factors at most, otherwise finds all factors.
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

    /*! @author Medynskyi Mykola
    * @brief Finds berlekamp matrix
    * @return berlekamp matrix
    */
    Matrix buildBerlekampMatrix() const;

    /*! @author Medynskyi Mykola, Pashchenko Dmytro
    * @brief factorizes polynomial by Berlekamp algorithm
    * @return string with factorized polinomial
    */
    std::string berlekampAlgorithm() const;

protected:
    /*! #1
    * @brief Adding two polynomials in field
    */
    Polynom addPoly(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    Polynom diffPoly(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    Polynom multPoly(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Multiplication of two polynomials in field with power=1
    */
    Polynom multSimple(Polynom const &p1, Polynom const &p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    Polynom multNumber(Polynom const &p, long long const &number);

    /*! #6
	* @brief Multiplication of two polynomials in field 
	*/
    Polynom multPolyforDivide(Polynom const &p1, Polynom const &p2);
    /*! #6
	* @brief Division
	*/
    std::pair<Polynom, Polynom> simple_division(Polynom const &p1, Polynom const &p2) const;

    /*! @author  Datsiuk Vitaliy, Medynskyi Mykola
    * @brief Computes the square free decomposition of the given polynomial. Returns a
    * list of pairs. The first element of the pair is a factor of the given
    * polynomial, and the second, its multiplicity.
    * @return vector of pairs<Polynom, int>
    */
    std::vector<std::pair<Polynom, long long>> squareFreeDecomposition() const;

    /*! @author Medynskyi Mykola
    * @brief Finds pth root of given polynom
    * @return polynom
    */
    Polynom pthRoot(Polynom f);

    std::vector<std::pair<std::vector<Polynom>, long long>> berlekampAlgorithmMainCase(std::vector<std::pair<Polynom, long long>> const& unmultiple_factors) const;

    /*! @author Pashchenko Dmytro
    * @brief builds polynomial basis of solution space of comparison system h^p = h (mod f)
    * @return basis polynomials
    */
    std::vector<Polynom> getComparisonSystemSolutionBasis() const;

    /*! @author Pashchenko Dmytro
    * @brief factorizes unmultiple factors using basis polynomials (f = Ï(gcd(f, h - a)))
    * @return massive with pairs "polynomials, their multiplicity"
    */
    std::vector<std::pair<std::vector<Polynom>, long long>> factorizeByBasisPolynomials(std::vector<std::pair<Polynom, long long>> const &unmultiple_factors, 
        std::vector<Polynom> const &basis) const;
};
