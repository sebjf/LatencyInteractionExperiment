/*
 * Path.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>

struct PathSegment
{
	int x;
	int y;
	float forward; //angle in radians from 0 to 2*pi
};

class Path
{
public:
	std::vector<PathSegment> m_points;
	int m_width;
};

#endif /* PATH_H_ */
