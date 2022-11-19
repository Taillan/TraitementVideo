//! @file   exple.cpp
//! @author P. FOUBERT
//! @brief  OpenCV project to show how to load and display an image

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <math.h>
#include <bitset>


#ifndef DATA_FOLDER
#define DATA_FOLDER
#endif

// ===========================================================================
//! @brief  Algorithme Proof of Concept
// ===========================================================================
void poc(){
    int n = 4;
    int p = 0;

    std::cout << "### Algorithme Proof of Concept ####" << std::endl;
    std::bitset<8> secret{"10001001"};
    std::bitset<8> cover_r{"10110111"};
    std::bitset<8> cover_g{"10010100"};
    std::bitset<8> cover_b{"11001001"};
    std::cout << "Byte of message to be inserted in LSB : " << secret << std::endl;
    std::cout << "RGB pixel value of the cover frame : " << std::endl;
    std::cout << "R : " << cover_r << std::endl;
    std::cout << "G : " << cover_g << std::endl;
    std::cout << "B : " << cover_b << std::endl;
    std::cout << "Hidding message ..." << std::endl;

    int k = p%n; // arbitrary offset depending of hiden image position to hardering the decryption 
    for(int l=0; l < 8; l++){
        int offset = (k+l)%n; // LSB bit postion within the pixel
        int bit_p = (3-offset)%n; // Inversing position to use most significant bit reference
        int secret_bit_p = (7-l)%8; // Inversing position to use most significant bit reference
        if(l < 3) cover_r.set(bit_p,secret[secret_bit_p]);
        else if(l < 6) cover_g.set(bit_p,secret[secret_bit_p]);
        else cover_b.set(bit_p,secret[secret_bit_p]);
    }

    std::cout << "RGB pixel value of the final frame : " << std::endl;
    std::cout << "R : " << cover_r << std::endl;
    std::cout << "G : " << cover_g << std::endl;
    std::cout << "B : " << cover_b << std::endl;
}


// ===========================================================================
//! @brief  encrypt
//! @return Encrypted Matrix of the cover Matrix with embed matrix within
// ===========================================================================
cv::Mat encrypt(cv::Mat cover, cv::Mat embed){

    cv::Mat encrypted = cover.clone();

    int n = 4;
    int p = 0;
    for(int i=0; i < embed.rows; i++){
        for(int j=0; j < embed.cols; j++){

            int secret_lsb = embed.at<cv::Vec3b>(i, j)[0];
            cv::Vec3b cover_rgb = cover.at<cv::Vec3b>(i, j);
            std::bitset<8> secret = std::bitset<8>(secret_lsb);
            std::bitset<8> cover_r = std::bitset<8>(cover_rgb[0]);
            std::bitset<8> cover_g = std::bitset<8>(cover_rgb[1]);
            std::bitset<8> cover_b = std::bitset<8>(cover_rgb[2]);
            int k = p%n; // arbitrary offset depending of hiden image position to hardering the decryption 

            for(int l=0; l < 8; l++){
                int offset = (k+l)%n; // LSB bit postion within the pixel
                int bit_p = (3-offset)%n; // Inversing position to use most significant bit reference
                int secret_bit_p = (7-l)%8; // Inversing position to use most significant bit reference
                if(l < 3) cover_r.set(bit_p,secret[secret_bit_p]);
                else if(l < 6) cover_g.set(bit_p,secret[secret_bit_p]);
                else cover_b.set(bit_p,secret[secret_bit_p]);
            }

            encrypted.at<cv::Vec3b>(i, j) = cv::Vec3b(cover_r.to_ulong(), cover_g.to_ulong(), cover_b.to_ulong());
            p++;
        }
    }

    return encrypted;
}


// ===========================================================================
//! @brief  decrypt
//! @return Decrypted Matrix with the embed Matrix shown
// ===========================================================================
cv::Mat decrypt(cv::Mat encrypted){
    
    cv::Mat decrypted = encrypted.clone();

    int n = 4;
    int p = 0;
    for(int i=0; i < encrypted.rows; i++){
        for(int j=0; j < encrypted.cols; j++){

            std::bitset<8> secret = std::bitset<8>();

            cv::Vec3b encrypted_rgb = encrypted.at<cv::Vec3b>(i, j);
            std::bitset<8> encrypted_r = std::bitset<8>(encrypted_rgb[0]);
            std::bitset<8> encrypted_g = std::bitset<8>(encrypted_rgb[1]);
            std::bitset<8> encrypted_b = std::bitset<8>(encrypted_rgb[2]);

            int k = p%n; // arbitrary offset depending of hiden image position to hardering the decryption 

            for(int l=0; l < 8; l++){
                int offset = (k+l)%n; // LSB bit postion within the pixel
                int bit_p = (3-offset)%n; // Inversing position to use most significant bit reference
                int secret_bit_p = (7-l)%8; // Inversing position to use most significant bit reference
                if(l < 3) secret.set(secret_bit_p, encrypted_r[bit_p]);
                else if(l < 6) secret.set(secret_bit_p, encrypted_g[bit_p]);
                else secret.set(secret_bit_p, encrypted_b[bit_p]);
            }

            decrypted.at<cv::Vec3b>(i, j) = cv::Vec3b(secret.to_ulong(), secret.to_ulong(), secret.to_ulong());
            p++;
        }
    }

    return decrypted;
}

// ===========================================================================
//! @brief  Main
//! @return <0 if error, 0 if success, >0 if warning
// ===========================================================================
int main() {
  
    poc();

    // Initialization

    cv::Mat opencv;
    cv::Mat lena;
    const std::string opencv_filename(DATA_FOLDER "opencv.jpg");
    const std::string lena_filename(DATA_FOLDER "lena.png");
    opencv = cv::imread(opencv_filename, cv::IMREAD_GRAYSCALE);
    lena = cv::imread(lena_filename, cv::IMREAD_COLOR);

    if(opencv.empty() || lena.empty()) {
        std::cout << "Cannot load images !" << std::endl;
        return -1;
    }

    // Encryption
    cv::Mat lena_encrypted;
    lena_encrypted = encrypt(lena, opencv);

    // Decryption
    cv::Mat lena_decrypted;
    lena_decrypted = decrypt(lena_encrypted);

    // Saving decrypted image
    cv::imwrite(DATA_FOLDER "lena_decrypted.png",lena_decrypted);

  
    // Showing images
    cv::namedWindow("lena", cv::WINDOW_AUTOSIZE);
    cv::imshow("lena", lena);

    cv::namedWindow("opencv_grey", cv::WINDOW_AUTOSIZE);
    cv::imshow("opencv_grey", opencv);

    cv::namedWindow("lena_decrypted", cv::WINDOW_AUTOSIZE);
    cv::imshow("lena_decrypted", lena_decrypted);

    // Waiting for the user to press ESC to exit
    cv::waitKey(0);

    return 0;
}
