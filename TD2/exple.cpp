//! @file   exple.cpp
//! @author P. FOUBERT
//! @brief  OpenCV project to show how to load and display an image

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <math.h>


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

  int font = cv::FONT_HERSHEY_SIMPLEX;
  img= cv::imread(filename, cv::IMREAD_COLOR/*IMREAD_GRAYSCALE*/);
  cv::Mat imgGRAY;
  cv::Mat imgFiltred;
  std::vector<cv::Vec3f>circles;
  
  if(img.empty()) {
    std::cout << "Cannot load image \"" << filename << "\"!" << std::endl;
    res = -1;
  } else {
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("circle", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar( "contrast", "image", &Alpha, 100, on_trackbar );
    cv::createTrackbar( "Luminosite", "image", &Beta, 100, on_trackbar );
    cv::imshow("image", img);

    cv::cvtColor(img,imgGRAY, cv::COLOR_BGR2GRAY);
    cv::threshold(imgGRAY,imgFiltred,240,255, cv::THRESH_BINARY);  
    
    cv::HoughCircles(imgGRAY,circles,cv::HOUGH_GRADIENT,1,
                    imgGRAY.rows/16,
                    100,30,1,30);
    
    for( size_t i = 0; i < circles.size(); i++ ){
      cv::Vec3i c =circles[i];
      cv::Point center = cv::Point(c[0],c[1]);
      int radius = c[2];
      cv::circle( img, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
    }
    cv::putText(img, "Nb Circle = "+std::to_string(circles.size()), cv::Point(0,30), font, 1, (0, 255, 0), 2, cv::LINE_AA);
    cv::imshow("circle", img);
    cv::waitKey(0);

  }
  return res;
}
