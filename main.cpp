/*
Names : Ahmed mohamed taha, adham tarek, ismail magdy
ID   : 20210033 - 20210051 - 20210069
task : group task 1 - assignment 1
last date modified : 10/20/2022
Description :Testing BigDecimalInt class 
*/

#include <bits/stdc++.h>
#include "BigDecimalInt.h"
using namespace std;

int main(){
    start:

    // inputs window
    system("CLS");
    cout << "please enter the first number : ";
    string s1;   cin >> s1;
    BigDecimalInt num1(s1);

    cout << "please enter the second number : ";
    string s2;  cin >> s2;
    BigDecimalInt num2(s2);


    // calculations' window
    system("CLS");
    cout << "num 1 : " << num1 << "\n";
    cout << "num 2 : " << num2 << "\n";

    BigDecimalInt num3 = num1 + num2;
    cout << "num 1 + num 2 = " << num3 << '\n';

    BigDecimalInt num4 = num1 - num2;
    cout << "num1 - num 2 = " << num4 << '\n';

    if(num1 == num2)
        cout << "num1 = num2\n";
    else if(num1 > num2)
        cout << "num1 > num2\n";
    else
        cout << "num 1 < num2\n";
    
    // repeat window
    choose:
    cout << "do you want to exit ? (y/n) : ";
    char c;     cin >> c;

    if(c == 'y')
        exit(0);
    else if(c == 'n')
        goto start;
    else{
        cout << "invalid input please try again!\n";
        goto choose;
    }
}
