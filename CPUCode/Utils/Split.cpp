/*
 * Split.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "Split.h"
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
