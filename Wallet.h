#include <string>
#include <map>

class Wallet
{
    public:
        /** Constructor */
        Wallet();

        // Methods
        /** Deposits currency into wallet */
        void depositCurrency(std::string type, double amount);
        /** Check whether wallet contains enough of currency */
        bool containsCurrency(std::string type, double amount);
        /** Generate string representation of the wallet */
        std::string toString();

        // Fields
    private:
        std::map<std::string,double> currencies;

};