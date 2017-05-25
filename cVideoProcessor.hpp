/*SU-function cImgProcessing
*Day03
*Kanav Arora & Ahmed Abid?
*16thFebruary
*/

#ifndef CVIDEOPROCESSOR_HPP
#define CVIDEOPROCESSOR_HPP

//system include files
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <list>


// user include files
#include "cVideoProcessor.hpp"

using namespace std;
using namespace cv;

class cVideoProcessor
{

	private:
		VideoCapture videoStream;
		Mat colorFrame;
		Mat grayImg;
		Mat backImg;
		Mat roiImg;
		Mat compImg;
		Mat bsImg;
		Mat threshImg;
		Mat out;
		double meanFrame;
		uint32_t sumPixels;
		int frameCount;
		char text[100];
		list<uint8_t> x;
		list<uint8_t> y;
		Mat graythresh;
		Mat skeletonthresh;

	public:
		cVideoProcessor(String _filename);
		void mainProcess();
		void mainProcess(int frameno,const char *fName);//E_COMPUTE_BGND,int frameno,const char *fName);
		void mainProcess(Rect roi);
		Mat frameProcess();
		uint32_t getPixelAvg(uint32_t row, uint32_t col);
		void saveFrame(int frameno,const char *path);
		Mat treshold(uint8_t tresh,Mat thresh);
		void flodding(Mat temp,int x,int y);
		void search(Mat LB, int label, int r, int c);
		void erosion(String _filename);
};

#endif