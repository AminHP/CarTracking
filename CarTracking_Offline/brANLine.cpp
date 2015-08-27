#include "brANLine.hpp"

#include <iostream>

using namespace std;

brANLine::brANLine(float *x, float *y, int n)
{
	funcs.clear();
	for (int i = 0; i < n - 1; i++)
	{
		LinearFunction lf = LinearFunction(x[i], y[i], x[i + 1], y[i + 1]);
		funcs.push_back(lf);
	}
	lastX = x[n - 1];
	lastY = y[n - 1];
}

brANLine::brANLine(deque<float> x, deque<float> y)
{
	funcs.clear();
	for (unsigned int i = 0; i < x.size(); i++)
	{
		LinearFunction lf = LinearFunction(x[i], y[i], x[i + 1], y[i + 1]);
		funcs.push_back(lf);
	}
	lastX = x[x.size() - 1];
	lastY = y[y.size() - 1];
}

void brANLine::push_point(float x, float y)
{
	LinearFunction lf = LinearFunction(lastX, lastY, x, y);
	funcs.push_back(lf);
	lastX = x;
	lastY = y;
}

float brANLine::getYGivenX(float x) const
{
	for (unsigned int i = 0; i < funcs.size(); i++)
		if (funcs[i].isXInRange(x))
			return funcs[i].getYGivenX(x);
	return '-nan';
}
