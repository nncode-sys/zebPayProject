/*
 * Exchange.cpp
 *
 *  Created on: 01-Feb-2026
 *      Author: Narendra Jatav
 */



#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<curl/curl.h>

#include "defines.hpp"
#include "RateLimiter.hpp"
#include "json.hpp"
using json = nlohmann::json;




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


