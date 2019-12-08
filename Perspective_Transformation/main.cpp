//
//  main.cpp
//  PerspectiveTransformation
//
//  Created by Shota Nishiyama on 2019/12/08.
//  Copyright © 2019 Shota Nishiyama. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

const int    WIDTH = 600;
const int    HEIGHT = 600;

#define INPUT_FILE "/Users/shotanishiyama/Desktop/HashimotoKanna.jpg"
int main(int argc, const char * argv[]) {
    
    cv::Mat src_img = cv::imread(INPUT_FILE);
    cv::Mat dst_img = cv::Mat::zeros(HEIGHT+100, WIDTH+100, CV_8UC3);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not found.\n");
        exit(0);
    }
    
      // 変換前の画像での座標
    const cv::Point2f src_pt[]={
        cv::Point2f(360 , 69 ),
        cv::Point2f(85  , 602),
        cv::Point2f(1032, 79 ),
        cv::Point2f(1198, 631)};
    
    // 変換後の画像での座標
    const cv::Point2f dst_pt[]={
        cv::Point2f(50,                 50           ),
        cv::Point2f(50,                 50+HEIGHT - 1),
        cv::Point2f(50+WIDTH - 1,       50           ),
        cv::Point2f(50+WIDTH - 1,       50+HEIGHT - 1)};
    
    const cv::Mat homography_matrix = getPerspectiveTransform(src_pt,dst_pt);
    // 透視変換
    warpPerspective(src_img, dst_img, homography_matrix, dst_img.size());
    
    
    
    cv::imshow("SRC",src_img);
    cv::imshow("Affine",dst_img);
    cv::waitKey();
       
    return 0;
}
