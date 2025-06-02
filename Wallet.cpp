 #include <string>
 #include <map>
 #include <vector>
 #include "csvReader.h"
 #include "Wallet.h"
 
 Wallet::Wallet()
 {

 }

 void Wallet::depositCurrency(std::string type, double amount)
 {
    if (amount > 0)
    {
        currencies[type] += amount;
    }    
 }

 bool Wallet::withdrawCurrency(std::string type, double amount)
 {
    if (amount < 0)
    {
        return false;
    }
    if (currencies[type] >= amount)
    {
        currencies[type] -= amount;
        return true;
    }
    return false;
 }

 /** Check whether wallet contains enough of currency */
bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0)
    {
        return false;
    }
    if (currencies[type] >= amount)
    {
        return true;
    }
    return false;
}

/** Checks whether wallet has enough to fulfill order (ask or bid) */
bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = csvReader::tokenise(order.product, '/');
    //std::string type = OrderBookEntry::obtToString(order.type);
    double amount = 0.0;
    if (order.type == OrderBookType::ask)
    {
        amount = order.amount;
        std::string currency = currs[0];
        return containsCurrency(currency, amount);
    }
    if (order.type == OrderBookType::bid)
    {
        amount = order.amount * order.price;
        std::string currency = currs[1];
        return containsCurrency(currency, amount);

    }
    return false;
}

/** Generate string representation of the wallet */
std::string Wallet::toString()
{
    std::string walletString = "";
    for (auto const& [currency, amount] : currencies)
    {
        walletString = walletString + currency + ": " + std::to_string(amount) + "\n";
    }
    return walletString;
}
