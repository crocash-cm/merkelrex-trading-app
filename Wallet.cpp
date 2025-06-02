 #include <string>
 #include <map>
 #include "Wallet.h"
 
 Wallet::Wallet()
 {

 }

 void Wallet::depositCurrency(std::string type, double amount)
 {
    currencies[type] += amount;
 }

 /** Check whether wallet contains enough of currency */
bool Wallet::containsCurrency(std::string type, double amount)
{
    return (currencies[type] >= amount);
}

/** Generate string representation of the wallet */
std::string Wallet::toString()
{
    std::string walletString = "";
    for (auto const& [currency, amount] : currencies)
    {
        walletString = walletString + currency + ": " + std::to_string(amount) + " ";
    }
    return walletString;
}
