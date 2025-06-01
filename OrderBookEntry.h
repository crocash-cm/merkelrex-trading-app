#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H
// Above is include guard, another option is #pragma once
#include <string>

enum class OrderBookType{bid, ask};

class OrderBookEntry 
{
    public:
        // Constructor
        OrderBookEntry(std::string _timestamp, 
            std::string _product, 
            OrderBookType _type, 
            double _price, 
            double _amount);

        // Methods
        std::string obtToString();
        static OrderBookType stringToOBT(std::string s);
        /** Returns true if e1 timestamp smaller than e2 */
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

        // Fields
        std::string timestamp;
        std::string product;
        OrderBookType type;
        double price;
        double amount;
        
};
// Endif for include guards
#endif