#pragma once
#include "core/Exchange.hpp"
#include <algorithm>
#include <iostream>

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

        std::sort(all_bids.begin(), all_bids.end(),
            [](const Order& a, const Order& b) {
                return a.price > b.price;
            });

        std::sort(all_asks.begin(), all_asks.end(),
            [](const Order& a, const Order& b) {
                return a.price < b.price;
            });
    }

    // ---------------- BUY SIDE ----------------

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
            std::cerr << "Warning: Not enough liquidity to buy "
                      << targetQty << std::endl;
        }

        return totalCost;
    }

    double calculateAverageBuyCost(double targetQty) {
        double totalCost = 0.0;
        double filledQty = 0.0;

        for (const auto& order : all_asks) {
            if (filledQty >= targetQty) break;

            double takeQty = std::min(order.quantity, targetQty - filledQty);
            totalCost += takeQty * order.price;
            filledQty += takeQty;
        }

        if (filledQty == 0.0) {
            std::cerr << "Error: No liquidity on buy side\n";
            return 0.0;
        }

        if (filledQty < targetQty) {
            std::cerr << "Warning: Partial fill on buy side ("
                      << filledQty << "/" << targetQty << ")\n";
        }

        return totalCost / filledQty;
    }

    // ---------------- SELL SIDE ----------------

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
            std::cerr << "Warning: Not enough liquidity to sell "
                      << targetQty << std::endl;
        }

        return totalRevenue;
    }

    double calculateAverageSellPrice(double targetQty) {
        double totalRevenue = 0.0;
        double filledQty = 0.0;

        for (const auto& order : all_bids) {
            if (filledQty >= targetQty) break;

            double takeQty = std::min(order.quantity, targetQty - filledQty);
            totalRevenue += takeQty * order.price;
            filledQty += takeQty;
        }

        if (filledQty == 0.0) {
            std::cerr << "Error: No liquidity on sell side\n";
            return 0.0;
        }

        if (filledQty < targetQty) {
            std::cerr << "Warning: Partial fill on sell side ("
                      << filledQty << "/" << targetQty << ")\n";
        }

        return totalRevenue / filledQty;
    }
};
