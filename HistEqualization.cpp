#include "HistEqualization.h"


void HistEqualization::equalize16Bit(const cv::Mat& _src, cv::Mat& _dst)
{
	_dst = _src.clone();

	// 16bit size
	const int hist_sz = 65536;

	int* hist = new int[hist_sz] {};
	int* lut = new int[hist_sz] {};

	// Mat::at() -> Returns a reference to the specified array element.
	for (int y = 0; y < _src.rows; y++)
		for (int x = 0; x < _src.cols; x++)
			hist[(int)_src.at<unsigned short int>(y, x)]++;

	auto i = 0;
	while (!hist[i]) ++i;

	// The method returns the number of pixels in an image.
	auto total = (int)_src.total();
	if (hist[i] == total)
	{
		_dst.setTo(i);
		return;
	}

	float scale = (hist_sz - 1.f) / (total - hist[i]);
	auto sum = 0;

	for (lut[i++] = 0; i < hist_sz; ++i)
	{
		sum += hist[i]; // cumulative frequency
		lut[i] = cv::saturate_cast<ushort>(sum * scale);
	}

	for (int y = 0; y < _src.rows; y++)
		for (int x = 0; x < _src.cols; x++)
		{
			_dst.at<unsigned short int>(y, x) = lut[(int)_src.at<unsigned short int>(y, x)];
		}
}