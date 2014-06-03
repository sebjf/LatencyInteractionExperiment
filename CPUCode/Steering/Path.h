/*
 * Path.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::vector<float_t> Vector ;

struct Polar
{
	float d;
	float a;
};

struct PathSegment
{
	int x;
	int y;
	float forward; //angle in radians from 0 to 2*pi

	Vector ToVector()
	{
		Vector v;
		v(0) = x;
		v(1) = y;
		return v;
	}
};

class Path
{
public:
	std::vector<PathSegment> m_points;
	int m_width;
};

#endif /* PATH_H_ */
