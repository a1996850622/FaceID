#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <math.h>  

#include<opencv2/face/facerec.hpp>
#include<opencv2/core.hpp>
#include<opencv2/face.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace cv;
using namespace cv::face;
using namespace std;

/* Used to normalize the source image */
static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	Mat dst;

	switch (src.channels()) {
		case 1:
			normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
			break;
		case 3:
			normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
			break;
		default:
			src.copyTo(dst);
			break;
	}

	return dst;
}

/* Used to read and handle the CSV format file */
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	ifstream file(filename.c_str(), ifstream::in);

	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}

	string line, path, classlabel;

	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);

		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}


int main(void){
	/* The name of your CSV format file */
	string fn_csv = "att_faces/at.txt";

	/* Two containers to store the image data and the corresponding label */
	vector<Mat> images;
	vector<int> labels;
	
	/* Read the CSV format file */
	try{
		read_csv(fn_csv, images, labels);
	} catch (Exception& e){
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		exit(-1);
	}

	/* Quit if it hasn't read enough pictures */
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}

	/* Remove the last photo from the data set because we want to use it as a test sample */ 
	Mat testSample = images[images.size() - 1];
	int testLabel = labels[labels.size() - 1];
	images.pop_back();
	labels.pop_back();

	/* Create the following three features model to apply to face recognition */
	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels);
	model->save("Source/MyFacePCAModel.xml");

	Ptr<FisherFaceRecognizer> model1 = FisherFaceRecognizer::create();
	model1->train(images, labels);
	model1->save("Source/MyFaceFisherModel.xml");

	Ptr<LBPHFaceRecognizer> model2 = LBPHFaceRecognizer::create();
	model2->train(images, labels);
	model2->save("Source/MyFaceLBPHModel.xml");

	/* Predict the test image. And the predictedLabel is the result of predictive labeling */ 
	int predictedLabel = model->predict(testSample);
	int predictedLabel1 = model1->predict(testSample);
	int predictedLabel2 = model2->predict(testSample);

	/* Print the result of prediction */
	string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
	string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
	string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
	cout << result_message << endl;
	cout << result_message1 << endl;
	cout << result_message2 << endl;

	/* Wait for any key */
	getchar();
	// waitKey(0);

	return 0;
}