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
    char mode = 'b';
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter video;
    

    std::cout << "Commande : \n b : mode de base\n p : pause\n m : afficher le mask\n h : afficher l'image en HSV\n";
    std::cout << " o : afficher les choux fleur une foi filtré\n q : quiter \n\n";

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        
        if(!video.isOpened()){
            video.open("out.mp4v",cv::VideoWriter::fourcc('x','v','i','d'),60, cv::Size(frame_width,frame_height));
            if(!video.isOpened()){
                std::cerr << "ERROR! can't create video writer\n";
                break;
            }
        }
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
        //cv::addWeighted(mask,1,frame,1,0, out);
        cv::bitwise_or( frame, frame, out, mask );

         switch(mode)
        {
            case 'b':
                cv::imshow("Frame", frame);
                video.write(frame);
                break;
            case 'm':
                cv::imshow("Frame", mask);
                video.write(mask);
                break;
            case 'h':
                cv::imshow("Frame", hsv);
                video.write(hsv);
                break;
            case 'o':
                cv::imshow("Frame", out);
                video.write(out);
                break;
            default:
                break;
        }

        char key = cv::waitKey(33);
        if (key == 27)
            break;
        if (key == 'p'){
            playVideo = !playVideo;
            if(playVideo)
                std::cout << "Pause <- off\n";
            else
                std::cout << "Pause <- on\n";
            }
        if (key == 'q')
            break;
        if (key == 'm'){
            mode = 'm';
            std::cout << "Mode :"<< mode <<"\n";
            }
        if (key == 'o'){
            mode = 'o';
            std::cout << "Mode :"<< mode <<"\n";
            }
        if (key == 'h'){
            mode = 'h';
            std::cout << "Mode :"<< mode <<"\n";
            }
        if (key == 'b'){
            mode = 'b';
            std::cout << "Mode :"<< mode <<"\n";
            }
    }
 
	cap.release();
    std::cout << "INFO Realease cap\n";
	video.release();
    std::cout << "INFO Realease video\n";
  // Closes all the frames
  	cv::destroyAllWindows();
    std::cout << "INFO Destroy all windows\n";
	//quiter le programme et fermer toutes les fenêtres ouvertes
	return 0;
}