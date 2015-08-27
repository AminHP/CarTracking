#include "Video.hpp"

Video::Video()
{
}

Video::Video(const char *addr)
{
	capture = cvCaptureFromAVI(addr);
	height    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	width     = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
}

Video::~Video()
{
}

void Video::releaseCapture()
{
	if (capture)
		cvReleaseCapture(&capture);
}
