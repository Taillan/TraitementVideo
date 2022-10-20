#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <string>
#include <math.h>

#ifndef DATA_FOLDER
#define DATA_FOLDER
#endif

int main() {

    cv::Mat frame;
  	const std::string filename(DATA_FOLDER "choux.mp4");
	cv::VideoCapture cap("data/choux.mp4");

    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap >> frame;
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        cv::imshow("Frame", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }
	cap.release();
 
  // Closes all the frames
  	cv::destroyAllWindows();
	//quiter le programme et fermer toutes les fenêtres ouvertes
	return 0;
}