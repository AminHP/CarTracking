#ifndef LINEAR_FUNCTION_HPP
#define LINEAR_FUNCTION_HPP

class LinearFunction {
private:
	float m;
	float b;
	float minD;
	float maxD;

public:
	LinearFunction();
	LinearFunction(const float, const float, const float, const float);

	bool isXInRange(const float) const;
	float getYGivenX(const float) const;
};

#endif // LINEAR_FUNCTION_HPP
