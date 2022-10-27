#include <bits/stdc++.h>
#include "BigDecimalInt.h"
using namespace std;


// ******************************** String Constructor ****************************
BigDecimalInt::BigDecimalInt(const string& num) {
    // validating (leading zeros ,sign ,etc....)
    validate(num);
}


// ***************************** Copy Constructor ***************************************
BigDecimalInt::BigDecimalInt(const BigDecimalInt &other) {

    // extracting  digits
    string num ;
    for (int i = 0; i <other.getSize(); ++i) {
        num+=other.digits[i];
    }

    // validating (leading zeros ,sign ,etc....)
    validate(num);
    setSign(other.getSign());
}


// ******************************** Int Constructor ****************************
BigDecimalInt::BigDecimalInt(const int & num) {
    int temp=num;
    if(num==0) {
        digits.push_back('0');
        setSign('+');
    }
    else if(num<0) {
        setSign('-');
        temp*=-1;
    }
    else
        setSign('+');
    while(temp) {
        int digit=temp%10;
        temp/=10;
        digits.push_front(digit + '0');
    }
}


// ******************************* Assign "=" Operator Function *****************************
BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &num) {
    this->digits.clear(); // clear the object
    this->setSign(num.getSign()); // copy the sign
    // copy the digits
    for (char i : num.digits) {
        digits.push_back(i);
    }
    return *this;
}


// ******************************* Size Getter Function *****************************
int BigDecimalInt::getSize() const {
    // return deque's size
    return  digits.size();
}


// ******************************* Sign Getter Function *****************************
char BigDecimalInt::getSign() const {
    return  sign;
}


// ******************************** Sign Setter Function ****************************
void BigDecimalInt::setSign(const char& sign) {
    if(!isdigit(sign)) {
        this->sign = sign;
    }
    else
        this->sign = '+';
}



// ******************************** Addition "+" Function ****************************
BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num)const {
    // if they not have the same signs change the operate to subtract
    // (1 + -2) == (1 - 2)
    if(this->getSign() != num.getSign()){
        BigDecimalInt temp(num);
        temp.setSign(this-> getSign());
        return *this-temp;
    }

    BigDecimalInt result;
    result.digits.clear();
    result.setSign(this->getSign());

    BigDecimalInt lhs = *this;
    BigDecimalInt rhs = num;

    // equate the sizes of the two numbers by leading zeros to the small number
    int diff = abs(lhs.getSize()-rhs.getSize());
    for (int i = 0; i <diff; ++i) {
        if(rhs.getSize()<lhs.getSize())
            rhs.digits.push_front('0');
        else
            lhs.digits.push_front('0');
    }

    int end = lhs.getSize()-1;
    int carry = 0 ;

    while (end>=0) {
        int d1 =  lhs.digits[end] - '0';
        int d2 =  rhs.digits[end] - '0';
        int sum = d1+d2+carry;
        // if the sum of two digits will make overflow("greater than 9") we add carry to the next digit's sum
        if(sum>9) {
            carry = 1;
            // take the last digit to add it to the object
            sum%=10;
        }
        else
            carry = 0;
        // push the sum to to object
        result.digits.push_front(sum + '0');
        end--;
    }
    if(carry)
        result.digits.push_front(carry + '0');
    return  result;
}



// ***************************** Subtraction "-" Function *******************************
BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &num)const{
    /* call add operator if they have non equal signs and set thier add sign to the first number
       (-3 - 2) = -(3 + 2) || (3 - -6) = (3 + 6)
    */
    if(this->getSign() != num.getSign()) {
        BigDecimalInt temp(num);
        temp.setSign(this-> getSign());
        return *this+temp;
    }

    BigDecimalInt result,bigger,smaller,lhs,rhs;
    result.digits.clear();

    // assign the left hand side
    lhs = *this;
    char lhsSign = lhs.getSign(); // save old sign
    lhs.setSign('+'); // get abs value

    // assign the right hand side
    rhs = num;
    if(rhs.getSign()=='+') // flip sign (1 - +6) == (1 - 6)
        rhs.setSign('-');
    else
        rhs.setSign('+'); // (1 - -6) == (1 + 6)

    char rhsSign = rhs.getSign(); // save old sign
    rhs.setSign('+'); // get abs value

    if(lhs > rhs) { // assign the bigger and the smaller value and the result's sign
        result.setSign(lhsSign);
        bigger = lhs;
        smaller = rhs;
    }
    else if(rhs > lhs) { // assign the bigger and the smaller value and the result's sign
        result.setSign(rhsSign);
        bigger = rhs;
        smaller = lhs;
    }
    else { // if they are equal return 0 (50 - 50) = 0
        result.setSign('+');
        return BigDecimalInt("0");
    }

    // equate the sizes of the two numbers with leading zeros in the front
    int diff = abs(bigger.getSize()-smaller.getSize());
    for (int i = 0; i < diff; ++i) {
        if(smaller.getSize() < bigger.getSize())
            smaller.digits.push_front('0');
        else
            bigger.digits.push_front('0');
    }

    // subtraction

    for (int i =  bigger.getSize()-1 ; i >= 0; i--) {
        // if the bigger's number digit less than the smaller's number digit borrow from it's left neighbor one
        if(bigger.digits[i] < smaller.digits[i]) {
            bigger.digits[i-1]--;
            bigger.digits[i] += 10;
        }
        // subtract them and store the result in the object
        result.digits.push_front('0' + bigger.digits[i] - smaller.digits[i]);
    }
    return result;
}



// ******************************* Less Than "<" Check Function *****************************
bool BigDecimalInt::operator< (const BigDecimalInt& anotherDec)const{
    // if the first number have a negative sign and the second number have positive sign function will return true
    if(this->getSign()=='-'&&anotherDec.getSign()=='+')
        return true;
    // if the first number have a positive sign and the second number have negative sign function will return false
    if(this->getSign()=='+'&&anotherDec.getSign()=='-')
        return false;

    /* if they both have negative signs we will take thier abs and compare them with less than operate
       (-2 < -3) ? --> (2 > 3) ? "no" // (-5 < -3) ? --> (5 > 3) ? "yes"
    */
    if(this->getSign()=='-' && anotherDec.getSign()=='-') {
        BigDecimalInt LHS = *this;
        LHS.setSign('+');
        BigDecimalInt RHS = anotherDec;
        RHS.setSign('+');
        return (LHS>RHS);
    }
    // if the first number has fewer digits than the second number that's mean it smaller than the second number it will be true
    if(this->getSize() < anotherDec.getSize())
        return true;
    if(this->getSize() > anotherDec.getSize()) // ^^ vice versa ^^
        return false;
    // if they are equal in digits number we will compare each digit from the left to the right
    for(long long i = 0; i < anotherDec.getSize(); i++){
        // if the second number's digit greater than the first number's digit return true
        if(anotherDec.digits[i] > this->digits[i])
            return true;
        else if(anotherDec.digits[i] < this->digits[i]) // ^^ vice versa return false ^^
            return false;
    }
    return false;
}


// ****************************** Greater Than ">" Check Function ******************************
bool BigDecimalInt::operator> (const BigDecimalInt& anotherDec)const{
    // if the first number have a negative sign and the second number have positive sign function will return false
    if(this->getSign()=='-' && anotherDec.getSign()=='+')
        return false;
    // if the first number have a positive sign and the second number have negative sign function will return true
    if(this->getSign()=='+' && anotherDec.getSign()=='-')
        return true;

    /* if they both have negative signs we will take thier abs and compare them with less than operate
       (-2 > -3) ? --> (2 < 3) ? "yes" // (-5 > -3) ? --> (5 < 3) ? "no"
    */
    if(this->getSign()=='-' && anotherDec.getSign()=='-') {
        BigDecimalInt LHS = *this;
        LHS.setSign('+');
        BigDecimalInt RHS = anotherDec;
        RHS.setSign('+');
        return (LHS<RHS);
    }
    // if the first number has fewer digits than the second number that's mean it smaller than the second number it will be false
    if(this->getSize() < anotherDec.getSize())
        return false;
    if(this->getSize() > anotherDec.getSize()) // ^^ vice versa ^^
        return true;
    // if they are equal in digits number we will compare each digit from the left to the right
    for(long long i = 0; i < anotherDec.getSize(); i++){
        // if the second number's digit greater than the first number's digit return false
        if(anotherDec.digits[i] > this->digits[i])
            return false;
        else if(anotherDec.digits[i] < this->digits[i]) // vice versa return true
            return true;
    }
    // if they are equal
    return false;
}


// ****************************** Equality "==" Check Functions******************************
bool BigDecimalInt::operator==(const BigDecimalInt& anotherDec) const {
    // if the first not greater than the second and not less than the second that means that the two numbers are equal
    return (!(*this < anotherDec) && !(*this > anotherDec));
}


// ****************************** Output Operator "<<" Overloading Function ******************************
ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    // if the object negative from check it's sign output the sign first
    if(bigint.getSign()=='-')
        out << '-';
    // then output the digits
    for (char i : bigint.digits) {
        out << i ;
    }
    return out;
}


// ****************************** Validating number **************************************************
void BigDecimalInt::validate(const string &num){
    bool valid = true;
    bool leadingZero = true;
    // check if sign exist only once or not and check if the string contain numbers only using regex
    if (! regex_match(num, regex("(\\+|-)?\\d+") ) )
        valid = false;
        // push back the numbers into the object and skip zeros in the left
    else {
        if(isdigit(num[0]) && num[0] != '0') {
            digits.push_back(num[0]);
            leadingZero = false;
        }
        for (int i = 1; i <num.size() ; ++i) {
            if(num[i] == '0' && leadingZero)
                continue;
            leadingZero = false;
            digits.push_back(num[i]);
        }
    }
    // if the string not valid set the object with deafult value zero
    if(!valid || leadingZero) {
        digits.push_back('0');
        setSign('+');
    }
        // set number's sign if valid using setSign function
    else
        setSign(num[0]);
}

// ********************************************************************************************
