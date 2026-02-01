/*
 * defines.cpp
 *
 *  Created on: 02-Feb-2026
 *      Author: Narendra Jatav
 */


#include "defines.hpp"
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


