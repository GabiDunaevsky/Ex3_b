#include "exception"
#include "vector"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include "Fraction.hpp"
#include <numeric>

#define MAX_INT std::numeric_limits<int>::max()
#define MIN_INT std::numeric_limits<int>::min()

using namespace std;


/*
Sources for this task:
    https://stackoverflow.com/questions/58212508/c-identifier-is-undefined
    https://stackoverflow.com/questions/13334169/compare-fraction-without-overflow
    https://github.com/idankam/EX3-B-CPP/blob/master/sources/Matrix.cpp
    https://stackoverflow.com/questions/26171631/throwing-a-run-time-error
    https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
    https://www.geeksforgeeks.org/inbuilt-function-calculating-lcm-cpp/
    https://learn.microsoft.com/en-us/cpp/preprocessor/hash-define-directive-c-cpp?view=msvc-170
    https://stackoverflow.com/questions/16610586/istream-operator-overloading-c
    https://en.cppreference.com/w/cpp/language/operators
    I was also using chat gpt in several functions
    While making some of the functions i took advises from a friend
    https://www.javatpoint.com/friend-function-in-cpp
    https://learn.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
*/

namespace ariel {
    // A deafult constructor.
    Fraction::Fraction(){
        this->numerator = 1;
        this->denominator = 1;
    }
    //A regular constructor.
    Fraction::Fraction(int numerator,int denominator){
        if(denominator == 0){
            throw std::invalid_argument("denominator can't be 0");
            //throw runtime_error("denominator can't be 0");
        }
        this->numerator = numerator;
        this->denominator = denominator;
    }
    // A constructor that is getting float and returning a fraction(requierd by the student tests).
    Fraction::Fraction(float num){
        Fraction tmp = floatTofraction(num);
        this->numerator = tmp.getNumerator();
        this->denominator = tmp.getDenominator();
    }
    /*
    Getters and setters functions.
    */
    int Fraction::getNumerator(){
        return this->numerator;
    }
    void Fraction::setNumerator(int numerator){
        this->numerator = numerator;
    }

    int Fraction::getDenominator(){
        return this->denominator;
    }
    void Fraction::setDenominator(int denominator){
        if(denominator == 0){
            // throw std::invalid_argument("denominator can't be 0");
            throw runtime_error("denominator can't be 0");
        }
        this->denominator = denominator;
    }
    //A static function that returns the reduced fraction by dividing the gcd.
    Fraction Fraction::findReducedFrac(const Fraction &frac){
       int gcd = __gcd(frac.numerator , frac.denominator);
       return Fraction(frac.numerator / gcd , frac.denominator / gcd);
    }
    //A static function that getting a float and returns a fraction.(i found this function by using gpt).
    Fraction Fraction::floatTofraction(float fNum) {
        int i = 0;
        while(i < 3 && fNum != round(fNum)){
            fNum = fNum * 10;
            i++;
        }
        return Fraction(round(fNum) , pow(10, i));
    }
    //A static function that returns true for positive function and false for negative function (This is a helper function)
    bool Fraction::checkFracPos(const Fraction &frac){
        if(frac.numerator < 0 && frac.denominator > 0 || frac.numerator > 0 && frac.denominator < 0){
            return false;
        }
        return true;
    }

    
    //-----------------------------
    // Arithmetic Operators
    //-----------------------------

    //This operator is for the operation "-" between 2 fractions.
    //In this function i got my idea while talking to a friend
    Fraction Fraction::operator-(const Fraction &frac){
        int findLcm = std::lcm(denominator, frac.denominator); // find the lcm between the denomeraitors(the new common denomirator).
        int newNumF1 = this->numerator * findLcm / denominator;// the new numarator of frac1.
        int newNumF2 = frac.numerator * findLcm / frac.denominator;// the new numarator of frac2.
         if (newNumF1 > 0 && newNumF2 < newNumF1 - MAX_INT) {// this condition is by the tests (0 dosnt matter because sub of 0 canot be smaller then min)
            throw std::overflow_error("Invalid fraction");
        }
        if( newNumF1 < 0 && newNumF2 > newNumF1 - MIN_INT){
            throw std::overflow_error("Invalid fraction");
        }
        Fraction frc(newNumF1 - newNumF2, findLcm);
        return  Fraction::findReducedFrac(frc);
    }
    //This operator is for the operation "+" between 2 fractions.
    //In this function i got my idea while talking to a friend
    Fraction Fraction::operator+(const Fraction &frac){
        int findLcm = std::lcm(denominator, frac.denominator);// find the lcm between the denomeraitors(the new common denomirator).
        int newNumF1 = this->numerator * findLcm / denominator;// the new numarator of frac1.
        int newNumF2 = frac.numerator * findLcm / frac.denominator;// the new numarator of frac2.
         if (newNumF1 > 0 && newNumF2 > MAX_INT - newNumF1) {// this condition is by the tests (0 dosnt matter because sub of 0 canot be נןעעקר then max)
            throw std::overflow_error("Invalid fraction");
        }
        if(newNumF1 < 0 && newNumF2 < MIN_INT - newNumF1){
            throw std::overflow_error("Invalid fraction");
        }
        Fraction frc(newNumF1 + newNumF2 , findLcm);
        return  Fraction::findReducedFrac(frc);
    }
    //This operator is for the operation "*" between 2 fractions.
    //In this function i got my idea while talking to a friend
    Fraction Fraction::operator*(const Fraction &frac){
        if (this->numerator == 0 || frac.numerator == 0) {//if one of the numerators is 0 so the fracrion will be 0 for sure.
            return Fraction(0,324);                    
        }
        if(frac.numerator == frac.denominator){ //if the second frac is one so return the first
            return Fraction::findReducedFrac(*this);
        }
        if(this->numerator == this->denominator){//if the first frac is one so return the second
            return Fraction::findReducedFrac(frac);
        }
        if (std::abs(frac.numerator) > MAX_INT / std::abs(this->numerator) ||
            std::abs(frac.denominator) > MAX_INT  / std::abs(this->denominator)) { //In this condition we are checking if the numerator and denomirator are bigger then max_int or smaller then min_int
            throw std::overflow_error("Fraction overflow");
        }
        Fraction frc(this->numerator*frac.numerator, this->denominator*frac.denominator);
        return  Fraction::findReducedFrac(frc);
    }
    //This operator is for the operation "/" between 2 fractions.
    Fraction Fraction::operator/(const Fraction &frac){
        if(frac.numerator == 0){
            throw std::runtime_error("Can't divide by 0");
        }
        Fraction frc(frac.denominator ,frac.numerator); // The only thing i am doing here is to flip the numerator and denominator of the second fraction and send it to the mul function.
        return (*this)*Fraction::findReducedFrac(frc);
    }
    /*
        The following functions are the operators between fraction and float numbers(using the flottofruction operators).
    */
    Fraction Fraction::operator*(float num){
        Fraction tmp = floatTofraction(num);
        return (*this)*tmp;
    }
    Fraction Fraction::operator+(float num){
        Fraction tmp = floatTofraction(num);
        return (*this)+tmp;
    }
    Fraction Fraction::operator-(float num){
        Fraction tmp = floatTofraction(num);
        return (*this)-tmp;
    }
    Fraction Fraction::operator/(float num){
        if(num == 0){
        //     throw std::invalid_argument("denominator can't be 0");
            throw runtime_error("denominator can't be 0");
        }
        Fraction tmp = floatTofraction(num);
        return (*this)/tmp;
    }

    //-----------------------------
    // Friend Comparison Operators
    //-----------------------------

    // This operator is to check if 2 fractions are different.
    bool operator!=(const Fraction &frac1, const Fraction &frac2){        
        Fraction frc1 =  Fraction::findReducedFrac(frac1);// checking reduced frac
        Fraction frc2 =  Fraction::findReducedFrac(frac2);// checking rducef frac
        return (frc1.getNumerator() != frc2.getNumerator() || frc1.getDenominator() != frc2.getDenominator()); // if 2 fracs are equal so the reduced frac is also equal.
    }
    // This operator is to check if fraction and float are different are different.
    bool operator!=(Fraction &frac1, float num){
        Fraction frac2 = Fraction::floatTofraction(num);
        return frac1 != frac2;
    }
    // This operator is to check if 2 fractions are equal.
    bool operator==(const Fraction &frac1, const Fraction &frac2){
        return !(frac1!=frac2);
    }
    //This operator is to check if a fraction and a float are equal.
    bool operator==(const Fraction &frac1, float num){
        Fraction frac2 =  Fraction::floatTofraction(num);
        return frac1 == frac2;
    }
    //This operator is to check if the first fraction is smaller then the second.
    bool operator<(const Fraction &frac1, const Fraction &frac2){
        bool posF1 = Fraction::checkFracPos(frac1);// check positivity of fraction1
        bool posF2 = Fraction::checkFracPos(frac2);// check positivity of fraction2
        int newFrac1;
        int newFrac2;
        if(posF1 && posF2){// if they are both positive so i am compering the 2 new numerators.
            newFrac1 = frac1.numerator * frac2.denominator;
            newFrac2 = frac2.numerator * frac1.denominator;
        }else if(posF1 && !posF2){ // if fraction 1 is positive and the second is negative return false
            return false;
        }else if(!posF1 && posF2){// if fraction 1 is negative and the second is positive return return true
            return true;
        }else{// if the both negative and the - is at the same level so there is no diffarence(arithmetic operation)
            if((frac1.denominator < 0 && frac2.denominator < 0) || (frac1.numerator < 0 && frac2.numerator < 0)){
                newFrac1 = frac1.numerator * frac2.denominator;
                newFrac2 = frac2.numerator * frac1.denominator;
            }else{// the new numerators will be negative fore sure so we will make them positive and will check the differnces.
                newFrac1 = frac1.numerator * frac2.denominator * (-1);
                newFrac2 = frac2.numerator * frac1.denominator * (-1);
            }
        }
        return newFrac1 < newFrac2;
    }
    //check if frraction smaller then num.
    bool operator<(const Fraction &frac1, float num){
        Fraction frac2 =  Fraction::floatTofraction(num);
        return frac1 < frac2;
    }
    //This operator is to check if the first fraction is bigger then the second.
    bool operator>(const Fraction &frac1, const Fraction &frac2){
        bool posF1 = Fraction::checkFracPos(frac1);// check positivity of fraction1
        bool posF2 = Fraction::checkFracPos(frac2);// check positivity of fraction1
        int newFrac1;
        int newFrac2;
        if(posF1 && posF2){// if they are both positive so i am compering the 2 new numerators.
            newFrac1 = frac1.numerator * frac2.denominator;
            newFrac2 = frac2.numerator * frac1.denominator;
        }else if(posF1 && !posF2){// if fraction 1 is positive and the second is negative return return true
            return true;
        }else if(!posF1 && posF2){// if fraction 1 is negative and the second is positive return false
            return false;
        }else{// if the both nrgative and the - is at the same level so there is no diffarence(arithmetic operation)
            if((frac1.denominator < 0 && frac2.denominator < 0) || (frac1.numerator < 0 && frac2.numerator < 0)){
                newFrac1 = frac1.numerator * frac2.denominator;
                newFrac2 = frac2.numerator * frac1.denominator;
            }else{// the new numerators will be negative fore sure so we will make them positive and will check the differnces.
                newFrac1 = frac1.numerator * frac2.denominator * (-1);
                newFrac2 = frac2.numerator * frac1.denominator * (-1);
            }
        }
        return newFrac1 > newFrac2;
    }
    //this fraction i am checking if ftaction bigger then a float number
    bool operator>(const Fraction &frac1, float num){
        Fraction frac2 =  Fraction::floatTofraction(num);
        return frac1 > frac2;
    }
    //in this function i am checking if fraction smaller or equal a fraction
    bool operator<=(const Fraction &frac1, const Fraction &frac2){
        return !(frac1>frac2);
    }
    //in this function i am checking if a fraction smaller or equal to a float number
    bool operator<=(const Fraction &frac1, float num){
        Fraction frac2 =  Fraction::floatTofraction(num);
        return frac1 <= frac2;
    }
    //in this function i am checking if fraction bigger or equal a fraction
    bool operator>=(const Fraction &frac1, const Fraction &frac2){
        return !(frac1<frac2);
    }
    //in this function i am checking if a fraction bigger or equal to a float number
    bool operator>=(const Fraction &frac1, float num){
         Fraction frac2 =  Fraction::floatTofraction(num);
        return frac1 >= frac2;
    }

    //-----------------------------
    // Increment Decrement Operators
    //-----------------------------

    //updating the new numerator(prefix)
    Fraction Fraction::operator--(){
        this->numerator -= this->denominator;
        return *this;
    }
    //updating the new numerator but returning the old values(postix)
    Fraction Fraction::operator--(int){
        Fraction tmp(this->numerator,this->denominator);
        this->numerator -= this->denominator;
        return tmp;    
    }
    //updating the new numerator(prefix)
    Fraction Fraction::operator++(){
        this->numerator += this->denominator;
        return *this;
    }
     //updating the new numerator but returning the old values(postix)
    Fraction Fraction::operator++(int){
        Fraction tmp(this->numerator,this->denominator);
        this->numerator += this->denominator;
        return tmp;
    }

    //-----------------------------
    // Friend Operators (on the othe side)
    //-----------------------------

    /*
    Arithmetic operators so we could make arithemetic operators from bothe sides.
    */
    Fraction operator*(float num, const Fraction &frac){
        return (Fraction::floatTofraction(num)*frac);
    }
    Fraction operator+(float num, const Fraction &frac){
        return (Fraction::floatTofraction(num)+frac);
    }
    Fraction operator-(float num, const Fraction &frac){
        return (Fraction::floatTofraction(num)-frac);
    }
    Fraction operator/(float num, const Fraction &frac){
        if(frac.denominator == 0){
        //     throw std::invalid_argument("denominator can't be 0");
            throw runtime_error("denominator can't be 0");
        }
        return (Fraction::floatTofraction(num)/frac);
    }

    //-----------------------------
    // I/O operations
    //-----------------------------
    
    //Output function, just implementing the string as we requierd in the tests and send it to the out.
    std::ostream& operator<<(std::ostream& out, const Fraction &frac){
        std::string ans;
        Fraction frc = Fraction::findReducedFrac(frac);//Make sure this is the smallest frac
        if(!(Fraction::checkFracPos(frc))){//Negative
            ans = "-"+to_string(int(std::abs(frc.numerator)))+"/"+to_string(int(std::abs(frc.denominator)));
        }else{
            ans = to_string(int(frc.numerator))+"/"+to_string(int(frc.denominator));
        }
        out << ans;
        return out;
    }
    // taking the values from istream to the numerator and denomirator and throwing exeptions as requierd.
    std::istream& operator>>(std::istream& inside, Fraction &frac){
        inside >> frac.numerator  >> frac.denominator;
        if (inside.fail()) {
            inside.clear();
            throw runtime_error("Input has fewer than 2 parameters");
        }
        
        if (frac.denominator == 0) {
            throw runtime_error("denominator can't be 0");
        }
        return inside;
    }
}