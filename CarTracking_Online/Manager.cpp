#include "Manager.hpp"

Manager::Manager()
{
	video.capture = NULL;
	band = Band();
	if (!band.loadFromFile())
	{
		cout << "Error: AveragePath.ct not found" << endl;
		exit(255);
	}
	confine = band.getConfine();
}

Manager::~Manager()
{
	cvReleaseImage(&ref);
}

deque<Point> Manager::getCenters(CvSeq *temp)
{
	deque<Point> res;
	while(temp != NULL)
	{
		/*int sumx = 0;
		int sumy = 0;
		for (int i = 0; i < temp->total; i++) 
		{
			CvPoint *p = (CvPoint*) cvGetSeqElem(temp, i);
			sumx += p->x;
			sumy += p->y;
		}

		Point p;
		p.x = sumx / temp->total;
		p.y = sumy / temp->total;
		if (confine.isPointInPolygon(p))
			res.push_back(p);
		temp = temp->h_next;*/


		CvRect rect = cvBoundingRect(temp);
		Point p;
		p.x = rect.x + (rect.width / 2);
		p.y = rect.y + (rect.height / 2);
		if (confine.isPointInPolygon(p))
			res.push_back(p);
		temp = temp->h_next;
	}

	return res;
}

void Manager::fillVideo()
{
	video.releaseCapture();
	video = Video("Data/Video.avi");
	if (!video.capture)
	{
		cout << "Error: Video.avi not found" << endl;
		exit(255);
	}
}

void Manager::fillReferenceImage()
{
	ref = cvLoadImage("Data/Reference.jpg");
	if (!ref)
	{
		cout << "Error: Reference.jpg not found" << endl;
		exit(255);
	}
}

string f2s(const float f)
{
	stringstream tmp (stringstream::in | stringstream::out);
	tmp << f;
	string res = tmp.str();
	return res;
}

void Manager::findCars()
{
	IplImage *grayRef = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	cvConvertImage(ref, grayRef, CV_CVTIMG_SWAP_RB);

	deque<Car> cars;

	IplImage *frame = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	IplImage *gray  = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	IplImage *diff  = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	CvMemStorage *g_storage;
	//int frameCount = -1;
	while (1)//(frameCount++ < 120)
	{
		frame = cvQueryFrame(video.capture);
		if (!frame)
			break;

		cvConvertImage(frame, gray, CV_CVTIMG_SWAP_RB);
		cvSub(grayRef, gray, diff);

		cvThreshold(diff, diff, 100, 255, CV_THRESH_BINARY);
		cvErode(diff, diff, NULL, 10);
		cvDilate(diff, diff, NULL, 50);
		cvErode(diff, diff, NULL, 40);
		//cvErode(diff, diff, NULL, 5);
		//cvDilate(diff, diff, NULL, 20);

		for (unsigned int i = 0; i < band.getLines().size(); i++)
			if (!band.getLines()[i].isEmpty())
			{
				for (float y = band.getLines()[i].getAveragePath().getMovementPoints().back().y; 
						y <= band.getLines()[i].getAveragePath().getMovementPoints().front().y; y += 1.0f)
				{
					CvScalar col;
					col.val[0] = 0;
					col.val[1] = 255;
					col.val[2] = 255;
					col.val[3] = 150;
					cvCircle(frame, cvPoint(band.getLines()[i].getAveragePath().getXGivenY(y), y), 5, col);
				}
			}

		CvScalar col;
  		col.val[0] = 255;
  		col.val[1] = 255;
  		col.val[2] = 0;
  		col.val[3] = 0;
		cvCircle(frame, cvPoint(confine.getVertexes()[0].x, confine.getVertexes()[0].y), 15, col);
		cvCircle(frame, cvPoint(confine.getVertexes()[1].x, confine.getVertexes()[1].y), 15, col);
		cvCircle(frame, cvPoint(confine.getVertexes()[2].x, confine.getVertexes()[2].y), 15, col);
		cvCircle(frame, cvPoint(confine.getVertexes()[3].x, confine.getVertexes()[3].y), 15, col);

		for (unsigned int i = 0; i < band.getLines().size(); i++)
			if (!band.getLines()[i].isEmpty())
				for (unsigned int j = 0; j < band.getLines()[i].getConfine().getVertexes().size(); j++)
				{
					CvScalar col;
					col.val[0] = 255;
					col.val[1] = 0;
					col.val[2] = 255;
					col.val[3] = 0;
					cvCircle(frame, cvPoint(band.getLines()[i].getConfine().getVertexes()[j].x, 
							band.getLines()[i].getConfine().getVertexes()[j].y), 20, col);
				}

		g_storage = cvCreateMemStorage(0);
		CvSeq* contours = NULL;
		cvFindContours(diff, g_storage, &contours);
		cvClearMemStorage(g_storage);

		CvSeq *temp = contours;
		while (temp != NULL)
		{
			CvRect rect = cvBoundingRect(temp);
			CvPoint p1;
			p1.x = rect.x;
			p1.y = rect.y;
			CvPoint p2;
			p2.x = rect.x + rect.width;
			p2.y = rect.y + rect.height;
			cvRectangle(frame, p1, p2, cvScalarAll(255));
			temp = temp->h_next;
		}

		if (contours)
		{
			deque<Point> centers = getCenters(contours);
			//cerr << "Number of cars in frame = " << centers.size() << endl;
			CvScalar color;
			color.val[0] = 255;
			color.val[1] = 0;
			color.val[2] = 0;
			color.val[3] = 255;

			unsigned int i = 0;
			while (i < cars.size())
			{
				int minDis = 1 << 30;
				int index = 0;
				for (unsigned int j = 0; j < centers.size(); j++)
				{
					float d = pDistance(cars[i].getCurrentPoint(), centers[j]);
					if (d < minDis)
					{
						minDis = d;
						index = j;
					}
				}

				if (minDis < 100)
				{
					cars[i++].push_point(centers[index]);
					centers.erase(centers.begin() + index);
				}
				else
				{
					cars.erase(cars.begin() + i);
				}
			}
			for (unsigned int j = 0; j < centers.size(); j++)
			{
				Point p;
				p.x = centers[j].x;
				p.y = centers[j].y;
				Car c = Car(p, video.fps);
				cars.push_back(c);
			}
			centers.clear();

			for (unsigned int i = 0; i < cars.size(); i++)
			{
				cars[i].setLines(band);
				cars[i].setSpeeds(band);

				CvScalar color;
				float diff_line = band.getConfine().getLines_pixel_width(cars[i].getCurrentPoint().y) / 3.0f;
				if (fabs(cars[i].getCurrentPoint().x -
						band.getLines()[cars[i].getLine()].getAveragePath().getXGivenY(cars[i].getCurrentPoint().y)) > diff_line &&
						fabs(cars[i].getCurrentPoint().x -
						band.getLines()[cars[i].getLine2()].getAveragePath().getXGivenY(cars[i].getCurrentPoint().y)) > diff_line)
				{
					cars[i].setNOY_plusPlus();
					color.val[0] = 0;
					color.val[1] = 0;
					color.val[2] = 255;
					color.val[3] = 0;
				}
				else
				{
					color.val[0] = 255;
					color.val[1] = 0;
					color.val[2] = 0;
					color.val[3] = 255;
				}
				cvCircle(frame, cvPoint(cars[i].getCurrentPoint().x, cars[i].getCurrentPoint().y), 25, color);

				if (cars[i].getNOY() > video.fps)
				{
					color.val[0] = 0;
					color.val[1] = 0;
					color.val[2] = 255;
					color.val[3] = 0;
				}
				else
				{
					color.val[0] = 255;
					color.val[1] = 0;
					color.val[2] = 0;
					color.val[3] = 255;
				}
				cvCircle(frame, cvPoint(cars[i].getCurrentPoint().x, cars[i].getCurrentPoint().y), 30, color);



				if (cars[i].getCurrentSpeed() < band.getLines()[cars[i].getLine()].getMaxSpeed() &&
						cars[i].getCurrentSpeed() > band.getLines()[cars[i].getLine()].getMinSpeed())
				{
					color.val[0] = 255;
					color.val[1] = 0;
					color.val[2] = 0;
					color.val[3] = 255;
				}
				else
				{
					color.val[0] = 0;
					color.val[1] = 0;
					color.val[2] = 255;
					color.val[3] = 0;
				}
				CvFont font;
				cvInitFont(&font,CV_FONT_HERSHEY_TRIPLEX, 0.75, 0.75);
				cvPutText(frame, f2s(cars[i].getCurrentSpeed()).c_str(),
						cvPoint(cars[i].getCurrentPoint().x - 14, cars[i].getCurrentPoint().y- 3), &font, color);

				if (cars[i].getMaxSpeed() < band.getLines()[cars[i].getLine()].getMaxSpeed())
				{
					color.val[0] = 255;
					color.val[1] = 0;
					color.val[2] = 0;
					color.val[3] = 255;
				}
				else
				{
					color.val[0] = 0;
					color.val[1] = 0;
					color.val[2] = 255;
					color.val[3] = 0;
				}
				cvPutText(frame, f2s(cars[i].getMaxSpeed()).c_str(),
						cvPoint(cars[i].getCurrentPoint().x - 14, cars[i].getCurrentPoint().y + 20), &font, color);

				if (cars[i].getMinSpeed() > band.getLines()[cars[i].getLine()].getMinSpeed())
				{
					color.val[0] = 255;
					color.val[1] = 0;
					color.val[2] = 0;
					color.val[3] = 255;
				}
				else
				{
					color.val[0] = 0;
					color.val[1] = 0;
					color.val[2] = 255;
					color.val[3] = 0;
				}
				cvPutText(frame, f2s(cars[i].getMinSpeed()).c_str(),
						cvPoint(cars[i].getCurrentPoint().x - 14, cars[i].getCurrentPoint().y + 40), &font, color);
			}
		}

		cvShowImage("Frame:", frame);
		cvWaitKey(2);
		//cvWaitKey(150 / video.fps);
		//cvWaitKey();
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&ref);
	cvReleaseImage(&grayRef);
	cvReleaseImage(&diff);
	video.releaseCapture();

	cvWaitKey();
}

void Manager::run()
{
	fillVideo();
	fillReferenceImage();
	findCars();
}
