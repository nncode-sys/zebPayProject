/*
#include <ios>
#include <iostream>
#include <string>
#include <iomanip>
#include <curl/curl.h>
#include "Exchange.hpp"
#include "Aggregator.hpp"

int main(int argc, char* argv[]) {
//	 curl_global_init(CURL_GLOBAL_DEFAULT);
    
    double targetQty = 10.0; 
    
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--qty" && i + 1 < argc) {
            targetQty = std::stod(argv[i+1]);
        }
    }

    OrderBookAggregator aggregator;
    Coinbase cb;
    Gemini gem;

    aggregator.addExchange(&cb);
    aggregator.addExchange(&gem);

    aggregator.fetchData(targetQty);

    double buyCost = aggregator.calculateBuyCost(targetQty);
    double sellRevenue = aggregator.calculateSellRevenue(targetQty);
    std::cout<<std::fixed<<std::setprecision(2);
    std::cout << "To buy "<< targetQty << " BTC: $" << buyCost << std::endl;
    std::cout << "To sell " << targetQty << " BTC: $" << sellRevenue << std::endl;

//    curl_global_cleanup();

    return 0;
}
*/
