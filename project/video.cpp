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
	cv::VideoCapture cap("./data/choux.mp4");
    bool playVideo = true;
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        
        if(playVideo)
            cap >> frame;

        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        cv::Mat hsv, mask, out;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
        cv::inRange(hsv, cv::Scalar(36, 25, 25), cv::Scalar(50, 255, 255), mask);
        cv::bitwise_and( frame, frame, out, mask );
        cv::imshow("Frame", frame);
        cv::imshow("Hsv", hsv);
        cv::imshow("Mask", mask);
        cv::imshow("Output", out);
        char key = cv::waitKey(1);
        if (key == 27)
            break;
        if (key == 'p')
            playVideo = !playVideo;
        if (key == 'q')
            break;
    }
	cap.release();
 
  // Closes all the frames
  	cv::destroyAllWindows();
	//quiter le programme et fermer toutes les fenêtres ouvertes
	return 0;
}