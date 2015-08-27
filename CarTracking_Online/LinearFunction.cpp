#include "LinearFunction.hpp"

LinearFunction::LinearFunction()
{
}

LinearFunction::LinearFunction(const float x1, const float y1, const float x2, const float y2)
{
	m = (y2 - y1) / (x2 - x1);
	b = y1 - (m * x1);
	minD = (x1 < x2) ? x1 : x2;
	maxD = (x2 > x1) ? x2 : x1;
}

bool LinearFunction::isXInRange(const float x) const
{
	if (x >= minD && x <= maxD)
		return 1;
	return 0;
}

float LinearFunction::getYGivenX(const float x) const
{
	return (m * x) + b;
}
