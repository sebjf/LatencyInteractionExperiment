/*
 * FittsLawTestConditions.h
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#ifndef FITTSLAWTESTCONDITIONS_H_
#define FITTSLAWTESTCONDITIONS_H_

#include <vector>
#include <string>
#include <stdlib.h>

class Rectangle
{
public:
	int center_x;
	int center_y;
	int width;
	int height;

	bool isCursorInRect(int x, int y)
	{
		return ((abs(center_x - x) <= (width/2))
				&&
				(abs(center_y - y) <= (height/2)));
	}

	friend std::ostream& operator<< (std::ostream& stream, const Rectangle& rect);

};


class FittsLawTestCondition
{
public:
	std::string m_filename;
	int m_condition_id;

	Rectangle staging_area;
	Rectangle target;
	int latency_in_ms;

	FittsLawTestCondition()
	{
		staging_area.center_x = 100;
		staging_area.center_y = 100;
		staging_area.width = 50;
		staging_area.height = 50;
		target.center_x = 500;
		target.center_y = 100;
		target.width = 25;
		target.height = 25;
		latency_in_ms = 0;
	}

	FittsLawTestCondition(int x, int y, int width, int height)
	{
		staging_area.center_x = 100;
		staging_area.center_y = 100;
		staging_area.width = 50;
		staging_area.height = 50;
		target.center_x = x;
		target.center_y = y;
		target.width = width;
		target.height = height;
		latency_in_ms = 0;
	}

	friend std::ostream& operator<< (std::ostream& stream, const FittsLawTestCondition& condition);

};

class FittsLawTestConditions : std::vector<FittsLawTestCondition*>
{
};

class FittsLawTestConditionLoader
{
public:
	std::vector<FittsLawTestCondition*> LoadHardcoded();
	std::vector<FittsLawTestCondition*>* LoadCSV(std::string filename);

};

#endif /* FITTSLAWTESTCONDITIONS_H_ */
