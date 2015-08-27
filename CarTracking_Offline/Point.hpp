#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

#include <iostream>
#include <fstream>

using namespace std;

struct Point {
	float x;
	float y;

	Point(const float, const float);
	Point();

	friend std::ostream &operator <<(std::ostream&, const Point&);
	friend std::istream &operator >>(std::istream&, Point&);

	Point operator -(const Point) const;
	void operator =(const Point);
};


float pDistance(const Point p1, const Point p2);
float pCrossProduct(const Point p1, const Point p2);

#endif // POINT_HPP
