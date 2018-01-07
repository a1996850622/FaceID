#include <iostream>

#include<opencv2/face/facerec.hpp>
#include<opencv2/core.hpp>
#include<opencv2/face.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace cv;
using namespace cv::face;
using namespace std;

/** Print error message **/
void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

String face_cascade_name = "Source/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;

int main(void){
	Mat frame;
	Mat edges;
	Mat frame_gray;
	Mat face;
	Mat face_test;
	Point test_1b;
	vector<Rect> faces(0);
	bool stop = false;

	VideoCapture capture(0);

	if(!capture.isOpened())
		PANIC("Error open camera!");

	if(!face_cascade.load(face_cascade_name))
		PANIC("Error loading face cascade!");

	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->read("Source/MyFacePCAModel.xml");

	while(!stop){
		capture >> frame;

		cvtColor(frame, frame_gray, CV_BGR2GRAY);

		equalizeHist(frame_gray, frame_gray);

		face_cascade.detectMultiScale(frame_gray, faces, 1.05, 5, CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for(size_t i=0; i<faces.size(); i++){
			if(faces[i].height>0 && faces[i].width>0){
				face = frame_gray(faces[i]);
				test_1b = Point(faces[i].x, faces[i].y);

				rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
			}
		}
		
		int predictPCA = 0;
		if(face.rows >= 120)
			resize(face, face_test, Size(92, 112));

		if(!face_test.empty())
			predictPCA = model->predict(face_test);

		cout << predictPCA << endl;
		if(predictPCA == 40){
			string name = "WenYuanChen";
			putText(frame, name, test_1b, FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));
		}

		imshow("face", frame);
		if(waitKey(50) >= 0)
			stop = true;
	}

	return 0;
}