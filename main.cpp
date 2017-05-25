#include <stdio.h>
#include "cVideoProcessor.hpp"

int main(int argc,const char **argv)
{	
	cout<<"hello";
	cVideoProcessor vid1("/home/riddlecoder/SU2017/cVideoProcessor/vid2.mp4");
	cVideoProcessor vid2("/home/riddlecoder/SU2017/cVideoProcessor/vid2.mp4");
	cVideoProcessor vid3("/home/riddlecoder/SU2017/cVideoProcessor/vid2.mp4");
	//vid1.mainProcess();
	//vid2.mainProcess(30,"Back");
	Rect roi=Rect(0,0,300,300);
	vid3.mainProcess(roi);
	cVideoProcessor vid4("/home/riddlecoder/SU2017/cVideoProcessor/gait02.mov");
	//vid4.mainProcess();
	
	//vid4.erosion("/home/riddlecoder/SU2017/cVideoProcessor/Stick/img158.jpg");
	
	waitKey(0);
	
	return 0;
}
