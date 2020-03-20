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
    Polynom addPoly(Polynom& pol1, Polynom& pol2);
    friend Polynom operator +(Polynom& p1, Polynom& p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    Polynom diffPoly(Polynom& pol1, Polynom& pol2);
    friend Polynom operator -(Polynom& p1, Polynom& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    Polynom multPoly(Polynom& pol1, Polynom& pol2);
    friend Polynom operator *(Polynom& p1, Polynom& p2);
    
    
    /** #2      @author Darikiva    **/
    //...

    /** #3      @author karina_masol & yuriy_momotenko     **/
    //...
};
