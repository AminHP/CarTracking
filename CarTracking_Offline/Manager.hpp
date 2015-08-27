#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <cstdlib>
#include <time.h>
#include <deque>
#include <cmath>

#include "brANLine.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "Video.hpp"
#include "Car.hpp"
#include "Band.hpp"

using namespace std;

class Manager {
private:
	Video video;
	IplImage *ref;
	deque<Car> totalCars;
	int numLines;
	Polygon confine;
	Band band;

	deque<Point> getCenters(CvSeq*);
	void fillVideo();
	void createReferenceImage();
	void fillReferenceImage();
	void fillConfineAndNumLines();
	void fillTotalCars();
	void fillBand();
	void getProblems();

public:
	Manager();
	~Manager();

	void run();
};

#endif // MANAGER_HPP
