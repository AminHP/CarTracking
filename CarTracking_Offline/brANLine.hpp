#ifndef BRANLINE_HPP
#define BRANLINE_HPP

#include <deque>
#include "LinearFunction.hpp"

using namespace std;

class brANLine {
private:
	deque<LinearFunction> funcs;
	float lastX;
	float lastY;

public:
	brANLine(float*, float*, int);
	brANLine(deque<float>, deque<float>);

	void push_point(float, float);
	float getYGivenX(float) const;
};

#endif // BRANLINE_HPP
