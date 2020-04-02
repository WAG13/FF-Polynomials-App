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
  * polynomials in field q^n (q - prime)
  * coefficient             by (mod q)
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
    bool n1 = false;    //checks if n=1 
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
    long long getPower() const { return power; }
    long long getPrime() const { return prime; }
    void setHead(PolyTerm* _head) { head = _head; }
    void setPower(long long _power) { power = _power; }
    void setPrime(long long _prime) { prime = _prime; }

    void show();
    
    // Creates new term (PolyTerm) with coefficient val
    PolyTerm* makeItem(long long pow, long long val);
    // Adding term to the polynom in non-descending order
    void addItem(PolyTerm* el);
    
    /** #1      @author Daryna Bondarets    **/
    /*! #1
    * @brief Adding two polynomials in field
    */
    Polynom addPoly(const Polynom pol1, const Polynom pol2);
    friend Polynom operator +(const Polynom p1, const Polynom p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    Polynom diffPoly(const Polynom pol1, const Polynom pol2);
    friend Polynom operator -(const Polynom p1, const Polynom p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    Polynom multPoly(const Polynom pol1, const Polynom pol2);
    friend Polynom operator *(const Polynom p1, const Polynom p2);
    
    
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

};
