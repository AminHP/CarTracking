#include "Car.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

Car::Car()
{
}

Car::Car(deque<Point> p)
{
	path = Path(p);
}

Path &Car::getPath() const
{
	return (Path&) path;
}

string i2s(int a)
{
	if (a == 0)
		return "0" ;
	string out = "" ;
	while (a != 0)
	{
		int baghimande = a % 10 ;
		a /= 10 ;
		out += "0" ;
		out[out.size()-1] = (baghimande + '0') ;
	}
	reverse(out.begin(), out.end()) ;
	return out ;
}

void Car::log(int index) const
{
	string xtAdd = "LogFiles/xt";
	string ytAdd = "LogFiles/yt";
	xtAdd += i2s(index);
	ytAdd += i2s(index);
	xtAdd += ".txt";
	ytAdd += ".txt";
	ofstream xFile(xtAdd.c_str());
	ofstream yFile(ytAdd.c_str());

/*	for (float y = path.getMovementPoints().front().y; y >= path.getMovementPoints().back().y; y -= 0.2)
	{
		xFile << path.getXGivenY(y) << endl;
		yFile << y << endl;
	}*/
	for (unsigned int i = 0; i < path.getMovementPoints().size(); i++)
	{
		xFile << path.getMovementPoints()[i].x << endl;
		yFile << path.getMovementPoints()[i].y << endl;
	}
}

bool Car::isYInPath(float y)
{
	if (y >= path.getMovementPoints().back().y && y <= path.getMovementPoints().front().y)
		return 1;
	return 0;
}

float Car::getXGivenY(float y)
{
	return path.getXGivenY(y);
}

float Car::getSpeed(float fps) const
{
	return (pDistance(path.getMovementPoints().front(), path.getMovementPoints().back()) / 100) / (path.getMovementPoints().size() / fps);
}

/*
void Car::saveToFile(int index) const
{
	string addr = "Data/Cars/";
	addr += i2s(index);
	addr += ".ct";
	ofstream file(addr.c_str(), ios::out);

	file << path << endl;
	file.close();
}
*/

/*
bool Car::loadFromFile(int index)
{
	string addr = "Data/Cars/";
	addr += i2s(index);
	addr += ".ct";
	ifstream file(addr.c_str(), ios::in);
	if (!file)
		return 0;

	file >> path;

	file.close();
	return 1;
}
*/

/*
std::ostream &operator <<(std::ostream &ost, const Car& c)
{
	ost << c.path;

	return ost;
}
*/

/*
std::istream &operator >>(std::istream &ist, Car& c)
{
	ist >> c.path;

	return ist;
}
*/
