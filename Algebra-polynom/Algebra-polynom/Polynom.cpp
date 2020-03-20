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
    power = 0;
}

Polynom::Polynom(long long _power, std::vector<long long> keys) {
    power = _power;
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(i, keys[i]));
    }
}

Polynom::Polynom(long long _power, std::vector<std::pair<long long, long long>> keys) {
    power = _power;
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(keys[i].first, keys[i].second));
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
    el->key = el->key % power;
    if (el->key < 0)  el->key += power;
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
        t->key = (t->key + el->key) % power;
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
            t1->key = (t1->key + el->key) % power;
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
Polynom Polynom::addPoly(Polynom& pol1, Polynom& pol2) {
    Polynom pol3 = pol1;
    //pol3.setHead(pol1.getHead());
    PolyTerm* tmp2 = pol2.getHead();
    while (tmp2) {
        pol3.addItem(makeItem(tmp2->pow,tmp2->key));
        tmp2 = tmp2->next;
    }
    return pol3;
}
/*1     operation +       */
Polynom operator+(Polynom& p1, Polynom& p2) {
    Polynom c = c.addPoly(p1, p2);
    return c;
}
/*1     operation -       */
Polynom Polynom::diffPoly(Polynom& pol1, Polynom& pol2) {
    Polynom pol3 = pol1;
    //pol3.setHead(pol1.getHead());
    cout << "pol1 ";
    pol1.show();
    PolyTerm* tmp2 = pol2.getHead();
    while (tmp2) {
        pol3.addItem(makeItem(tmp2->pow, -tmp2->key));
        tmp2 = tmp2->next;
    }
    return pol3;
}
/*1     operation -       */
Polynom operator-(Polynom& p1, Polynom& p2) {
    Polynom c = c.diffPoly(p1, p2);
    return c;
}
/*1     operation *       */
Polynom Polynom::multPoly(Polynom& pol1, Polynom& pol2) {

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

    return Polynom(pow, num);
}
/*1     operation *       */
Polynom operator*(Polynom& p1, Polynom& p2) {
    Polynom c = c.multPoly(p1, p2);
    return c;
}

/**/

