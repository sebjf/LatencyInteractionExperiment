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

class PathFollower
{
public:
	PathFollower(Path& path);

	void Update(int x, int y);

	Vector GetBallLocation();
	bool IsComplete();

private:
	Path& m_path;
	uint m_s; //current abscissa

	uint m_tolerance; //in pixels

	Vector GetBallForwardVector();
	Polar GetCoordinateAroundBall(Vector Cursor, Vector Ball);
	float GetBallRadius();

	bool IsBehindBall(Vector cursor);
	bool IsWithinBall(Vector cursor);
};

#endif /* PATHFOLLOWER_H_ */
