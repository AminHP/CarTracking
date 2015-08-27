#ifndef MOVEMENT_FUNCTION_HPP
#define MOVEMENT_FUNCTION_HPP

#include <deque>
#include <tr1/memory>

#include "Point.hpp"
#include "brANLine.hpp"

using namespace std;
using namespace tr1;

class MovementFunction {
private:
	shared_ptr<brANLine> xy;

public:
	MovementFunction();
	MovementFunction(deque<Point>);
	float getXGivenY(float) const;
};

#endif // MOVEMENT_FUNCTION_HPP
