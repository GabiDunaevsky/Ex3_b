/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;


int main() {
    Fraction a(5,3), b(14,21);
    cout << "a: " << a << "b: " << b << endl;
    cout << "a+b" << a+b << endl; 
    cout << "a-b" << a-b << endl; 
    cout << "a/b" << a/b << endl; 
    cout << "a*b" << a*b << endl; 
    cout << "2.3*b" << 2.3*b << endl; 
    cout << "a+2.421" << a+2.421 << endl; 
    Fraction c = a+b-1;
    cout << c++ << endl;
    cout << --c << endl;
    cout << "c >=b ? : " << (c >= b) << endl;
    if (a > 1.1) cout << " a is bigger than 1.1" << endl;
    else cout << " a is smaller than 1.1" << endl;
    /*
    a++;
    cout << "a Nom= " << a.getNumerator() << endl;
    cout << "a Den= " << a.getDenominator() << endl;
    cout << "b Nom= " << b.getNumerator() << endl;
    cout << "b Den= " << b.getDenominator() << endl;
    cout << "c Nom= " << c.getNumerator() << endl;
    cout << "c Den= " << c.getDenominator() << endl;
    a+Fraction{3,4};
    cout << a.getNumerator() << endl;
    Fraction e(1200, 2400), d(300,500);
    bool tmpp = e>d;
    cout << tmpp << endl;
    bool hhh = e>=d;
    cout << hhh << endl;
    Fraction gabi = Fraction{1, 2} + 0.5;
    cout << gabi.getNumerator() << endl;
    std::stringstream ss;
    ss.str("");
    Fraction neg_frac{-7, 9};
    // ss << neg_frac;
    cout << neg_frac << endl;
    Fraction fgh (2,5);
    istringstream is("20 56");
    is >> fgh;
    cout << fgh << endl;
    */
}
