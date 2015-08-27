#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

struct Video {
	CvCapture *capture;
	int width;
	int height;
	int fps;
	int numFrames;

	Video();
	Video(const char*);
	~Video();

	void releaseCapture();
};

#endif // VIDEO_HPP
