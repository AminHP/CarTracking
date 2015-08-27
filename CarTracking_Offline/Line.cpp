#include "Line.hpp"

Line::Line()
{
}

Line::Line(deque<Point> v)
{
	confine = Polygon(v);
}

bool Line::isCarInPolygon(const Car c) const
{
	return confine.isPointInPolygon(c.getPath().getMovementPoints().front());
}

void Line::push_car(const Car c)
{
	tmp_cars.push_back(c);
}

void Line::setAveragePath()
{
	int miny = 1 << 30;
	int maxy = -(1 << 30);
	for (unsigned int i = 0; i < tmp_cars.size(); i++)
	{
		if (tmp_cars[i].getPath().getMovementPoints().back().y < miny)
			miny = tmp_cars[i].getPath().getMovementPoints().back().y;
		if (tmp_cars[i].getPath().getMovementPoints().front().y > maxy)
			maxy = tmp_cars[i].getPath().getMovementPoints().front().y;
	}

	deque<Point> p;
	p.clear();
	for (float y = miny; y <= maxy; y++)
	{
		float x = 0;
		float count = 0;
		for (unsigned int i = 0; i < tmp_cars.size(); i++)
			if (tmp_cars[i].isYInPath(y))
			{
				x += tmp_cars[i].getXGivenY(y);
				count ++;
			}
		x /= count;
		p.push_front(Point(x, y));
	}

	if (tmp_cars.size())
		empty_flag = 0;
	else
		empty_flag = 1;
	tmp_cars.clear();

	if (!isEmpty())
		averagePath = Path(p);
}

float Line::getDistance(const Car &car) const
{
	float dist = 0;
	for (float y = car.getPath().getMovementPoints().back().y; y <= car.getPath().getMovementPoints().front().y; y += 1.0f)
	{
		float x1 = averagePath.getXGivenY(y);
		float x2 = car.getPath().getXGivenY(y);
		dist += fabs(x1 - x2);
	}
	return dist;
}

bool Line::isEmpty() const
{
	return empty_flag;
}

Polygon &Line::getConfine() const
{
	return (Polygon&) confine;
}

Path &Line::getAveragePath() const
{
	return (Path&) averagePath;
}

std::ostream &operator <<(std::ostream &ost, const Line& l)
{
	ost << l.empty_flag << endl;
	if (!l.isEmpty())
		ost << l.averagePath << endl;
	ost << l.confine;

	return ost;
}

std::istream &operator >>(std::istream &ist, Line& l)
{
	ist >> l.empty_flag;
	if (!l.isEmpty())
		ist >> l.averagePath;
	ist >> l.confine;

	return ist;
}
