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

int Alpha;
int Beta;
cv::Mat img ;


static void on_trackbar( int, void* userdata )
{
   cv::Mat dest;

   dest = (Alpha) * img + cv::Scalar::all(Beta);

   cv::imshow("image", dest);
}


int main() {
  int res(0);
  const std::string filename(DATA_FOLDER "smarties.jpg");

  img= cv::imread(filename, cv::IMREAD_COLOR/*IMREAD_GRAYSCALE*/);
  cv::Mat imgGRAY;
  if(img.empty()) {
    std::cout << "Cannot load image \"" << filename << "\"!" << std::endl;
    res = -1;
  } else {
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar( "contrast", "image", &Alpha, 100, on_trackbar );
    cv::createTrackbar( "Luminosite", "image", &Beta, 100, on_trackbar );
    cv::imshow("image", img);
    cv::waitKey(0);

  }
  return res;
}
