//
//  Globals.h
//  MortgageApp

#ifndef __MortgageApp__Globals__
#define __MortgageApp__Globals__

#include <iostream>

const int GmonthsInYear = 12;
const int GpercentDenominator = 100;

struct GamortizeMonth
{
    int year;
    int yearMonth;
    long loanMonth;
    double payment;
    double pureInterest;
    double paidDownPrincipal;
    double principalBalance;

};

// new variable type with seven element
// define own variable types 




#endif /* defined(__MortgageApp__Globals__) */
