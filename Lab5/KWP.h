#ifndef KWP_H
#define KWP_H

#include "Profit.h"
#include <fstream>

class KWP {
private:
    Profit _kwProfit[3];
    static int _numObjects;
    int _z; //number of weeks
    Profit _profit_z;
    std::ofstream output;
    unsigned long int getNumOfCasesI(int);
    unsigned long int getNumOfCasesR(int);
    long double calAvgProfitI(int);
    long double calAvgProfitR(int);
public:
    KWP(Profit*, int); // initialize _kwProfit, _z
    ~KWP();
    void setProfit(Profit); // already know the avg profit for z number of weeks
    Profit getProfit() const; // get avg profit for z number of weeks
    void printKWP() const;
    unsigned long int getNumOfCases(char); 
    long double calAvgProfit(char);
};

#endif
