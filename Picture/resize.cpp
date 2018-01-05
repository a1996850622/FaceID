/** g++ resize.cpp -o resize `pkg-config --cflags --libs opencv` **/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;

/** Print error message **/
void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

/** Gloabal variables **/
String face_cascade_name = "../Source/haarcascade_frontalface_default.xml";
String eyes_cascade_name = "../Source/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade; // Define the face classifier
CascadeClassifier eyes_cascade; // Define the eyes classifier

int main(int argc, char *argv[]){
	Mat image_gray;
	std::vector<Rect> faces;

	if(argc<2){
		printf("Please enter the filename of picture\n");
		printf("eg: ./resize picture.jpg 1.jpg\n");
		exit(-1);
	}

	char *filename = argv[1];
	char *output = argv[2];

	if (!face_cascade.load(face_cascade_name)) 
		PANIC("Error loading face cascade");
	if (!eyes_cascade.load(eyes_cascade_name))
		PANIC("Error loading eyes cascade");

    Mat image = imread(filename, IMREAD_COLOR);

    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    equalizeHist(image_gray, image_gray);

    // Detect faces of different sizes using cascade classifier 
    face_cascade.detectMultiScale(image_gray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for (size_t j = 0; j < faces.size(); j++){
        Mat faceROI = image(faces[j]);
        Mat MyFace;

        if (faceROI.cols > 100){
            resize(faceROI, MyFace, Size(92, 112));
            imwrite(output, MyFace);
            imshow("ii", MyFace);
            cout << MyFace.cols << ", " << MyFace.rows << endl;
        }
        waitKey(10);
    }

    return 0;
}
