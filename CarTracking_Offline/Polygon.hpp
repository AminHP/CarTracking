#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <deque>
#include "Point.hpp"

#include <iostream>
#include <fstream>

using namespace std;

class Polygon {
private:
	deque<Point> vertexes;

	bool getCrossProductSym(const Point, const Point) const;

public:
	Polygon();
	Polygon(const deque<Point>);

	bool isPointInPolygon(const Point) const;

	deque<Point> getVertexes() const;
	//deque<Point> getOutside() const;

	friend std::ostream &operator <<(std::ostream&, const Polygon &);
	friend std::istream &operator >>(std::istream&, Polygon &);
};

#endif // POLYGON_HPP
