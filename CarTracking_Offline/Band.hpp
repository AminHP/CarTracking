#ifndef BAND_HPP
#define BAND_HPP

#include <deque>
#include "Line.hpp"
#include "Polygon.hpp"
#include "Car.hpp"

using namespace std;

class Band {
private:
	deque<Line>lines;
	Polygon confine;

	void saveToFile();
	int getCarLine(const Car&) const;

public:
	Band();
	Band(int, Polygon, deque<Car>);

	bool loadFromFile();
	float getMaxDistanceFromLine(const Car&) const;
	deque<Line> &getLines() const;
};

#endif // BAND_HPP
