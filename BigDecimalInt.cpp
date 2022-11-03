#include "BigReal.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <regex>
using namespace std;



//***********************************************************************************************************
BigReal::BigReal (const string &realNumber){
    setWhole(realNumber);
    setFraction(realNumber);
}

//***********************************************************************************************************
BigReal::BigReal(const double& realNumber){
    string number = to_string(realNumber);
    *this = BigReal(number);       //////////////////////////////// KOSMEK
}

//***********************************************************************************************************
BigReal::BigReal (const BigDecimalInt& bigInteger){
    this->whole = bigInteger;
    this->fraction = "0";
}


//***********************************************************************************************************
BigReal::BigReal (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
}


//***********************************************************************************************************
BigReal& BigReal::operator = (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
    return *this;
}


//***********************************************************************************************************
int BigReal::size()const{
    return fraction.size() + whole.size();  /////// KOSMEK anty kaman
}

//***********************************************************************************************************
char BigReal::sign()const{
    return whole.getSign();
}

//***********************************************************************************************************
bool BigReal::operator==(const BigReal& anotherReal)const {
    string leftFraction = this->fraction;
    string rightFraction= anotherReal.fraction;
    matchFractionSize(leftFraction, rightFraction); // 13.3500
    return ((this->whole==anotherReal.whole)&&(leftFraction==rightFraction));
}


//***********************************************************************************************************
BigReal BigReal::operator+(const BigReal& other)const{

    if(this->sign() != other.sign()){
        BigReal temp(other);
        temp.whole.setSign(this->sign());
        return *this-temp;
    }

    // fraction part addition
    string LHS = this->fraction;
    string RHS = other.fraction;

    matchFractionSize(LHS,RHS);

    string fractionResult;
    fractionResult.resize(LHS.size());
    int fractionCarry = 0 ;

    for (int i = LHS.size() - 1; i >= 0 ; --i) {
        int lhsDigit = LHS[i] - '0';
        int rhsDigit = RHS[i] - '0';
        int sum = lhsDigit + rhsDigit + fractionCarry;

        // if the sum of two digits will make overflow("greater than 9") we add fractionCarry to the next digit's sum
        if(sum>9) {
            fractionCarry = 1;
            sum%=10;
        }
        else{
            fractionCarry = 0;
        }
        fractionResult[i] = sum+'0';
    }
    // whole part addition
    BigDecimalInt wholeResult  = this->whole + other.whole;

    wholeResult = wholeResult+fractionCarry;

    BigReal result;
    result.whole = wholeResult;
    result.fraction = fractionResult;
    return result;
}


//***********************************************************************************************************
BigReal BigReal::operator-(const BigReal& other) const {
    if(this->sign() != other.sign()) {
        BigReal temp(other);
        temp.whole.setSign(this->sign());
        return *this+temp;
    }

    BigReal result ;

    BigReal bigger =  max(*this,other);
    BigReal smaller = min(*this,other);

    string biggerFraction = bigger.fraction;
    string smallerFraction = smaller.fraction;

    if(smallerFraction>biggerFraction){
        bigger = bigger - 1;
        biggerFraction[0]+=10;
    }
    matchFractionSize(biggerFraction,smallerFraction);

    result.fraction.resize(biggerFraction.size());

    for (int i = biggerFraction.size() - 1 ; i >= 0; i--) {
        if(biggerFraction[i] < smallerFraction[i]) {
            biggerFraction[i-1]--;
            biggerFraction[i] += 10;
        }
        result.fraction[i] = biggerFraction[i]-smallerFraction[i];
    }
    result.whole = bigger.whole-smaller.whole;

    return result;
}

//***********************************************************************************************************
bool BigReal::operator<(const BigReal& anotherReal)const{
    if(this->whole==anotherReal.whole){
        return (this->fraction<anotherReal.fraction);
    }
    else
        return (this->whole<anotherReal.whole);
}


//***********************************************************************************************************
bool BigReal::operator>(const BigReal &anotherReal) const {
    if(this->whole==anotherReal.whole){
        return (this->fraction>anotherReal.fraction);
    }
    else
        return (this->whole>anotherReal.whole);
}


//***********************************************************************************************************
ostream& operator << ( ostream& out,const BigReal& num){
    out<<num.whole<<"." << num.fraction;
    return  out;
}


//***********************************************************************************************************
istream& operator >> (istream& in,BigReal& num){
    string str;
    in >> str;
    num = BigReal(str);
    return in;
}


//***********************************************************************************************************
void BigReal::setFraction(const string &number){
    int pointIdx = -1;
    string fractionPart;
    for (int i = 0; i <number.size(); ++i) {
        if (number[i] == '.' && pointIdx == -1){
            pointIdx = i;
        }
        else if (pointIdx != -1){  // found the decimal point
            fractionPart+=number[i];
        }
    }

    if(pointIdx==-1 || fractionPart.empty() || !regex_match(fractionPart, regex("\\d+") ) ){
        this->fraction ="0";
        return;
    }

    // remove trailing zeros
    for (int i = fractionPart.size()-1; i>=0 ; --i){
        if(fractionPart[i]!='0'){
            break;
        }
        fractionPart.erase(i,1);
    }

    if(fractionPart.empty())
        this->fraction = "0";
    else
        this->fraction = fractionPart;
}

//***********************************************************************************************************
void BigReal::setWhole(const string &number) {
    string wholePart ;
    for (const char& i : number) {
        if(i=='.')
            break;
        wholePart+=i;
    }
    this->whole = BigDecimalInt(wholePart);
}



//***********************************************************************************************************
void BigReal::matchFractionSize(string &LHS, string &RHS){
    long long diff = abs((long long)LHS.size()-(long long)RHS.size());
    for(long long i = 0; i < diff; i++){
        // add trailing zeros to the shorter number to facilitate operations
        if(RHS.size() > LHS.size()){
            LHS.push_back('0');
        }
        else{
            RHS.push_back('0');
        }
    }
}



//***********************************************************************************************************
