#include "Band.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Band::Band()
{
}

bool Band::loadFromFile()
{
	ifstream f("Data/AveragePath.ct", ios::in);
	if (!f)
		return 0;

	lines.clear();
	f >> confine;
	confine.setLinearFuncs();

	int size = 0;
	f >> size;
	for (int i = 0; i < size; i++)
	{
		Line l;
		f >> l;
		lines.push_back(l);
	}

	f.close();

	ifstream plines("Data/PLines.ct", ios::in);
	if (!plines)
		return 0;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		float minSpeed, maxSpeed;
		plines >> minSpeed >> maxSpeed;
		lines[i].setMinSpeed(minSpeed);
		lines[i].setMaxSpeed(maxSpeed);
	}
	plines >> lines_width;

	plines.close();

	confine.setNOL(lines.size());
	confine.setLines_width(lines_width);

	return 1;
}

float Band::getLines_width() const
{
	return lines_width;
}

deque<Line> &Band::getLines() const
{
	return (deque<Line>&) lines;
}

Polygon &Band::getConfine() const
{
	return (Polygon&) confine;
}
