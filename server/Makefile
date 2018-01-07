all: att_faces/at.txt FaceRecognition Photogragh Train

att_faces/at.txt: CSV.py
	python3 CSV.py
FaceRecognition: FaceRecognition.cpp
	g++ FaceRecognition.cpp -o FaceRecognition `pkg-config --cflags --libs opencv`
Photogragh: Photogragh.cpp
	g++ Photogragh.cpp -o Photogragh `pkg-config --cflags --libs opencv`
Train: Train.cpp
	g++ Train.cpp -o Train `pkg-config --cflags --libs opencv`
clean:
	rm *.o FaceRecognition Photogragh Train
