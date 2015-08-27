#include "Line.hpp"

Line::Line()
{
}

Line::Line(deque<Point> v)
{
	confine = Polygon(v);
}

bool Line::isEmpty() const
{
	return empty_flag;
}

Polygon &Line::getConfine() const
{
	return (Polygon&) confine;
}

Path &Line::getAveragePath() const
{
	return (Path&) averagePath;
}

void Line::setMinSpeed(const float ms)
{
	minSpeed = ms;
}

void Line::setMaxSpeed(const float ms)
{
	maxSpeed = ms;
}

float Line::getMinSpeed() const
{
	return minSpeed;
}

float Line::getMaxSpeed() const
{
	return maxSpeed;
}

std::ostream &operator <<(std::ostream &ost, const Line& l)
{
	ost << l.empty_flag << endl;
	if (!l.isEmpty())
		ost << l.averagePath << endl;
	ost << l.confine;

	return ost;
}

std::istream &operator >>(std::istream &ist, Line& l)
{
	ist >> l.empty_flag;
	if (!l.isEmpty())
		ist >> l.averagePath;
	ist >> l.confine;

	return ist;
}
