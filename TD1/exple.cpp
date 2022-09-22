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
int main() {
  int res(0);
  const std::string filename(DATA_FOLDER "smarties.jpg");

  cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR/*IMREAD_GRAYSCALE*/);
  cv::Mat imgGRAY;
  if(img.empty()) {
    std::cout << "Cannot load image \"" << filename << "\"!" << std::endl;
    res = -1;
  } else {
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", img);
    cv::namedWindow("imageGRAY", cv::WINDOW_AUTOSIZE);
    cv::cvtColor(img,imgGRAY, cv::COLOR_BGR2GRAY);
    cv::imshow("imageGRAY", imgGRAY);
    cv::imwrite("./imageGray.png",imgGRAY);
    cv::waitKey(0);

  }
  return res;
}
