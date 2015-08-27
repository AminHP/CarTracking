#include "MovementFunction.hpp"

MovementFunction::MovementFunction()
{
}

MovementFunction::MovementFunction(deque<Point> movementPoints)
{
	deque<float> x;
	deque<float> y;
	x.clear();
	y.clear();

	for (unsigned int i = 0; i < movementPoints.size(); i++)
	{
		x.push_back(movementPoints[i].x);
		y.push_back(movementPoints[i].y);
	}
	xy = shared_ptr<brANLine> (new brANLine(y, x));
}

float MovementFunction::getXGivenY(float y) const
{
	return xy->getYGivenX(y);
}
