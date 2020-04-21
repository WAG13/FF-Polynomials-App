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
#include "../Matrix/Matrix.hpp"

 /*!
  * @brief class Polynom that describes polynomial
  * @details 
  * polynomials in field p^n (p - prime)
  * coefficient             by (mod p)
  * power of this polinom -         n
  * Every object contains with terms (PolyTerm)
  * Every structure "PolyTerm" have objects that contains fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PolyTerm"
  */
class Polynom {
private:
    long long prime;    // p
    long long power;    // n
    // Structure that describes term of Polynom
    struct PolyTerm {
        long long key;      // Coefficient of terms of polynomial
        long long pow;      // Power of term
        PolyTerm* next;     // Pointer to next term
    };
    PolyTerm* head;         // Pointer to the first term of polynom

public:
    /*constructors*/
    Polynom();
    Polynom(long long _prime, long long _power, std::vector<long long> keys);   //for all terms
    Polynom(long long _prime, long long _power, std::vector<std::pair<long long, long long>> keys); //for some terms
    /*destructor*/
    ~Polynom() { }

    /*Getters and Setters*/
    PolyTerm* getHead() const { return head; }
    PolyTerm* getTerm(long long pow) const {    //retuns term by its power
        PolyTerm* tmp = head;
        if (head == nullptr) return nullptr;
        while (tmp) {
            if (tmp->pow == pow) return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }
    long long getTermKey(long long pow) const {    //retuns coef of a term by its power
        PolyTerm* term = getTerm(pow);
        if (term) return term->key;
        return 0;
    }
    // return power of a field
    long long getPower() const { return power; } 
    long long getPrime() const { return prime; }
    void setHead(PolyTerm* _head) { head = _head; }
    void setPower(long long _power) { power = _power; }
    void setPrime(long long _prime) { prime = _prime; }
    void copy(const Polynom pol) {
        prime = pol.getPrime();
        power = pol.getPower();
        head = nullptr;
        PolyTerm* tmp = pol.getHead();
        while (tmp) {
            addItem(makeItem(tmp->pow, tmp->key));
            tmp = tmp->next;
        }
    };
    void show();
    // return power of a polinomial
    long long getPolyPower() const {
        long long pow = 0;
        PolyTerm* tmp = head;
        if (head == nullptr) return pow;
        while (tmp) {
            if (tmp->pow > pow) { pow = tmp->pow; }
            tmp = tmp->next;
        }
        return pow; 
    }
    // Creates new term (PolyTerm) with coefficient val
    PolyTerm* makeItem(long long pow, long long val);
    // Adding term to the polynom in non-descending order
    void addItem(PolyTerm* el);
    
    /** #1      @author Daryna Bondarets    **/
    /*! #1
    * @brief Adding two polynomials in field
    */
    friend Polynom operator +(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    friend Polynom operator -(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    friend Polynom operator *(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    friend Polynom operator *(Polynom const& p, long long const& number);
    friend Polynom operator *(long long const &number, Polynom const& p);
	/* #6
	* @brief Divides polynomial in field
	*/
	friend Polynom operator /(Polynom const& p1, Polynom const& p2);
	/* #6
	* @brief Get rest from the divison of polinomials
	*/
	friend Polynom operator %(Polynom const& p1, Polynom const& p2);
    /** #2      @author Darik Ivashyn    **/
    //...

    /** #3      @author Karina Masol & Yuriy Momotenko     **/
    //...

    /** #4      @author Yana Skyrda    **/
    /*! #4
    * @brief This function implements algorithm  for finding number of roots for polynomial
    *        in accordance with Konig-Rados theorem
    */
    long long rootsNumber();

protected:
    /*! #1
    * @brief Adding two polynomials in field
    */
    Polynom addPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    Polynom diffPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    Polynom multPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field with power=1
    */
    Polynom multSimple(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    Polynom multNumber(Polynom const& p, long long const& number);


	/*! #6
	* @brief Multiplication of two polynomials in field 
	*/
	Polynom multPolyforDivide(Polynom const& p1, Polynom const& p2);
	/*! #6
	* @brief Division
	*/
	std::pair<Polynom, Polynom> simple_division(Polynom const & p1, Polynom const & p2) const;
	/*! #6
	* @brief Inverse for numbers
	*/
	long long division_for_numbers(long long a, long long b, long long prime);
	/*! #6
	* @brief Inverse for numbers
	*/
	long long inverse(long long number, long long prime);
	/*! #6
	* @brief Function for inverse
	*/
	void decrease(long long& a, long long& b, long long& a_count_in_a, long long& a_count_in_b) const;

};
