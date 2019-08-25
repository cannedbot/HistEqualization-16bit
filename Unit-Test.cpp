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
	string imageName = "test_image.TIF";
	string testFolder = "TestFolder\\";
	string inputFilename = testFolder + imageName;
	cout << "Reading image : " << inputFilename << endl;


	Mat src = imread(inputFilename, IMREAD_ANYDEPTH);

	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
	//	cvtColor(src, src, COLOR_BGR2GRAY);
	Mat dst;
	HistEqualization::equalize16Bit(src, dst);

	imwrite("unit_test_output.TIF", dst);
	cout << "Test unit successful..." << endl;
	cout << "Press ENTER to quit" << endl;
	cin.get();
}

