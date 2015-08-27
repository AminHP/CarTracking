#ifndef CAR_HPP
#define CAR_HPP

#include <deque>
#include "Point.hpp"
#include "Path.hpp"

class Car {
private:
	Path path;

//	friend std::ostream &operator <<(std::ostream&, const Car&);
//	friend std::istream &operator >>(std::istream&, Car&);

public:
	Car();
	Car(deque<Point>);
	Path &getPath() const;
	void log(int) const;
	bool isYInPath(float);
	float getXGivenY(float);
	float getSpeed(float) const;
//	void saveToFile(int) const;
//	bool loadFromFile(int);
};

#endif // CAR_HPP
