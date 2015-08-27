#include "LinearFunction.hpp"

LinearFunction::LinearFunction(float x1, float y1, float x2, float y2)
{
	m = (y2 - y1) / (x2 - x1);
	b = y1 - (m * x1);
	minD = (x1 < x2) ? x1 : x2;
	maxD = (x2 > x1) ? x2 : x1;
}

bool LinearFunction::isXInRange(float x) const
{
	if (x >= minD && x <= maxD)
		return 1;
	return 0;
}

float LinearFunction::getYGivenX(float x) const
{
	return (m * x) + b;
}
