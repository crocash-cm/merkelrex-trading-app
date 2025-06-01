#include "csvReader.h"
#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

const int EXPECTED_NUMBER_OF_TOKENS = 5;

csvReader::csvReader() 
{

}

std::vector<OrderBookEntry> csvReader::read(std::string filename)
{
    double price;
    double amount;
    OrderBookType obt;
    std::vector<OrderBookEntry> orderBook;
    std::vector<std::string> tokens;
    std::string line;
    std::ifstream csvFile{filename};
    if (!csvFile.is_open())
    {
        throw std::runtime_error("csvReader::read File reading error. File not found or cannot be read.");
    }
    while (std::getline(csvFile, line))
    {
        tokens = tokenise(line, ',');
        if (tokens.size() != EXPECTED_NUMBER_OF_TOKENS)
        {
            std::cout << "csvReader::read Line read error: token number does not match expected output." << std::endl;
            continue;
        }
        try
        {
            obt = OrderBookEntry::stringToOBT(tokens[2]);
            price = std::stod(tokens[3]);
            amount = std::stod(tokens[4]);
        }
        catch (const std::exception& e)
        {
            std::cout << "csvReader::read Bad data encountered, skipping." << std::endl;
            continue;
        }
        OrderBookEntry obe{tokens[0], tokens[1], obt, price, amount};
        orderBook.push_back(obe);
    }
    
    return orderBook;
}

std::vector<std::string> csvReader::tokenise(std::string csvLine, char separator)
{   
    std::vector<std::string> tokens;
    signed int start = csvLine.find_first_not_of(separator);
    signed int end;
    std::string token;

    do
    {
        // end = next 'separator' after start
        end = csvLine.find(separator, start);
        // if start == csvLine.length or start == end -> nothing more to find
        if (start == csvLine.length() || start == end)
        {   
            // break
            break;
        }
        //  we found the separator
        if (end >= 0) 
        {
            //  start, substring length
            token = csvLine.substr(start, end - start);
        }
        else
        {
            //  end is invalid
            token = csvLine.substr(start, csvLine.length() - start);
        }
        // add token to the end of the tokens vector
        tokens.push_back(token);
        
        // move past this token
        start = end + 1;
        
    } while (end != std::string::npos);
    
    return tokens;
}

OrderBookEntry csvReader::stringsToOBE(std::string timestamp, std::string product, std::string type, std::string price, std::string amount)
{

    double parsedPrice;
    double parsedAmount;
    OrderBookType parsedType;
    try
    {
        parsedPrice = std::stod(price);
        parsedAmount = std::stod(amount);
        parsedType = OrderBookEntry::stringToOBT(type);
    }
    catch (const std::exception& e)
    {
        std::cout << "csvReader::stringsToOBE bad float" << std::endl;
        throw;
    }
    OrderBookEntry obe{timestamp, product, parsedType, parsedPrice, parsedAmount};
    return obe;
}