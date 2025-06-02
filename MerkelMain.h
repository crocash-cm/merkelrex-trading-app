#ifndef MERKELMAIN_H
#define MERKELMAIN_H
// Above is include guard, another option is #pragma once
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <string>

const std::string DATABASE_FILENAME = "./loncppDB.csv";

class MerkelMain 
{
    public:
        // Constructor and initializer
        MerkelMain();
        /** Call this to start sim */
        void init();

    private:
        // Methods
        void loadOrderBook();
        void printMenu();
        int getUserOption();
        void processUserOption(int userOption);
        void printHelp();
        void printStats();
        void placeAsk();
        void placeBid();
        void printWallet();
        void gotoNextTimeUnit();
        void printError();

        // Fields
        bool isRunning;
        std::string currentTime;
        // Order book
        OrderBook orderBook{DATABASE_FILENAME};
        Wallet wallet{};
        
};
// Endif for include guard
#endif