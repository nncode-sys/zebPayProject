/*
 * Coinbase.cpp
 *
 *  Created on: 01-Feb-2026
 *      Author: Narendra Jatav
 */


#include <iostream>
#include "../core/Exchange.hpp"
#include "../core/defines.hpp"

class Coinbase : public Exchange {
public:
    Coinbase() : Exchange("Coinbase", "https://api.exchange.coinbase.com/products/BTC-USD/book?level=2") {}

    void fetchOrderBook(std::vector<Order>& bids, std::vector<Order>& asks, double qty) override {
        std::string response = httpGet();
        if (response.empty()) return;

        try {
            auto j = json::parse(response);
            double targetQty = qty;
            for (const auto& item : j["bids"]) {
                double quantity = std::stod(item[1].get<std::string>());
                targetQty -= quantity;
                bids.push_back({std::stod(item[0].get<std::string>()), quantity, name});
                if(targetQty < 0)
                    break;
            }
            targetQty = qty;
            for (const auto& item : j["asks"]) {
                double quantity = std::stod(item[1].get<std::string>());
                targetQty -= quantity;
                asks.push_back({std::stod(item[0].get<std::string>()), quantity, name});
                if(targetQty < 0)
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing Coinbase data: " << e.what() << std::endl;
        }
    }
};


