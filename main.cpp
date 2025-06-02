#include <iostream>
#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "csvReader.h"

int main() 
{
    //Start program
    MerkelMain app{};
    app.init();
    // Wallet wallet{};
    // std::cout << "Inserting 10 BTC" << std::endl;
    // wallet.depositCurrency("BTC", 10);
    // std::cout << wallet.toString();
    // std::cout << "Withdrawing 4 BTC" << std::endl;
    // wallet.withdrawCurrency("BTC", 4);
    // std::cout << wallet.toString();
    // std::cout << "containsCurrency() test: contains 6 BTC: " << wallet.containsCurrency("BTC", 6);
    // std::cout << "containsCurrency() test: contains 10 BTC: " << wallet.containsCurrency("BTC", 10);
    // std::cout << "containsCurrency() test: contains 5 ETH: " << wallet.containsCurrency("ETH", 5);
    return 0;
}