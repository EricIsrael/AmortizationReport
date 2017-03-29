//  main.cpp
//  MortgageApp
//  Created by Eric Israel on 8/6/16.

#include <iostream>
#include "Divisor.h"
#include "Multplier.h"
#include "cmath"
#include "iomanip"
#include "Globals.h"


using namespace std;

enum AmortizeProgram
{
    LOAN_PRINCIPAL = 1,
    INTEREST_RATE = 2,
    YEARS_OF_LOAN = 3
    
};

enum AmortEnum
{
    YR_OUT = 2,
    MN_OUT = 2,
    CUM_MN_OUT = 5,
    PAYMENT_OUT = 12,
    INTEREST_OUT = 12,
    PRINCIPAL_OUT = 12,
    BALANCE_OUT = 16
    
    };

string AmortHeader[]
{
    "Yr",
    "Mn",
    "CumMn",
    "Payment",
    "Interest",
    "Principal",
    "Balance"
    
};

void printAmortHeader()
{

cout <<
    endl <<
    setw (YR_OUT) << AmortHeader[0] << " " <<
    setw (MN_OUT) << AmortHeader[1] << " " <<
    setw (CUM_MN_OUT) << AmortHeader[2] << " " <<
    setw (PAYMENT_OUT) << AmortHeader[3] << " " <<
    setw (INTEREST_OUT) << AmortHeader[4] << " " <<
    setw (PRINCIPAL_OUT) << AmortHeader[5] << " " <<
    setw (BALANCE_OUT) << AmortHeader[6] <<
    endl <<
    endl;
}


int main(int argc, char* argv[])
{
    double Principal = 0.0;
    double HumanInterest = 0.0;
    int YearsofLoan = 0.0;
    
// == means is argc equal to 1?... argc = 1 sets it to 1
    
    
    if (argc == 1)
    
    {
        cout << "Enter the Principal Amount: ";
        cin >> Principal;
    
        cout << "Enter Interest Rate:";
        cin >> HumanInterest;
    
        cout << "Enter the years of loan:";
        cin >> YearsofLoan;
    
    } else {
        
        Principal = atof(argv[LOAN_PRINCIPAL]);
        
        //NOTE* argv[1] does not work b/c string
        
        HumanInterest = atof(argv[INTEREST_RATE]);
        YearsofLoan = atoi(argv[YEARS_OF_LOAN]);
    }
    
    cout << "Loan Principal: " << Principal << endl;
    cout << "Interest Rate: " << HumanInterest << "%" << endl;
    cout << "Time Period " << YearsofLoan << "year(s)" << endl;
    
    double interest = divisor(HumanInterest,GpercentDenominator);
    
    double MonthInterest = divisor (interest, GmonthsInYear);
    long monthsOfLoan = multiplier(YearsofLoan, GmonthsInYear);

    double payment = 0.0;
    
    payment  = Principal * (MonthInterest/
                            (1 - (pow ((double) 1 + MonthInterest,
                            (double) - monthsOfLoan))));
    
    cout << "Payment: " << setiosflags(ios::fixed) <<
        setprecision(2) << payment << endl;
    
    
    double CurrentInterestPayment = 0.0;
    double CurrentPrincipalPayment = 0.0;
    double CurrentBalance = 0.0;
    
    CurrentBalance = Principal;

// while loop ... start at month of loan 1 -360 then principal decreases to 0
    

    long CurrentLoanMonth = 1;
    
    int year = 1;
    int switchYear = 0;
    int yearMonth = 1;
    
    
    
    while(CurrentLoanMonth <= monthsOfLoan) {
        
        if (switchYear != year) {
            
            switchYear = year;
            
            printAmortHeader();
        }
        
        GamortizeMonth amortMonth;
        
        CurrentInterestPayment = CurrentBalance * MonthInterest;
        CurrentPrincipalPayment = payment - CurrentInterestPayment;
        CurrentBalance = abs(CurrentBalance - CurrentPrincipalPayment);
        
        
        amortMonth.year = year;
        amortMonth.yearMonth = yearMonth;
        amortMonth.loanMonth = CurrentLoanMonth;
        amortMonth.payment = payment;
        amortMonth.pureInterest = CurrentInterestPayment;
        amortMonth.paidDownPrincipal = CurrentPrincipalPayment;
        amortMonth.principalBalance = CurrentBalance ;
        
        
    cout <<
         setw (YR_OUT) << amortMonth.year << " " <<
         setw (MN_OUT) << amortMonth.yearMonth << " " <<
         setw (CUM_MN_OUT) << amortMonth.loanMonth << " " <<
         setw (PAYMENT_OUT) << amortMonth.payment << " " <<
         setw (INTEREST_OUT) << amortMonth.pureInterest << " " <<
         setw (PRINCIPAL_OUT) << amortMonth.paidDownPrincipal << " " <<
         setw (BALANCE_OUT) << amortMonth.principalBalance <<
         endl;
        
        yearMonth++;
        
        if (yearMonth > GmonthsInYear)
        {
            yearMonth = 1;
            year++;
        }
    
        
        CurrentLoanMonth++;
    }

    cout <<
        endl <<
        "Loan Payments Complete." <<
        endl <<
        endl;
    
    return 0;
}

