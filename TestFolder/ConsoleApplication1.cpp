#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main1(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, "{@input | 16bit_grayscale.TIF | input image}");
	Mat src = imread(parser.get<String>("@input"), IMREAD_ANYDEPTH);
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
//	cvtColor(src, src, COLOR_BGR2GRAY);
	//Mat dst;
	//equalizeHist(src, dst);
	//imshow("Source image", src);
	int scale_percent = 20;
	int	width = int(src.size().width * scale_percent / 100);
	int	height = int(src.size().height * scale_percent / 100);
	resize(src, src, cv::Size(width, height));
	//equalizeHist
	imwrite("resize.TIF", src);
	imshow("Equalized Image", src);
	waitKey();
	return 0;
}