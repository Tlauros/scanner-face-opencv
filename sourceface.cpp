#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <stdio.h>
#include <windows.h> // For Sleep
using namespace std;
using namespace cv;


/////// tabe tashkhis sortat
CascadeClassifier face_cascade;
void faceDetection(Mat frame)
{
	// fream webcam ro taqviyat mikone
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	flip(frame, frame, 1);
	// tashkhis sorat
	vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);
	for (size_t i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 6);
		Mat faceROI = frame_gray(faces[i]);
		flip(frame, frame, 1);
	}
	
	//panjereyi ke webcam baz mishe va anjm be tashkhis sorat anjm mide
	imshow("live face detection", frame);
}

// yeseri tabe baraye ax gereftan
int ct = 0;
char tipka;
char filename[100]; // For filename
int  c = 1; // For filename

// xml tashkhis sortar
int main(int, char**)
{
	string faceClassifier = "E:/opencv/opencv-4.5.5/data/haarcascades/haarcascade_frontalface_alt.xml";
	if (!face_cascade.load(faceClassifier))
	{
		cout << "could not open xml file";
		return -1;
	}

	VideoCapture capture(0);

	if (!capture.isOpened())
	{
		cout << "could not open webcam";
		return -1;
	}
	Mat frame;
	while (capture.read(frame))
	{
		if (frame.empty())
		{
			cout << "no frame captured from camera";
			break;
		}
		// bastane panjare
		faceDetection(frame);
		if (waitKey(10) == 'k')
		{
			break;
		}
		//ax gereftan
		tipka = waitKey(30);
		if (tipka == 'q') {
			// dar qesmate file name shoma bayad ye file be esme takepic dorost konid ta ax ha onja sabt beshe
			sprintf_s(filename, "E:/takepic/Frame_%d.jpg", c); // select your folder - filename is "Frame_n"
			imwrite(filename, frame);
			cout << "Frame_" << c << endl;
			c++;
		}
	}

	return 0;
}
