#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class HistEqualization
{
public:
	static void equalize16Bit(const cv::Mat& _src, cv::Mat& _dst);
};