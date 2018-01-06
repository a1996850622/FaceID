import cv2



if __name__ == "__main__":
	fn_csv='at.txt'

	images = []
	labels = []

	cv2.read_csv(fn_csv, images, labels)
