#include"opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{

	Mat image = imread("C:\\Users\\SIDDESH\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\module.jpg");

	// Check for failure
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}


	bool isSuccess = imwrite("C:\\Users\\SIDDESH\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\Newmodule.jpg", image); //write the image to a file as JPEG 
	//bool isSuccess = imwrite("D:/MyImage.png", image); //write the image to a file as PNG
	if (isSuccess == false)
	{
		cout << "Failed to save the image" << endl;
		cin.get(); //wait for a key press
		return -1;
	}

	cout << "Image is succusfully saved to a file" << endl;

	String windowName = "The Saved Image"; //Name of the window
	namedWindow(windowName); // Create a window
	imshow(windowName, image); // Show our image inside the created window.

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName); //destroy the created window

	return 0;
}