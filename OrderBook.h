#pragma once

#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "csvReader.h"

class OrderBook
{
    public:
        /** Constructor, take filename and load csv into order book */
        OrderBook(std::string filename);
        
        /** return vector of all known products in dataset */
        std::vector<std::string> getKnownProducts();
        /** return vector of orders according to filters (parameters) */
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                            std::string product,
                                            std::string timestamp);
        
        /** Gets earliest time from data set */
        std::string getEarliestTime();

        /** Returns next time, loops to beginning if no time found */
        std::string getNextTime(const std::string& timestamp);

        /** Inserts order */
        void insertOrder(OrderBookEntry& order);

        /** Matches bids, takes product, timestamp returns OrderBookEntry Vector */
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
        

        static double maxPrice(std::vector<OrderBookEntry>& orders);
        static double minPrice(std::vector<OrderBookEntry>& orders);
        static double averagePrice(std::vector<OrderBookEntry>& orders);
        static double priceSpread(std::vector<OrderBookEntry>& asks, std::vector<OrderBookEntry>& bids);
        static double depth(std::vector<OrderBookEntry>& orders);

        // Fields
        std::vector<OrderBookEntry> orders;

};