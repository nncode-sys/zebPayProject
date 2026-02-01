/*
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<curl/curl.h>
#include "RateLimiter.hpp"
#include "json.hpp"
using json = nlohmann::json;


struct Order {
    double price;
    double quantity;
    std::string exchange;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



class Exchange {
protected:
    std::string name;
    std::string url;
    RateLimiter limiter;

public:
    Exchange(std::string n, std::string u) : name(n), url(u), limiter(2000) {} 

    virtual ~Exchange() {}

    std::string getName() const { return name; }

    virtual void fetchOrderBook(std::vector<Order>& bids, std::vector<Order>& asks, double qty) = 0;

protected:
    std::string httpGet() {
        if (!limiter.canRequest()) {
            std::cerr << "[Warning] Rate limit hit for " << name << ". Skipping request." << std::endl;
            return "";
        }

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "CryptoAggregator/1.0");
            
            curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/curl-certs/cacert.pem");

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }
};

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
*/
