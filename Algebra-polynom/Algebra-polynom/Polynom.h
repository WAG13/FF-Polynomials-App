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

 /*!
  * @brief class Polynom that describes polynomial
  * @details 
  * polynomials in field q^n (q - simple)
  * power of this polinom - q^n (q - simple)
  * Every object contains with terms (PolyTerm)
  * Every structure "PolyTerm" have objects that contains fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PolyTerm"
  */
class Polynom {
private:
    long long power;
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
    Polynom(long long _power, std::vector<long long> keys);
    Polynom(long long _power, std::vector<std::pair<long long, long long>> keys);
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
    void setHead(PolyTerm* _head) { head = _head; }
    void setPower(long long _power) { power = _power; }

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
    
    
    /** #2      @author Darikiva    **/
    //...

    /** #3      @author karina_masol & yuriy_momotenko     **/
    //...
};
