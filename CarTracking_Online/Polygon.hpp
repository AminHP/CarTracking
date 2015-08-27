#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <deque>
#include "Point.hpp"
#include "LinearFunction.hpp"

#include <iostream>
#include <fstream>

using namespace std;

class Polygon {
private:
	deque<Point> vertexes;	

	LinearFunction lFunc;
	LinearFunction rFunc;

	int nol; // number of lines
	float lines_width;

	bool getCrossProductSym(const Point, const Point) const;

public:
	Polygon();
	Polygon(const deque<Point>);

	bool isPointInPolygon(const Point) const;

	void setLinearFuncs();
	LinearFunction &getLFunc() const;
	LinearFunction &getRFunc() const;

	float getLines_pixel_width(const float) const;
	float getPixelsPerMeter(const float) const;

	void setNOL(const int);
	void setLines_width(const float);

	deque<Point> getVertexes() const;
	//deque<Point> getOutside() const;

	friend std::ostream &operator <<(std::ostream&, const Polygon &);
	friend std::istream &operator >>(std::istream&, Polygon &);
};

#endif // POLYGON_HPP
