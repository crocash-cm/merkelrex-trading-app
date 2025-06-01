#include <stdexcept>
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(std::string _timestamp, std::string _product,  OrderBookType _type, double _price, double _amount)
: timestamp(_timestamp),
    product(_product),
    type(_type),
    price(_price),
    amount(_amount)
{
      
}

std::string OrderBookEntry::obtToString()
{
    OrderBookType t = this->type;
    switch (t)
    {
    case OrderBookType::ask:
        return "ask";
    case OrderBookType::bid:
        return "bid";
    default:
        throw std::invalid_argument("OrderBookEntry::obtToString invalid type.");
    }
}

 OrderBookType OrderBookEntry::stringToOBT(std::string s)
 {
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    else if (s == "bid")
    {
        return OrderBookType::bid;
    }
    else
    {
        throw std::invalid_argument("OrderBookEntry::stringToOBT invalid argument");
    }
 }

 bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
 {
    return (e1.timestamp < e2.timestamp);
 }
