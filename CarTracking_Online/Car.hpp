#ifndef CAR_HPP
#define CAR_HPP

#include <deque>
#include "Point.hpp"
#include "Band.hpp"

class Car {
private:
	bool first_time;
	unsigned int line;
	unsigned int line2;
	float fps;
	float current_speed;
	float min_speed;
	float max_speed;
	Point currentPoint;
	Point lastPoint;
	unsigned int noy; // number of yaw

public:
	Car();
	Car(const Point, const float);

	void setNOY_plusPlus();
	int getNOY() const;
	void setLines(const Band&);
	int getLine() const;
	int getLine2() const;
	void push_point(const Point);
	float getMinSpeed() const;
	float getMaxSpeed() const;
	void setSpeeds(const Band&);
	float getCurrentSpeed() const;
	Point getCurrentPoint() const;
	Point getLastPoint() const;
};

#endif // CAR_HPP
