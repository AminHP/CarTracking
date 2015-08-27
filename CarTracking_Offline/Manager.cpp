#include "Manager.hpp"

Manager::Manager()
{
	video.capture = NULL;
	band = Band();
}

Manager::~Manager()
{
	cvReleaseImage(&ref);
	totalCars.clear();
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

void Manager::createReferenceImage()
{
	uchar ***a = new uchar**[video.height];
	for (int i = 0; i < video.height; i++)
	{
		a[i] = new uchar*[video.width];
		for (int j = 0; j < video.width; j++)
		{
			a[i][j] = new uchar[256];
			for (int k = 0; k < 256; k++)
				a[i][j][k] = 0;
		}
	}

	IplImage *gray = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	while(1)
	{
		IplImage *frame = cvQueryFrame(video.capture);
		if (frame == NULL)
			break;
		cvCvtColor(frame, gray, CV_BGR2GRAY);
		for (int i = 0; i < video.height; i++)
			for (int j = 0; j < video.width; j++)
		a[i][j][CV_IMAGE_ELEM(gray, uchar, i, j)] ++;
		//cvWaitKey(600 / fps);
	}
	cvReleaseImage(&gray);

	IplImage *refrenceImage = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	for (int i = 0; i < video.height; i++)
		for (int j = 0; j < video.width; j++)
		{
			int max = -(1 << 30);
			int color = 0;
			for (int k = 0; k < 256; k++)
				if (a[i][j][k] > max)
				{
					max = a[i][j][k];
					color = k;
				}
			CV_IMAGE_ELEM(refrenceImage, uchar, i, j) = color;
		}

	for (int i = 0; i < video.height; i++)
	{
		for (int j = 0; j < video.width; j++)
			delete [](a[i][j]);
		delete [](a[i]);
	}
	delete [](a);

	cvSaveImage("Data/Reference.jpg", refrenceImage);
	fillVideo();
}

void Manager::fillReferenceImage()
{
	ref = NULL;
	ref = cvLoadImage("Data/Reference.jpg");
	if (!ref)
	{
		createReferenceImage();
		ref = cvLoadImage("Data/Reference.jpg");
	}
}

void Manager::fillConfineAndNumLines()
{
	numLines = 0;
	deque<Point> v;

//	To do it by better ideas
	v.push_back(Point(230, 250));
	v.push_back(Point(30, video.height - 200));
	v.push_back(Point(video.width - 450, 250));
	v.push_back(Point(video.width - 170, video.height - 200));
	confine = Polygon(v);

	numLines = 3;
}

void Manager::fillTotalCars()
{
	totalCars.clear();
	band.loadFromFile();

	IplImage *grayRef = cvCreateImage(cvSize(video.width, video.height), 8, 1);
	cvConvertImage(ref, grayRef, CV_CVTIMG_SWAP_RB);

	deque< deque<Point> > cars;

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
			for (unsigned int i = 0; i < centers.size(); i++)
				cvCircle(frame, cvPoint(centers[i].x, centers[i].y), 25, color);

			unsigned int i = 0;
			while (i < cars.size())
			{
				int minDis = 1 << 30;
				int index = 0;
				for (unsigned int j = 0; j < centers.size(); j++)
				{
					float d = pDistance(cars[i].back(), centers[j]);
					if (d < minDis)
					{
						minDis = d;
						index = j;
					}
				}

				if (minDis < 100)
				{
					cars[i++].push_back(centers[index]);
					centers.erase(centers.begin() + index);
				}
				else
				{
					Car c = Car(cars[i]);
					totalCars.push_back(c);
					cars.erase(cars.begin() + i);
				}
			}
			for (unsigned int j = 0; j < centers.size(); j++)
			{
				Point p;
				p.x = centers[j].x;
				p.y = centers[j].y;
				deque<Point> tmp;
				tmp.push_back(p);
				cars.push_back(tmp);
			}
			centers.clear();
			cerr << "Number of cars in all frames = " << totalCars.size() << endl;
		}
		//cvShowImage("Frame:", frame);
		//cvShowImage("Diff:", diff);
		//cvWaitKey(150 / video.fps);
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&ref);
	cvReleaseImage(&grayRef);
	cvReleaseImage(&diff);
	video.releaseCapture();

	unsigned int index = 0;
	while (index < totalCars.size())
	{
		if (totalCars[index].getPath().getMovementPoints().size() <= 5)
			totalCars.erase(totalCars.begin() + index);
		else
			index ++;
	}

	cerr << "Total Cars = " << totalCars.size() << endl;

	for (unsigned int i = 0; i < totalCars.size(); i++)
		totalCars[i].log(i);

	if (!band.loadFromFile())
		fillBand();
	//cvWaitKey();
	//cvDestroyWindow("Frame:");

	IplImage *log_image = cvCreateImage(cvSize(video.width, video.height), 8, 3);

	for (unsigned int i = 0; i < totalCars.size(); i++)
		for (float y = totalCars[i].getPath().getMovementPoints().back().y; 
				y <= totalCars[i].getPath().getMovementPoints().front().y; y += 1.0f)
		{
			CvScalar col;
			col.val[0] = 255;
			col.val[1] = 255;
			col.val[2] = 0;
			col.val[3] = 0;
			cvCircle(log_image, cvPoint(totalCars[i].getPath().getXGivenY(y), y), 2, col);
		}

	/*for (unsigned int i = 0; i < totalCars[1].getPath().getMovementPoints().size(); i++)
	{
		CvScalar col;
		col.val[0] = 255;
		col.val[1] = 0;
		col.val[2] = 0;
		col.val[3] = 255;
		cvCircle(log_image, cvPoint(totalCars[1].getPath().getMovementPoints()[i].x, 
				totalCars[1].getPath().getMovementPoints()[i].y), 2, col);
	}*/

	for (unsigned int i = 0; i < band.getLines().size(); i++)
		if (!band.getLines()[i].isEmpty())
			for (float y = band.getLines()[i].getAveragePath().getMovementPoints().back().y; 
					y <= band.getLines()[i].getAveragePath().getMovementPoints().front().y; y += 1.0f)
			{
				CvScalar col;
				col.val[0] = 0;
				col.val[1] = 255;
				col.val[2] = 255;
				col.val[3] = 150;
				cvCircle(log_image, cvPoint(band.getLines()[i].getAveragePath().getXGivenY(y), y), 5, col);
			}

	cvSaveImage("LogFiles/AveragePath.jpg", log_image);
	cvShowImage("LOG_IMAGE:", log_image);
	cvReleaseImage(&log_image);
	cvWaitKey();
}

void Manager::fillBand()
{
	band = Band(numLines, confine, totalCars);
}

void Manager::getProblems()
{
	for (unsigned int i = 0; i < totalCars.size(); i++)
	{
		if (band.getMaxDistanceFromLine(totalCars[i]) > 10000)
			cout << "car[" << i << "] az masir monharef shode ! :D" << endl;
		else if (totalCars[i].getSpeed(video.fps) > 60.0f)
			cout << "car[" << i << "] sorate qeire mojaz dare ! :)" << endl;
		else 
			cout << "car[" << i << "] Adame khobiye :(" << endl ;
	}
}

void Manager::run()
{
	fillVideo();
	fillReferenceImage();
	fillConfineAndNumLines();
	fillTotalCars();
	getProblems();
}
