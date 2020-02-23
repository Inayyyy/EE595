#ifndef KYP_H
#define KYP_H

#include "Profit.h"

class KYP {
private:
    Profit _kypProfit;
public:
    void setProfit(Profit);
    Profit getProfit() const;
};

#endif
