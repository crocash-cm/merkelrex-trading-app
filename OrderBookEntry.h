#pragma once

#include <string>

enum class OrderBookType{bid, ask, bidsale, asksale};

class OrderBookEntry 
{
    public:
        // Constructor
        OrderBookEntry(std::string _timestamp, 
            std::string _product, 
            OrderBookType _type, 
            double _price, 
            double _amount,
            std::string _username = "dataset");

        // Methods
        static std::string obtToString(OrderBookType type);
        static OrderBookType stringToOBT(std::string s);
        /** Returns true if e1 timestamp smaller than e2 */
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

        // Fields
        std::string timestamp;
        std::string product;
        OrderBookType type;
        double price;
        double amount;
        std::string username;
        
};

