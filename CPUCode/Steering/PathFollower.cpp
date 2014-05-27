/*
 * PathFollower.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "PathFollower.h"

using namespace boost::numeric::ublas;

PathFollower::PathFollower(Path& path)
:m_path(path),
 m_s(0)
{

}

//http://users.ics.aalto.fi/pwagner/software/lifespace/refman_devel/lifespace-0.0.31/Vector_8hpp-source.html
template<class E>
void normalize( vector_expression<E> &vector )
{
	float_t len = norm_2(vector);
	vector() /= ((len > 0) ? len : (float_t)NAN);
}

Vector normalized(Vector vector )
{
	normalize( vector );
	return vector;
}

Polar PathFollower::GetCoordinateAroundBall(Vector C, Vector B)
{
	vector<float_t> up(2);
	up(0) = 0;
	up(1) = 1;

	vector<float_t> d = C - B;

	//check what side of the ball the cursor is on and add the angle offset if necessary

	float angle = acos(inner_prod(d, up));
	if(C(0) < B(0)){
		angle += 3.14;
	}

	float distance = norm_2(d);

	Polar p;
	p.a = angle;
	p.d = distance;
	return p;
}

Vector PathFollower::GetBallLocation()
{
	Vector v;
	PathSegment s = m_path.m_points[m_s];
	v(0) = s.x;
	v(1) = s.y;
	return v;
}

float PathFollower::GetBallRadius()
{
	return m_path.m_width;
}

bool PathFollower::IsComplete()
{
	return m_s >= m_path.m_points.size();
}

void PathFollower::Update(int x, int y)
{
	/* The path tracing works in the following way. The ball starts out at the beginning of a set of segments. The
	 * distance and angle of the cursor from the ball centre is computed. If it is within a certain range, the ball
	 * is moved to the next segment. If it is outside, nothing happens. */

	// if we have reached the end of the path, just exit

	if(IsComplete())
	{
		return;
	}

	// Get cursor distance and angle to ball center

	vector<float_t> C(2);
	C(0) = x;
	C(1) = y;

	do{
		Polar p = GetCoordinateAroundBall(C,GetBallLocation());

		// Check if cursor is pushing ball down path

		if(p.d < GetBallRadius())
		{
			m_s++; //if so move it on
		}
		else
		{
			break; //continue to move it on until its moved outside the cursor range
		}

	}while(true);

}
