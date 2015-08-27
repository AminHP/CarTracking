#include "Band.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Band::Band()
{
}

Band::Band(int numLines, Polygon cfn, deque<Car> totalCars)
{
	if (!loadFromFile())
	{
		deque<Point> v = cfn.getVertexes();
		confine = Polygon(v);

		for (int i = 1; i < numLines; i++)
		{
			float x = v[0].x + (((v[v.size() - 2].x - v[0].x) / numLines) * i);
			float y = v[0].y + (((v[v.size() - 2].y - v[0].y) / numLines) * i);
			v.insert(v.end() - 2, Point(x, y));

			x = v[1].x + (((v[v.size() - 1].x - v[1].x) / numLines) * i);
			y = v[1].y + (((v[v.size() - 1].y - v[1].y) / numLines) * i);
			v.insert(v.end() - 2, Point(x, y));
		}

		for (unsigned int i = 0; i < v.size() - 3; i += 2)
		{
			deque<Point> linePolygon;
			linePolygon.push_back(v[i]);
			linePolygon.push_back(v[i + 1]);
			linePolygon.push_back(v[i + 2]);
			linePolygon.push_back(v[i + 3]);
			lines.push_back(Line(linePolygon));
		}

		for (unsigned int i = 0; i < totalCars.size(); i++)
			for (unsigned int j = 0; j < lines.size(); j++)
				if (lines[j].isCarInPolygon(totalCars[i]))
				{
					lines[j].push_car(totalCars[i]);
					break;
				}
		for (unsigned int i = 0; i < lines.size(); i++)
			lines[i].setAveragePath();

		saveToFile();
	}
}

bool Band::loadFromFile()
{
	ifstream f("Data/AveragePath.ct", ios::in);
	if (!f)
		return 0;

	lines.clear();
	f >> confine;
	int size = 0;
	f >> size;
	for (int i = 0; i < size; i++)
	{
		Line l;
		f >> l;
		lines.push_back(l);
	}

	f.close();
	return 1;
}

void Band::saveToFile()
{
	ofstream f("Data/AveragePath.ct", ios::out);

	f << confine << endl;
	f << lines.size() << endl;
	for (unsigned int i = 0; i < lines.size(); i++)
		f << lines[i] << endl;

	f.close();
}

int Band::getCarLine(const Car &car) const
{
	for (unsigned int i = 0; i < lines.size(); i++)
		if (!lines[i].isEmpty())
			if (lines[i].isCarInPolygon(car))
				return i;
}

float Band::getMaxDistanceFromLine(const Car &car) const
{
	return lines[getCarLine(car)].getDistance(car);
}

deque<Line> &Band::getLines() const
{
	return (deque<Line>&) lines;
}
