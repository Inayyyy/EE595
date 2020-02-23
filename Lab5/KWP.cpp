#include "KWP.h"
#include <iostream>

KWP::KWP(Profit* first_three_week, int z) {
    for(int i = 0; i < sizeof(_kwProfit)/sizeof(Profit); i++) {
        _kwProfit[i] = *first_three_week;
        first_three_week++;
    }
    _z = z;
    _numObjects++;
    output.open("output.txt", std::ios::app);
    if (output.is_open()) {
        output << "This is the (" << _numObjects << ")th object.\n";
        output.close();
    } else {
        std::cout << "Unable to open file.\n";
    }
}

KWP::~KWP() {
    output.open("output.txt", std::ios::app);
    if (output.is_open()) {
        output << "Call destructor here." << std::endl;
        output.close();
    } else {
        std::cout << "Unable to open file.\n";
    }
}

int KWP::_numObjects = 0;

void KWP::printKWP() const {
    std::cout << "/******Print KWP*******/\n";
    for(int i = 0; i < sizeof(_kwProfit)/sizeof(Profit); i++) {
        std::cout << _kwProfit[i].duration << " " << _kwProfit[i].dollar << std::endl;
    }
    std::cout << _z << std::endl;
    std::cout << _numObjects << std::endl;
}

unsigned long int KWP::getNumOfCases(char option) {
    if(option == 'I') {
        unsigned long int i = getNumOfCasesI(_z);
        //std::cout << "Cases = " << i << std::endl;
        return i;
    } else {
        unsigned long int i = getNumOfCasesR(_z);
        //std::cout << "Cases = " << i << std::endl;
        return i;
    }
    
}

unsigned long int KWP::getNumOfCasesR(int n) {
    //std::cout << "R" << std::endl;
    // base case
    if (n == 0 || n == 1 || n == 2) return n;
    else if (n == 3) return 4;
    
    // recursive rule
    return getNumOfCasesR(n-1) + getNumOfCasesR(n-2) + getNumOfCasesR(n-3);
} 

unsigned long int KWP::getNumOfCasesI(int n) {
    //std::cout << "I" << std::endl;
    unsigned long int arr[n+1];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 4;
    for(int i = 4; i <= n; i++) {
        arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
    }
    //std::cout << "Cases = " << arr[n] << std::endl;
    return arr[n];
}

Profit KWP::getProfit() const {
    return _profit_z;
}

long double KWP::calAvgProfit(char option) {
    if(option == 'I') return calAvgProfitI(_z);
    else return calAvgProfitR(_z) / getNumOfCasesR(_z);
}

long double KWP::calAvgProfitI(int n) {
    //std::cout << "I" << std::endl;
    long double arr[n+1];
    arr[0] = 0;
    arr[1] = _kwProfit[0].dollar;
    arr[2] = _kwProfit[0].dollar*2 + _kwProfit[1].dollar;
    arr[3] = 3*_kwProfit[0].dollar + 2*(_kwProfit[1].dollar + _kwProfit[0].dollar) 
                + _kwProfit[2].dollar;

    for(int i = 4; i <= n; i++) {
        arr[i] = arr[i-1] + _kwProfit[0].dollar + 
                    arr[i-2] + _kwProfit[1].dollar + 
                    arr[i-3] + _kwProfit[2].dollar; 
    }
    /*
    for(int i = 0; i < n+1; i++) {
        std::cout << arr[i] << std::endl;
    }*/
    return arr[n] / getNumOfCasesI(n);
}

long double KWP::calAvgProfitR(int n) {
    //std::cout << "R" << std::endl;
    if (n == 0) return 0;
    else if (n == 1) return _kwProfit[0].dollar;
    else if (n == 2) return _kwProfit[0].dollar*2 + _kwProfit[1].dollar;
    else if (n == 3) return 3*_kwProfit[0].dollar + 
                            2*(_kwProfit[1].dollar + _kwProfit[0].dollar) + _kwProfit[2].dollar;
    
    return calAvgProfitR(n-1) + _kwProfit[0].dollar + 
                   calAvgProfitR(n-2) + _kwProfit[1].dollar + 
                   calAvgProfitR(n-3) + _kwProfit[2].dollar; 

}

void KWP::setProfit(Profit a) {
    _profit_z = a;
}

















