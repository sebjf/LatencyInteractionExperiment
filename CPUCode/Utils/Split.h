/*
 * Split.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef SPLIT_H_
#define SPLIT_H_

#include <string>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

#endif /* SPLIT_H_ */
