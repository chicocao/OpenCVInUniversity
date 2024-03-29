#include "cv.h"
#include "highgui.h"

IplImage* doCanny(
	IplImage* in,
	double    lowThresh,
	double    highThresh,
	double    aperture)
{
	IplImage* out = cvCreateImage(
		cvGetSize(in),
		in->depth, //IPL_DEPTH_8U,    
		1);
	cvCanny(in, out, lowThresh, highThresh, aperture);
	return(out);
};

IplImage* doPyrDown(
	IplImage* in,
	int       filter = IPL_GAUSSIAN_5x5)
{

	// Best to make sure input image is divisible by two.
	//
	//assert(in->width % 2 == 0 && in->height % 2 == 0);

	IplImage* out = cvCreateImage(
		cvSize(in->width / 2, in->height / 2),
		in->depth,
		in->nChannels
	);
	cvPyrDown(in, out);
	return(out);
};

int m_ain(int argc, char** argv)
{
	IplImage* img_rgb = cvLoadImage("1.jpg");
	IplImage* img_gry = cvCreateImage(cvSize(img_rgb->width, img_rgb->height), img_rgb->depth, 1);
	cvCvtColor(img_rgb, img_gry, CV_BGR2GRAY);
	IplImage* img_pyr = doPyrDown(img_gry, IPL_GAUSSIAN_5x5);
	IplImage* img_pyr2 = doPyrDown(img_pyr, IPL_GAUSSIAN_5x5);
	IplImage* img_cny = doCanny(img_pyr2, 10, 100, 3);

	cvNamedWindow("Example Gray", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example Pyr", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example Canny", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example Gray", img_gry);
	cvShowImage("Example Pyr", img_pyr2);
	cvShowImage("Example Canny", img_cny);
	cvWaitKey(0);
	cvReleaseImage(&img_rgb);
	cvReleaseImage(&img_gry);
	cvReleaseImage(&img_pyr);
	cvReleaseImage(&img_pyr2);
	cvReleaseImage(&img_cny);
	cvDestroyWindow("Example Gray");
	cvDestroyWindow("Example Pyr");
	cvDestroyWindow("Example Canny");
	return 0;
}
