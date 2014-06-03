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
 m_s(0),
 m_tolerance(2)
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

	float distance = norm_2(d);

	//check what side of the ball the cursor is on and add the angle offset if necessary

	d = normalized(d);
	float angle = acos(inner_prod(d, up));
	if(C(0) < B(0)){
		angle += 3.14;
	}

	Polar p;
	p.a = angle;
	p.d = distance;
	return p;
}

Vector PathFollower::GetBallForwardVector()
{
	int i1 = m_s;
	int i2 = m_s + 1;

	if(i2 == m_path.m_points.size())
	{
		i1--;
		i2--;
	}

	Vector v1 = m_path.m_points[i1].ToVector();
	Vector v2 = m_path.m_points[i2].ToVector();

	return normalized(v2 - v1);
}

Vector PathFollower::GetBallLocation()
{
	return m_path.m_points[m_s].ToVector();
}

float PathFollower::GetBallRadius()
{
	return m_path.m_width;
}

bool PathFollower::IsComplete()
{
	return m_s >= m_path.m_points.size();
}

bool PathFollower::IsBehindBall(Vector cursor)
{
	Vector ball = GetBallLocation();
	Vector cb = cursor - ball;
	Vector forward = GetBallForwardVector();
	float angle = acos(inner_prod(cb, forward));
	if(angle > 3.14 / 2)
	{
		return true;
	}

	return false;
}

bool PathFollower::IsWithinBall(Vector cursor)
{
	Vector ball = GetBallLocation();
	Vector cb = ball - cursor;
	float distance = norm_2(cb);
	if(distance < (GetBallRadius() + m_tolerance))
	{
		return true;
	}

	return false;

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
		bool moveon = IsBehindBall(C) & IsWithinBall(C);
		if(moveon)
		{
			m_s++; //if so move it on
		}
		else
		{
			break; //continue to move it on until its moved outside the cursor range
		}

	}while(true);

}
