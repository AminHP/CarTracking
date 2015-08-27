#ifndef PATH_HPP
#define PATH_HPP

#include <deque>
#include "MovementFunction.hpp"

class Path {
private:
	deque<Point> movementPoints;
	MovementFunction movementFunc;

	void setMovementFunction();

public:
	Path();
	Path(deque<Point>);
	float getXGivenY(float) const;

	deque<Point> &getMovementPoints() const;

	friend std::ostream &operator <<(std::ostream&, const Path&);
	friend std::istream &operator >>(std::istream&, Path&);
};

#endif // PATH_HPP
