//
//  main.cpp
//  Pyramid
//
//  Created by Shota Nishiyama on 2019/12/08.
//  Copyright © 2019 Shota Nishiyama. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define INPUT_FILE "/Users/shotanishiyama/Desktop/HashimotoKanna.jpg"
int main(int argc, const char * argv[]) {
    cv::Mat src_img = cv::imread(INPUT_FILE);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not found.\n");
        exit(0);
    }
    cv::Mat down_img;
    cv::pyrDown(src_img,down_img);
    
    cv::Mat up_img;
    cv::pyrUp(down_img, up_img);
    
    
    std::vector<cv::Mat> build_pyramid_img;
    cv::buildPyramid(src_img, build_pyramid_img, 2);
    
    
    cv::imshow("SRC",src_img);
    cv::imshow("down img",down_img);
    cv::imshow("up img",up_img);
//    cv::waitKey();
//    heigh , width is 1/2
    
    cv::imshow("level0", build_pyramid_img[0]);
    cv::imshow("level1", build_pyramid_img[1]);
    cv::waitKey();
    
    return 0;
}
