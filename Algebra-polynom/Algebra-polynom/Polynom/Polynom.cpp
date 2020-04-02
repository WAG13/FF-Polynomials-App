 /*!
  * @file Polynom.cpp
  * @brief Implementation of class Polynom
  * @details Functional of polynomial
  */

#include "Polynom.h"

using std::cout;
using std::cin;
using std::endl;

Polynom::Polynom() {
    head = nullptr;
    power = 1;
    prime = 1;
}

Polynom::Polynom(long long _prime, long long _power, std::vector<long long> keys) :prime(_prime), power(_power) {
    head = nullptr;
    if (power == 1) {
        n1 = true;
        power = prime;
    }
    for (int i = 0; i < keys.size(); i++) {
        if (i < power) addItem(makeItem(i, keys[i]));
    }
}

Polynom::Polynom(long long _prime, long long _power, std::vector<std::pair<long long, long long>> keys) :prime(_prime), power(_power) {
    head = nullptr;
    if (power == 1) {
        n1 = true;
        power = prime;
    }
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i].first < power) addItem(makeItem(keys[i].first, keys[i].second));
    }
}

Polynom::PolyTerm* Polynom::makeItem(long long pow, long long value) {
    auto* el = new PolyTerm;
    el->key = value;
    el->pow = pow;
    el->next = nullptr;
    return el;
}

void Polynom::addItem(Polynom::PolyTerm* el) {
    el->key = el->key % prime;
    if (el->key < 0)  el->key += prime;
    if (el->key != 0){
    //checks if polinom is empty 
    if (head == nullptr)
    {
        head = el;
        return;
    }
    PolyTerm* t = head;
    //checks if polinoms head
    if (t->pow == el->pow)
    {
        t->key = (t->key + el->key) % prime;
        if (t->key == 0) {
            head = t->next;
            //delete t;
        }
        return;
    }
    else if (t->pow > el->pow)
    {
        el->next = t;
        head = el;
        return;
    }
    //checks the rest terms of polinom
    PolyTerm* t1 = t->next;
    while (t1)
    {
        if (t1->pow == el->pow)
        {
            t1->key = (t1->key + el->key) % prime;
            if (t1->key == 0) {
                //delete t->next;
                t->next = t1->next;
            }
            return;
        }
        else if (t1->pow > el->pow)
        {
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

void Polynom::show() {
    PolyTerm* tmp = head;
    bool isFirst = true;
    while (tmp != nullptr) {
        if (!isFirst) { cout << " + "; }
        else { isFirst = false; }
        cout << tmp->key;
        if (tmp->pow != 0) cout << "*x^" << tmp->pow;
        tmp = tmp->next;
    }
    cout << endl;
}


/*1     operation +       */
Polynom Polynom::addPoly(const Polynom pol1, const Polynom pol2) {
    Polynom pol3 = pol1;
    PolyTerm* tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow,tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}
/*1     operation +       */
Polynom operator+(const Polynom p1, const Polynom p2) {
    Polynom c = c.addPoly(p1, p2);
    return c;
}
/*1     operation -       */
Polynom Polynom::diffPoly(const Polynom pol1, const Polynom pol2) {
    Polynom pol3 = pol1;
    PolyTerm* tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow, -tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}
/*1     operation -       */
Polynom operator-(const Polynom p1, const Polynom p2) {
    Polynom c = c.diffPoly(p1, p2);
    return c;
}
/*1     operation *       */
Polynom Polynom::multPoly(const Polynom pol1, const Polynom pol2) {

   if (n1) {
    long long pow = pol1.power * pol2.power - 1;
    std::vector<long long> num(pow + 1);

    PolyTerm* tmp1 = pol1.getHead();
    PolyTerm* tmp2 = pol2.getHead();
    long long i = 0;
    long long j = 0;

    while (tmp1) {
        while (tmp2) {
            if ((power + 1) > (i + j))
                num[i + j] = num[i + j] + (tmp1->key * tmp2->key);
            j++;
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
        i++;
        tmp2 = pol2.head;
        j = 0;
    }

    return Polynom(pow, 1, num);

   }
   else {
   //TODO: mult when n>1
    return Polynom();
   }
    
}
/*1     operation *       */
Polynom operator*(const Polynom p1, const Polynom p2) {
    Polynom c = c.multPoly(p1, p2);
    return c;
}

/**/

/*4     Number of roots       */
long long Polynom::rootsNumber() {
    long long power = getPower() - 1;
    Matrix AMatrix(power, power);

    for (long long i = 0, shift = 0; i < power; i++, shift++) {
        for (long long j = 0; j < power; j++) {
            auto currTerm = getTerm((j + shift) % power);
            if (currTerm != nullptr) {
                AMatrix.setElement(i, j, currTerm->key);
            }
            else {
                AMatrix.setElement(i, j, 0);
            }
        }
    }

    long long matrixRank = AMatrix.rank();
    return (power - matrixRank);
}
