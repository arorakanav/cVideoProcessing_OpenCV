/*SU-function cImgProcessing
*Day03
*Kanav Arora & Ahmed Abid
*16thFebruary
*/

#include "cVideoProcessor.hpp"


using namespace std;
using namespace cv;

cVideoProcessor::cVideoProcessor(String _filename)
{
		
		videoStream.open(_filename);
		if(!videoStream.isOpened())
		{
				cout<<"Error Reading video";
		}
}

void cVideoProcessor::mainProcess()
{	
	frameCount=0;
		namedWindow( "Display Frame", WINDOW_AUTOSIZE );
		videoStream.read(colorFrame);
		
		for(;colorFrame.rows>0;)
		{	
			
			 colorFrame=frameProcess();
			 imshow("Display Frame",colorFrame);
			 waitKey(1);
			videoStream.read(colorFrame);			
		}
}

Mat cVideoProcessor::frameProcess()
{
	
	frameCount++;
	grayImg.create(colorFrame.rows,colorFrame.cols,CV_8UC1);
	graythresh.create(colorFrame.rows,colorFrame.cols,CV_8UC1);
		for(int i=0;i<colorFrame.rows;i++){
			for(int j=0;j<colorFrame.cols;j++){
				 grayImg.at<uchar>(i,j)=getPixelAvg(i,j);	
			}
		}
		meanFrame=cv::mean(grayImg)[0];
		sprintf(text,"Frame no : %d Mean: %lf",frameCount,meanFrame);
		
		graythresh=treshold(42,grayImg);
		saveFrame(frameCount,"/home/riddlecoder/SU2017/cVideoProcessor/Stick/");
		
		
		return grayImg;

	
}

uint32_t cVideoProcessor::getPixelAvg(uint32_t row, uint32_t col)
{
		return ((colorFrame.at<cv::Vec3b>(row,col)[0]+colorFrame.at<cv::Vec3b>(row,col)[1]+colorFrame.at<cv::Vec3b>(row,col)[2])/3);
}

void cVideoProcessor::saveFrame(int frameno,const char *path)
{
	char nameImg[100];
	
	sprintf(nameImg,"%simg%d.jpg",path,frameno);
	imwrite(nameImg,graythresh);
	
}

void cVideoProcessor::mainProcess(int frameno,const char *fName)//E_COMPUTE_BGND,int frameno,const char *fName)
{		
	
		int count;
		count=0;
		char path[100];
		
		videoStream.read(colorFrame);
		for(;colorFrame.rows>0;)
		{	
			colorFrame=frameProcess();
			if(count==frameno)
			{
			
				sprintf(path,"/home/riddlecoder/SU2017/cVideoProcessor/Images/%s",fName);
				saveFrame(frameno,path);
			}
			count++;
			colorFrame=frameProcess();
			videoStream.read(colorFrame);			
		}
}

void cVideoProcessor::mainProcess(Rect roi)
{
   backImg=imread("/home/riddlecoder/SU2017/cVideoProcessor/Images/Backimg30.jpg",CV_LOAD_IMAGE_GRAYSCALE);
   Mat greyImage;
	int count=0;
   roiImg=backImg(roi);
   bsImg.create(roiImg.rows,roiImg.rows, CV_8U);
   
   videoStream.read(colorFrame);
   
   /*namedWindow( "Display subImg", WINDOW_AUTOSIZE );// Create a window for display.
   namedWindow( "Display threshImg", WINDOW_AUTOSIZE );// Create a window for display.*/
   
   for(;colorFrame.rows>0;)
	{
		greyImage=frameProcess();
		greyImage=greyImage(roi);
		absdiff( greyImage, roiImg, bsImg);
		videoStream.read(colorFrame);
		threshImg=treshold(42,bsImg);
		imshow("Display subImg", bsImg );
		imshow("Threshold image",threshImg);
		threshImg=treshold(127,bsImg);
		imshow("Threshold100 image",threshImg);
		waitKey(1);
		count++;
	}
}

Mat cVideoProcessor::treshold(uint8_t tresh , Mat thresh)
{
	size_t row = thresh.rows, col = thresh.cols;
	Mat out(row, col, CV_8UC1);
	for(size_t i = 0; i < row; i++)
	{
		for(size_t j = 0; j < col; j++)
		{
			out.at<uint8_t>(i, j) = thresh.at<uint8_t>(i,j) > tresh ? 255 : 0;
			//flodding(out,i,j);
		}
	}
	return out;
}

void cVideoProcessor::flodding(Mat LB,int rows,int cols)
{
	Mat process=LB.clone();
	if(process.at<uchar>(rows,cols)==0)
	
	if(process.at<uchar>(rows,cols)==255)
	{
			x.push_back(rows);
			y.push_back(cols);
			process.at<uchar>(rows,cols)=0;
			//flodding(Mat process,);
	}
}

void cVideoProcessor::erosion(String _filename)
{
		int compbit;
		int  arrayerr[3][3]={{0,255,0},{255,255,255},{0,255,0}};
		Mat errorsion=Mat(100,100,CV_8UC1,&arrayerr);
		//skeletonthresh=imread("/home/riddlecoder/SU2017/cVideoProcessor/Stick/img158.jpg",CV_LOAD_IMAGE_GRAYSCALE);
		Mat square(16, 16, CV_8UC1);
		size_t xMin = 7, xMax = 14;
		for(size_t i = 0; i < 16; i++)
		{
			for(size_t j = 0; j < 16; j++)
			{
				if(i > xMin && i < xMax && j > xMin && j<xMax)
				square.at<uchar>(i, j) = 255;
				else
				square.at<uchar>(i, j) = 0;
			}
		}
		namedWindow( "Display TrialImg", WINDOW_AUTOSIZE );// Create a window for display.
		imshow("Display TrialImg",square);
		Mat errodedImg(square.rows,square.cols,CV_8UC1,Scalar(0));
		for(int i=errorsion.rows/2;i<(square.rows);i++)
		{
			for(int j=errorsion.cols/2;j<(square.cols);j++)
			{
				compbit=square.at<uchar>(i,j) & errorsion.at<uchar>(i,j);
				compbit=square.at<uchar>(i+1,j)& errorsion.at<uchar>(i+1,j); 
				compbit=square.at<uchar>(i-1,j)& errorsion.at<uchar>(i-1,j); 
				compbit=square.at<uchar>(i,j+1) & errorsion.at<uchar>(i,j+1); 
				compbit=square.at<uchar>(i,j-1)& errorsion.at<uchar>(i,j-1); 
				if(compbit==255)
					errodedImg.at<uchar>(i,j)=square.at<uchar>(i,j);
			}
		}
		namedWindow( "Display subImg", WINDOW_AUTOSIZE );// Create a window for display.
		imshow("Display subImg",errodedImg);
}


