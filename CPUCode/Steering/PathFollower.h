/*
 * PathFollower.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef PATHFOLLOWER_H_
#define PATHFOLLOWER_H_

#include "Path.h"
#include <vector>
#include <math.h>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::vector<float_t> Vector ;

struct Polar
{
	float d;
	float a;
};

class PathFollower
{
public:
	PathFollower(Path& path);

	void Update(int x, int y);

	Vector GetBallLocation();
	bool IsComplete();

private:
	Path& m_path;
	int m_s; //current abscissa

	Polar GetCoordinateAroundBall(Vector Cursor, Vector Ball);
	float GetBallRadius();
};

#endif /* PATHFOLLOWER_H_ */
