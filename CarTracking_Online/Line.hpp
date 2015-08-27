#ifndef LINE_HPP
#define LINE_HPP

#include <deque>
#include "Path.hpp"
#include "Polygon.hpp"

#include <iostream>
#include <fstream>

using namespace std;

class Line {
private:
	Path averagePath;
	Polygon confine;
	bool empty_flag;

	float minSpeed; // Km/h
	float maxSpeed; // Km/h

public:
	Line();
	Line(deque<Point>);

	bool isEmpty() const;
	Polygon &getConfine() const;
	Path &getAveragePath() const;

	void setMinSpeed(const float);
	void setMaxSpeed(const float);

	float getMinSpeed() const;
	float getMaxSpeed() const;

	friend std::ostream &operator <<(std::ostream&, const Line&);
	friend std::istream &operator >>(std::istream&, Line&);
};

#endif // LINE_HPP
