#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "OrderBookEntry.h"

class csvReader 
{
    public:
        // Constructor
        csvReader();
        // Methods
        static std::vector<OrderBookEntry> read(std::string csvFile);
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::string timestamp, 
                                            std::string product, 
                                            std::string type, 
                                            std::string price, 
                                            std::string amount);

    private:
        


};