#include "csvReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <iostream>
#include <string>
#include <vector>



const int ASCII_VALUE_OF_ZERO = 48;


/** Constructor for MerkelMain */
MerkelMain::MerkelMain()
{
    // Initialise isRunning to false for loops.
    isRunning = false;
}

/** MerkelMain::init initialises and runs the program */
void MerkelMain::init()
{
    // Load order book (testing function)
    // loadOrderBook();
    // Set start time
    currentTime = orderBook.getEarliestTime();

    // Initialise wallet
    wallet.depositCurrency("BTC", 10);
    wallet.depositCurrency("ETH", 50);
    wallet.depositCurrency("USDT", 100000);

    // Start program
    isRunning = true; 
    while (isRunning) 
    {
        int userOption;
        printMenu();
        userOption = getUserOption();
        processUserOption(userOption);    
    }
}

/** Prints menu */
void MerkelMain::printMenu() 
{
    // Print menu
    std::cout << "+==========================+" << std::endl;
    std::cout << " 1. Print help" << std::endl;
    std::cout << " 2. Print exchange stats" << std::endl;
    std::cout << " 3. Place an offer" << std::endl;
    std::cout << " 4. Place a bid" << std::endl;
    std::cout << " 5. Print wallet" << std::endl;
    std::cout << " 6. Continue" << std::endl;
    std::cout << " 7. Exit" << std::endl; 
    std::cout << "+=========================+" << std::endl;
    std::cout << "Current time: " << currentTime << std::endl;
    std::cout << "+=========================+" << std::endl;

}

/** Gets user option as an int */
int MerkelMain::getUserOption() 
{
    // Take input
    char userOption;
    std::cout << "Type in 1-7: " << std::endl;
    // .get is used to get character because otherwise could not
    // clear std::cin and infinite loop was triggered on bad input
    std::cin.get(userOption);
    // clear std::cin to prevent infinite loop on bad input
    std::cin.ignore();
    int parsedUserOption = (int)userOption - ASCII_VALUE_OF_ZERO;
    return parsedUserOption;
   
}

/** Processes user option and calls correct function */
void MerkelMain::processUserOption(int userOption) 
{
    switch (userOption) 
    {
        case 1:
            printHelp();
            break;
        case 2:
            printStats();
            break;
        case 3:
            placeAsk();
            break;
        case 4:
            placeBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNextTimeUnit();
            break;
        case 7:
            std::cout << "Exiting. Thank you for using Trading App." << std::endl;
            isRunning = false;
            break;            
        default:
            printError();
    }
    
}

/** Prints help */
void MerkelMain::printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

/** Prints stats */
void MerkelMain::printStats()
{
    for (const std::string& p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Product: " << p << std::endl;
        std::cout << "Asks seen: " << asks.size() << std::endl;
        std::cout << "Bids seen: " << bids.size() << std::endl;
        std::cout << "Asks depth: " << OrderBook::depth(asks) << std::endl;
        std::cout << "Bids depth: " << OrderBook::depth(bids) << std::endl;
        std::cout << "Max ask: " << OrderBook::maxPrice(asks) << std::endl;
        std::cout << "Min ask: " << OrderBook::minPrice(asks) << std::endl;
        std::cout << "Max bid: " << OrderBook::maxPrice(bids) << std::endl;
        std::cout << "Min bid: " << OrderBook::minPrice(bids) << std::endl;
        std::cout << "Bid/Ask Spread: " << OrderBook::priceSpread(asks, bids) << std::endl;
    }
}

/** Places offer to sell or ask */
void MerkelMain::placeAsk()
{
    std::cout << "Make an ask: product,price,amount, e.g.: ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = csvReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::placeAsk Bad input!" << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = csvReader::stringsToOBE(currentTime, tokens[0], "ask", tokens[1], tokens[2]);
            orderBook.insertOrder(obe);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
             
    }
    std::cout << "You typed: " << input << std::endl;  

}

/** Places bid to buy */
void MerkelMain::placeBid()
{
    std::cout << "Make an bid: product,price,amount, e.g.: ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = csvReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::placeBid Bad input!" << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = csvReader::stringsToOBE(currentTime, tokens[0], "bid", tokens[1], tokens[2]);
            orderBook.insertOrder(obe);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
             
    }
    std::cout << "You typed: " << input << std::endl;
    std::cout << "Bid made!" << std::endl;
}

/** Prints wallet */
void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

/** Goes to next time unit */
void MerkelMain::gotoNextTimeUnit()
{
    std::cout << "Time marches on!" << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "Matching: " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        }
}
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printError()
{
    std::cout << "Invalid command. Type 1-7." << std::endl;
}

