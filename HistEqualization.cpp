#include "HistEqualization.h"


bool HistEqualization::equalize16Bit(const cv::Mat& _src, cv::Mat& _dst)
{
	int channel, depth;
	bool rval = false;
	//String type2str(const Mat & src);
	float  type = _src.type();
	channel = _src.channels();
	depth = _src.depth();
	// check input type

	/*cout << "Type:" << type << endl;
	cout << "Channel:" << channel << endl;
	cout << "Depth:" << depth << endl;*/

	if ((type == 2) && (channel == 1) && (depth == 2))
	{
		cout << "Image is acceptable format 16bit grayscale" << endl;
		
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
			//return;
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

		rval = true;
	}
	else if ((type == 0) && (channel == 1) && (depth == 0))
	{
		cout << "Image is not in acceptable format 16bit grayscale" << endl;
		cout << "Image is 8bit RGB format" << endl;
		
		rval = false;
	}
	else if ((type == 2) && (channel == 3) && (depth == 2))
	{
		cout << "Image is not in acceptable format 16bit grayscale" << endl;
		cout << "Image is 16bit RGB format" << endl;

		rval = false;
	}
	else
	{
		cout << "Image is not in acceptable format 16bit grayscale" << endl;

		rval = false;
	}


	
	return rval;
}