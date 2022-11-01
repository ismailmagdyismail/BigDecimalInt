
#ifndef MAIN_CPP_BIGDECIMAL_H
#define MAIN_CPP_BIGDECIMAL_H

//#include <bits/stdc++.h>
#include <iostream>
#include <deque>
using namespace std;


class BigDecimalInt {
    // cout operator overloading function
    friend ostream& operator<<(ostream& out,const BigDecimalInt& bigint);

public:

    // constructors
    BigDecimalInt(const string& num);
    BigDecimalInt(const long long int &num=0);
    BigDecimalInt(const BigDecimalInt& num);

    // getter functions
    int size()const;
    char getSign()const;

    // operator overloading functions
    BigDecimalInt& operator=(const BigDecimalInt& num);
    BigDecimalInt operator+(const BigDecimalInt& num)const;
    BigDecimalInt operator-(const BigDecimalInt& num)const;
    bool operator< (const BigDecimalInt& anotherDec)const;
    bool operator> (const BigDecimalInt& anotherDec)const;
    bool operator==(const BigDecimalInt& anotherDec)const;

private:
    deque<char> digits; // for storing digits from the string
    char sign;  // to store the sign

    void setSign(const char &sign);
    void validate(const string &num); // helper /utility function
    static void matchSize(BigDecimalInt& LHS,BigDecimalInt& RHS);// helper /utility function
};

#endif
