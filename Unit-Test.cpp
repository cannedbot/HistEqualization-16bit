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
namespace filesys = std::experimental::filesystem;
void removeSubstrs(string& s, string& p);

vector <string> test_list;
vector <string> error_list;

int main(int argc, char** argv)
{
	int errorCounts = 0;
	int successfulCounts = 0;
	// put images in test-images folder to a list
	string path = "./test-images";
	cout << "############################" << endl;
	cout << "Initiating unit test..." << endl;
	cout << "reading from path: " << path << endl;
	
	for (const auto& entry : filesys::directory_iterator(path))
	{
		string a = entry.path().string();
		string b = ".\\test-images\\";
		removeSubstrs(a, b);
		test_list.push_back(a);
		/*cout << a << std::endl;*/
	}

	cout << "List of images found: " << endl;
	for (int i = 0; i < test_list.size(); i++)
		cout << test_list[i] << "\n";

	cout << endl;

	for (int i = 0; i < test_list.size(); i++) 
	{
		cout << "Testing image: ";
		cout << test_list[i] << endl;

		string testFolder = "test-images\\";
		string inputFilename = testFolder + test_list[i];

		Mat src = imread(inputFilename, IMREAD_ANYDEPTH);

		if (src.empty())
		{
			cout << "Could not open or find the image!\n" << endl;
			cout << "Usage: " << argv[0] << " <Input image>" << endl;
			return -1;
		}

		Mat dst;
		bool successVal;
		successVal = HistEqualization::equalize16Bit(src, dst);

		if (successVal)
		{
			cout << "IMAGE TEST SUCCESSFUL" << endl;
			successfulCounts++;
		}
		else
		{
			cout << "IMAGE TEST " << test_list[i] << " NOT SUCCESSFUL" << endl;
			errorCounts++;
			error_list.push_back(test_list[i]);
		}
		
	}
	
	//Summary
	cout << "###########" << endl;
	cout << "UNIT TEST SUMMARY:" << endl;
	cout << "Successful image test: [" << successfulCounts << "/" << test_list.size() << "]" << endl;
	cout << "Unsuccessful image test: [" << errorCounts << "/" << test_list.size() << "]" << endl;
	cout << "List of unsuccessful image test:" << endl;
	for (int i = 0; i < error_list.size(); i++)
		cout << error_list[i] << "\n";
	
	cout << endl << endl;
	cout << "Unit test done!" << endl;
	cout << "Press ENTER to quit" << endl;
	cin.get();
}

void removeSubstrs(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p);
		i != string::npos;
		i = s.find(p))
		s.erase(i, n);
}

