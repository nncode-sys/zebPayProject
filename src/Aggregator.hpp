
#pragma once
#include "core/Exchange.hpp"

class OrderBookAggregator {
private:
    std::vector<Exchange*> exchanges;
    std::vector<Order> all_bids;
    std::vector<Order> all_asks;

public:
    void addExchange(Exchange* ex) {
        exchanges.push_back(ex);
    }

    void fetchData(double targetQty) {
        all_bids.clear();
        all_asks.clear();

        for (auto ex : exchanges) {
            ex->fetchOrderBook(all_bids, all_asks, targetQty);
        }

        std::sort(all_bids.begin(), all_bids.end(), [](const Order& a, const Order& b) {
            return a.price > b.price;
        });

        std::sort(all_asks.begin(), all_asks.end(), [](const Order& a, const Order& b) {
            return a.price < b.price;
        });
    }

    // Calculate cost to BUY (Walking down Asks)
    double calculateBuyCost(double targetQty) {
        double totalCost = 0.0;
        double remainingQty = targetQty;

        for (const auto& order : all_asks) {
            if (remainingQty <= 0) break;

            double takeQty = std::min(remainingQty, order.quantity);
            totalCost += takeQty * order.price;
            remainingQty -= takeQty;
        }

        if (remainingQty > 0) {
            std::cerr << "Warning: Not enough liquidity to buy " << targetQty << " BTC." << std::endl;
        }
        return totalCost;
    }

    // Calculate revenue to SELL (Walking up Bids)
    double calculateSellRevenue(double targetQty) {
        double totalRevenue = 0.0;
        double remainingQty = targetQty;

        for (const auto& order : all_bids) {
            if (remainingQty <= 0) break;

            double takeQty = std::min(remainingQty, order.quantity);
            totalRevenue += takeQty * order.price;
            remainingQty -= takeQty;
        }

        if (remainingQty > 0) {
            std::cerr << "Warning: Not enough liquidity to sell " << targetQty << " BTC." << std::endl;
        }
        return totalRevenue;
    }
};
