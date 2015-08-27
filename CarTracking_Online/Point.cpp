#include "Point.hpp"

Point::Point(const float xx, const float yy)
{
	x = xx;
	y = yy;
}

Point::Point()
{
	x = y = 0;
}

float pDistance(const Point p1, const Point p2)
{
	return sqrt(pow(fabs(p1.x - p2.x), 2) + pow(fabs(p1.y - p2.y), 2));
}

float pCrossProduct(const Point p1, const Point p2)
{
	return (p1.x * p2.y) - (p1.y * p2.x);
}

std::ostream &operator <<(std::ostream &ost, const Point &p)
{
	ost << p.x << " " << p.y;

	return ost;
}

std::istream &operator >>(std::istream &ist, Point &p)
{
	ist >> p.x >> p.y;

	return ist;
}

Point Point::operator -(const Point p) const
{
	return Point(x - p.x, y - p.y);
}
