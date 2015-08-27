#ifndef BAND_HPP
#define BAND_HPP

#include <deque>
#include "Line.hpp"
#include "Polygon.hpp"

using namespace std;

class Band {
private:
	deque<Line>lines;
	float lines_width; // meter
	Polygon confine;

public:
	Band();

	bool loadFromFile();
	float getLines_width() const;
	deque<Line> &getLines() const;
	Polygon &getConfine() const;
};

#endif // BAND_HPP
