#include "Path.hpp"

Path::Path()
{
}

Path::Path(deque<Point> p)
{
	movementPoints.clear();
	for (unsigned int i = 0; i < p.size(); i++)
		movementPoints.push_back(p[i]);

	setMovementFunction();
}

void Path::setMovementFunction()
{
	if (movementPoints.size())
		movementFunc = MovementFunction(movementPoints);
}

float Path::getXGivenY(float y) const
{
	return movementFunc.getXGivenY(y);
}

deque<Point> &Path::getMovementPoints() const
{
	return (deque<Point>&) movementPoints;
}

std::ostream &operator <<(std::ostream &ost, const Path &p)
{
	ost << p.movementPoints.size() << endl;
	for (unsigned int i = 0; i < p.movementPoints.size(); i++)
	{
		ost << p.movementPoints[i];
		if (i < p.movementPoints.size() - 1)
			ost << endl;
	}

	return ost;
}

std::istream &operator >>(std::istream &ist, Path &p)
{
	int size = 0;
	ist >> size;
	for (int i = 0; i < size; i++)
	{
		Point tmp;
		ist >> tmp;
		p.movementPoints.push_back(tmp);
	}
	p.setMovementFunction();

	return ist;
}
