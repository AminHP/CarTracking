#ifndef LINE_HPP
#define LINE_HPP

#include <deque>
#include "Path.hpp"
#include "Polygon.hpp"
#include "Car.hpp"

#include <iostream>
#include <fstream>

using namespace std;

class Line {
private:
	Path averagePath;
	Polygon confine;
	deque<Car> tmp_cars;
	bool empty_flag;

public:
	Line();
	Line(deque<Point>);
	bool isCarInPolygon(const Car) const;
	void push_car(const Car);
	void setAveragePath();
	float getDistance(const Car&) const;
	bool isEmpty() const;

	Polygon &getConfine() const;
	Path &getAveragePath() const;

	friend std::ostream &operator <<(std::ostream&, const Line&);
	friend std::istream &operator >>(std::istream&, Line&);
};

#endif // LINE_HPP
