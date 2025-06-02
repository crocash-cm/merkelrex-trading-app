 #include <string>
 #include <map>
 #include "Wallet.h"
 
 Wallet::Wallet()
 {

 }

 void Wallet::depositCurrency(std::string type, double amount)
 {

 }

 /** Check whether wallet contains enough of currency */
bool Wallet::containsCurrency(std::string type, double amount)
{
    return false;
}

/** Generate string representation of the wallet */
std::string Wallet::toString()
{
    return "test";
}
