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

	Vector2 GetBallLocation();
	bool IsComplete();

private:
	Path& m_path;
	uint m_s; //current abscissa

	uint m_tolerance; //in pixels

	Vector2 GetBallForwardVector();
	Polar GetCoordinateAroundBall(Vector2 Cursor, Vector2 Ball);
	float GetBallRadius();

	bool IsBehindBall(Vector2 cursor);
	bool IsWithinBall(Vector2 cursor);
};

#endif /* PATHFOLLOWER_H_ */
