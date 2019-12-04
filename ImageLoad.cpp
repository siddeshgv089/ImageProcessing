// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat image = imread("C:\\Users\\SIDDESH\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\module.jpg",1);
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	string windowName = "Image"; //Name of the window

	// Mat image(600, 800, CV_8UC3, Scalar(100, 250, 30)); creating a new color image

	namedWindow(windowName); // Create a window

	imshow(windowName, image); // Show our image inside the created window.

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName); //destroy the created window

	return 0;
}

