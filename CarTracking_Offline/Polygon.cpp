#include "Polygon.hpp"

Polygon::Polygon()
{
}

Polygon::Polygon(const deque<Point> v)
{
	vertexes.clear();
	for (unsigned int i = 0; i < v.size(); i += 2)
		vertexes.push_back(v[i]);
	for (int i = v.size() - 1; i >= 1; i -= 2)
		vertexes.push_back(v[i]);
}

bool Polygon::getCrossProductSym(const Point p1, const Point p2) const
{
	return (pCrossProduct(p1, p2) < 0) ? 0 : 1;
}

bool Polygon::isPointInPolygon(const Point p) const
{
	bool lastSym = getCrossProductSym(vertexes[0] - p, vertexes[1] - p);
	for (unsigned int i = 1; i < vertexes.size() - 1; i++)
		if (getCrossProductSym(vertexes[i] - p, vertexes[i + 1] - p) != lastSym)
			return 0;
	if (getCrossProductSym(vertexes.back() - p, vertexes.front() - p) != lastSym)
		return 0;
	return 1;
}

deque<Point> Polygon::getVertexes() const
{
	deque<Point> v;
	for (unsigned int i = 0; i < vertexes.size() / 2; i++)
	{
		v.push_back(vertexes[i]);
		v.push_back(vertexes[vertexes.size() - 1 - i]);
	}
	return v;
}

/*deque<Point> Polygon::getOutside() const
{
	float x[4];
	float y[4];
	memset(x, vertexes.front().x, sizeof(x));
	memset(y, vertexes.front().y, sizeof(y));

	for (int i = 1; i < vertexes.size(); i++)
	{
		if (vertexes[i].y <= y[0] && vertexes[i].x <= x[0])
		{
			x[0] = vertexes[i].x;
			y[0] = vertexes[i].y;
		}
		if (vertexes[i].y >= y[1] && vertexes[i].x <= x[1])
		{
			x[1] = vertexes[i].x;
			y[1] = vertexes[i].y;
		}
		if (vertexes[i].y <= y[2] && vertexes[i].x >= x[2])
		{
			x[2] = vertexes[i].x;
			y[2] = vertexes[i].y;
		}
		if (vertexes[i].y >= y[3] && vertexes[i].x >= x[3])
		{
			x[3] = vertexes[i].x;
			y[3] = vertexes[i].y;
		}
	}
}*/

std::ostream &operator <<(std::ostream &ost, const Polygon &p)
{
	ost << p.vertexes.size() << endl;
	for (unsigned int i = 0; i < p.vertexes.size() - 1; i++)
		ost << p.vertexes[i] << endl;
	ost << p.vertexes.back();

	return ost;
}

std::istream &operator >>(std::istream &ist, Polygon &p)
{
	int size = 0;
	ist >> size;
	for (int i = 0; i < size; i++)
	{
		Point tmp;
		ist >> tmp;
		p.vertexes.push_back(tmp);
	}

	return ist;
}
