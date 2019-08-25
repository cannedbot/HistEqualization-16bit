#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "HistEqualization.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, "{@input | 16bit_grayscale.TIF | input image}");
	Mat src = imread(parser.get<String>("@input"), IMREAD_ANYDEPTH);
	//cout << "val_org: " << src.channels() << endl;

	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}

	if (src.depth() == 2)
	{
		cout << "Input image is the correct depth 16bits" << endl;

		//	cvtColor(src, src, COLOR_BGR2GRAY);
		Mat dst;
		HistEqualization::equalize16Bit(src, dst);
		//	imshow("Source image", src);
		//	int scale_percent = 20;
		//	int	width = int(src.size().width * scale_percent / 100);
		//	int	height = int(src.size().height * scale_percent / 100);
		//	resize(src, src, cv::Size(width, height));

		cout << "val_resize: " << src.channels() << endl;
		imwrite("16bit_1ch_grayscale_src.TIF", src);
		imwrite("16bit_1ch_grayscale_dst.TIF", dst);
		//	imshow("Ori Image", src);
		//	imshow("Equalized Image", dst);
		//	waitKey();
		//	return 0;
		cout << "Press ENTER to quit" << endl;
		cin.get();
	}
	else
	{
		cout << "Input image is not the correct depth 16bits" << endl;
		cout << "Please input 16bit image" << endl;
	}

	
	
}

