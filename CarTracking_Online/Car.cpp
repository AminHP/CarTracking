#include "Car.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

Car::Car()
{
}

Car::Car(const Point p, const float fps) : fps(fps)
{
	noy = 0;
	first_time = 1;
	max_speed = -999999999.0f;
	min_speed = 999999999.0f;
	currentPoint = p;
	lastPoint    = p;
}

void Car::setNOY_plusPlus()
{
	noy ++;
}

int Car::getNOY() const
{
	return noy;
}

void Car::setLines(const Band &b)
{
	float min = 999999999.0f;
	for (unsigned int i = 0; i < b.getLines().size(); i++)
		if (fabs(b.getLines()[i].getAveragePath().getXGivenY(currentPoint.y) - currentPoint.x) < min)
		{
			min = fabs(b.getLines()[i].getAveragePath().getXGivenY(currentPoint.y) - currentPoint.x);
			line = i;
		}

	min = 999999999.0f;
	for (unsigned int i = 0; i < b.getLines().size(); i++)
		if (i != line)
			if (fabs(b.getLines()[i].getAveragePath().getXGivenY(currentPoint.y) - currentPoint.x) < min)
			{
				min = fabs(b.getLines()[i].getAveragePath().getXGivenY(currentPoint.y) - currentPoint.x);
				line2 = i;
			}
}

int Car::getLine() const
{
	return line;
}

int Car::getLine2() const
{
	return line2;
}

void Car::push_point(const Point p)
{
	lastPoint = currentPoint;
	currentPoint = p;
}

void Car::setSpeeds(const Band &b)
{
	float sym = (currentPoint.y > lastPoint.y) ? -1.0f : +1.0f;
	float d = pDistance(currentPoint, lastPoint);
	current_speed = (((((d / b.getConfine().getPixelsPerMeter(currentPoint.y)) +
			(d / b.getConfine().getPixelsPerMeter(lastPoint.y))) / 2) * fps) * sym) * 3.6f; // set to Km/h

	if (!first_time)
	{
		if (current_speed > max_speed)
			max_speed = current_speed;
		if (current_speed < min_speed)
			min_speed = current_speed;
	}
	else
		first_time = 0;
}

float Car::getCurrentSpeed() const
{
	return current_speed; 
}

float Car::getMinSpeed() const
{
	return min_speed;
}

float Car::getMaxSpeed() const
{
	return max_speed;
}

Point Car::getCurrentPoint() const
{
	return currentPoint;
}

Point Car::getLastPoint() const
{
	return lastPoint;
}
