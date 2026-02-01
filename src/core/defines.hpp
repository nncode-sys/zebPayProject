/*
 * Order.hpp
 *
 *  Created on: 01-Feb-2026
 *      Author: Narendra Jatav
 */

#ifndef CORE_DEFINES_HPP_
#define CORE_DEFINES_HPP_

#pragma once
#include <string>

struct Order {
    double price;
    double quantity;
    std::string exchange;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);





#endif /* CORE_DEFINES_HPP_ */
