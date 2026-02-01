/*
 * Gemini.cpp
 *
 *  Created on: 01-Feb-2026
 *      Author: Narendra Jatav
 */


#include <iostream>
#include "../core/Exchange.hpp"
#include "../core/defines.hpp"


class Gemini : public Exchange {
public:
    Gemini() : Exchange("Gemini", "https://api.gemini.com/v1/book/BTCUSD") {}

    void fetchOrderBook(std::vector<Order>& bids, std::vector<Order>& asks, double qty) override {
        std::string response = httpGet();
        if (response.empty()) return;

        try {
            auto j = json::parse(response);
            double targetQty = qty;
            for (const auto& item : j["bids"]) {
                double quantity = std::stod(item["amount"].get<std::string>());
                targetQty -= quantity;
                bids.push_back({std::stod(item["price"].get<std::string>()), quantity, name});
                if(targetQty < 0)
                    break;
            }
            targetQty = qty;
            for (const auto& item : j["asks"]) {
                double quantity = std::stod(item["amount"].get<std::string>());
                targetQty -= quantity;
                asks.push_back({std::stod(item["price"].get<std::string>()), std::stod(item["amount"].get<std::string>()), name});
                if(targetQty < 0)
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing Gemini data: " << e.what() << std::endl;
        }
    }
};
