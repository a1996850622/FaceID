#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/** Print error message **/
void PANIC(char *msg);
#define PANIC(msg){perror(msg); exit(-1);}

int main(void){
	VideoCapture capture = VideoCapture(0);
	Mat frame, frame_gray;
	int i = 1;

	if(!capture.isOpened())
		PANIC("Error open camera");

	cout << "Press p to take a picture" << endl;
	while(1){
		char key = waitKey(100);
		capture >> frame;

		if(frame.empty())
            PANIC("Error capture frame");

		String filename = format("Picture/picture%d.jpg", i);

		/** Press p to take pictures **/
		switch(key){
			case 'p':
				i++;
				imwrite(filename, frame);
				imshow("photo", frame);
				waitKey(500);
				destroyWindow("photo");
				break;
			default:
				break;
		}
		imshow("frame", frame);
	}
}
