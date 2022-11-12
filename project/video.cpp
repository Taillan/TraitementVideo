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
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cv::VideoWriter video;
    bool playVideo = true;
    char mode = 'b';
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);

    

    std::cout << "Commande : \n b : mode de base\n p : pause\n m : afficher le mask\n h : afficher l'image en HSV\n";
    std::cout << " o : afficher les choux fleur une foi filtré\n q : quiter \n\n";

    for (;;)
    {
        //Ouverture du fichier video d'output
        if(!video.isOpened()){
            video.open("out.avi",cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),60, cv::Size(frame_width,frame_height));
            if(!video.isOpened()){
                //si celuio ci ne souvre pas correctement c'est une erreur
                std::cerr << "ERROR! can't create video writer\n";
                break;
            }
        }
        // si la vidéo n'est pas en pause on lit la frame suivante
        if(playVideo){
            cap >> frame;
        }

        //si cette frame est vide alors la video est soit fini soit cest une erreur donc on coupe la boucle
        if (frame.empty()) {
            std::cerr << "frame_count : "<<frame_count<< " frame_number : "<<cap.get(cv::CAP_PROP_POS_FRAMES)<<std::endl;
            if(frame_count == cap.get(cv::CAP_PROP_POS_FRAMES)){
                break;
            }
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        cv::Mat hsv, mask, out;
        // convertion de l'image en HSV pour pouvoir appliquer un filtre plus efficace
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
        //conservation des pixel compris dans le range [HSV(35,25,25),HSV(50,255,255)]  
        cv::inRange(hsv, cv::Scalar(36, 25, 25), cv::Scalar(50, 255, 255), mask);
        //Application d'un or pour ne garder les pixel que des choux avec leur couleur dorigine
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