#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
    public:
        /** Constructor */
        Wallet();

        // Methods
        /** Deposits currency into wallet */
        void depositCurrency(std::string type, double amount);
        /** Withdraws currency into wallet */
        bool withdrawCurrency(std::string type, double amount);
        /** Check whether wallet contains enough of currency */
        bool containsCurrency(std::string type, double amount);
        bool canFulfillOrder(OrderBookEntry order);
        /** Generate string representation of the wallet */
        std::string toString();

        // Fields
    private:
        std::map<std::string,double> currencies;

};