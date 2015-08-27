#ifndef LINEAR_FUNCTION_HPP
#define LINEAR_FUNCTION_HPP

class LinearFunction {
private:
	float m;
	float b;
	float minD;
	float maxD;

public:
	LinearFunction(float, float, float, float);

	bool isXInRange(float) const;
	float getYGivenX(float) const;
};

#endif // LINEAR_FUNCTION_HPP
