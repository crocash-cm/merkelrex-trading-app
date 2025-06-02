#include "OrderBook.h"
#include "OrderBookEntry.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

/** Constructor, take filename and load csv into order book */
OrderBook::OrderBook(std::string filename)
{
    orders = csvReader::read(filename);
}

/** return vector of all known products in dataset */
std::vector<std::string> OrderBook::getKnownProducts()
{
    // Inserts to set (duplicates rejected)
    std::set<std::string> prodSet;
    std::vector<std::string> products;
    for (const OrderBookEntry& e : orders)
    {
        prodSet.insert(e.product);
    }
    // Copy set to vector for return
    for (const std::string p : prodSet)
    {
        products.push_back(p);
    }
    return products;
}

/** return vector of orders according to filters (parameters) */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                    std::string product,
                                    std::string timestamp)
{
    std::vector<OrderBookEntry> ordersReturn;
    for (const OrderBookEntry& e : orders)
    {
        if (e.type == type 
            && e.product == product 
            && e.timestamp == timestamp)
        {
            ordersReturn.push_back(e);
        }
    }
    
    return ordersReturn;

}

/** Gets earliest time */
std::string OrderBook::getEarliestTime()
{
    std::string earliestTime = orders[0].timestamp;
    for (const OrderBookEntry& e : orders)
    {
        if (earliestTime > e.timestamp)
        {
            earliestTime = e.timestamp;
        }
    }
    return earliestTime;
}

/** Given timestamp, goes to next timestamp */
std::string OrderBook::getNextTime(const std::string& timestamp)
{
    std::string next_timestamp = "";
    for (const OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = getEarliestTime();
    }
    
    return next_timestamp;
}

/** Inserts order into orderbook */
void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids)
        {
            if (bid.price >= ask.price)
            {
                // Default type, because we do not care about the wallet in case of dataset (non-user)
                OrderBookEntry sale{timestamp, product, OrderBookType::asksale, ask.price, 0};
                if (bid.username == "simuser")
                {
                    sale.type = OrderBookType::bidsale;
                    sale.username = "simuser";
                    
                }
                if (ask.username == "simuser")
                {
                    sale.type = OrderBookType::asksale;
                    sale.username = "simuser";
                }
                
                if (bid.amount == ask.amount) 
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                else if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                else if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }

            }
        }
    }
    return sales;
}

////////////////////////////////////////////////////////////////////////////////////
// STATISTICS FUNCTIONS                                                          //
//////////////////////////////////////////////////////////////////////////////////

/** Returns lowest price amongst argument orders */
double OrderBook::minPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}

/** Returns highest price in orders */
double OrderBook::maxPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

/** Finds the average price of orders */
double OrderBook::averagePrice(std::vector<OrderBookEntry>& orders)
{
    double sum = 0.0;
    for (const OrderBookEntry& e : orders)
    {
        sum = sum + e.price;
    }
    return sum / orders.size();
}

/** Return spread between bids and asks, returns max(bids) - min(asks) */
double OrderBook::priceSpread(std::vector<OrderBookEntry>& asks,
                                        std::vector<OrderBookEntry>& bids)
{
    double maxBid = maxPrice(bids);
    double minAsk = minPrice(asks);
    return maxBid - minAsk;
}

/** Returns the depth or total amount being offered or bid upon in orders */
double OrderBook::depth(std::vector<OrderBookEntry>& orders)
{
    double depth = 0.0;
    for (const OrderBookEntry& e : orders)
    {
        depth = depth + e.amount;
    }
    return depth;
}

///////////////////////////////////////////////////////////////////////////


    ////// Official instructor's solution 
    ////// to getKnownProducts is below:
    // // Maps prod strings to bools in a paid
    // // Bool true if product appeares in orders
    // // Further appearances retain true
    // // Effect is to create unique set of products
    // // Paired with the bool "true"
    // std::map<std::string, bool> prodMap;
    // for (const OrderBookEntry& e : orders)
    // {
    //     prodMap[e.product] = true;
    // }

    // // Iterate over the prodMap extracting the string section
    // // The products themselves
    // std::vector<std::string> products;
    // for (const std::pair<std::string,bool> & prodStringBoolPair : prodMap)
    // {
    //     products.push_back(prodStringBoolPair.first);
    // }

    // return products;