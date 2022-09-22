//! @file   exple.cpp
//! @author P. FOUBERT
//! @brief  OpenCV project to show how to load and display an image

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>


#ifndef DATA_FOLDER
#define DATA_FOLDER
#endif

// ===========================================================================
//! @brief  Main
//! @return <0 if error, 0 if success, >0 if warning
// ===========================================================================
int main(int argc, char* argv[]) {
  int res(0);
  char input;
  const std::string filename(argv[1]);
  int angl=0;

  cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR/*IMREAD_GRAYSCALE*/);
  cv::Mat imgGRAY;
  cv::Mat imgGRAYrotated;
  cv::Mat rotMat;
  if(img.empty()) {
    std::cout << "Cannot load image \"" << filename << "\"!" << std::endl;
    res = -1;
  } else {
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", img);

    cv::namedWindow("imageGRAY2", cv::WINDOW_AUTOSIZE);
    cv::cvtColor(img,imgGRAY, cv::COLOR_BGR2GRAY);
    cv::imshow("imageGRAY2", imgGRAY);
    cv::imwrite("./imageGray.png",imgGRAY);

    input = static_cast<char>(cv::waitKey(0));

    while(input != 'e'){
      if('l' == input){
        angl -= 10;
      }
      if('r' == input){
        angl += 10;
      }
      rotMat = cv::getRotationMatrix2D( cv::Point2f( imgGRAY.cols / 2,imgGRAY.rows / 2  ),angl, 1.0 );
      cv::warpAffine(imgGRAY,imgGRAYrotated,rotMat,cv::Size(imgGRAY.cols,imgGRAY.rows));
      cv::imshow("imageGRAY2", imgGRAYrotated);
      input = static_cast<char>(cv::waitKey(0));
    }

  }
  return res;
}
