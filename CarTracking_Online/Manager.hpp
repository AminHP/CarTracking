#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
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
	Polygon confine;
	Band band;

	deque<Point> getCenters(CvSeq*);
	void fillVideo();
	void fillReferenceImage();
	void findCars();

public:
	Manager();
	~Manager();

	void run();
};

#endif // MANAGER_HPP
