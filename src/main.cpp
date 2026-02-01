/*
 * main1.cpp
 *
 *  Created on: 01-Feb-2026
 *      Author: Narendra Jatav
 */

#include <ios>
#include <iostream>
#include <string>
#include <iomanip>
#include <curl/curl.h>

#include "exchanges/Coinbase.cpp"
#include "exchanges/Gemini.cpp"
#include "Aggregator.hpp"
#include "core/Exchange.hpp"
class Coinbase;
class Gemini;


int main(int argc, char* argv[]) {
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

    return 0;
}



