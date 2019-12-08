//
//  main.cpp
//  AffineTransform
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
    cv::Point2f center = cv::Point2f(
           static_cast<float>(src_img.cols / 2),
           static_cast<float>(src_img.rows / 2));
    
    double degree = 60.0;  // 回転角度
    double scale = 1.0;    // 拡大率
    
    cv::Mat dst_img = src_img.clone();
    
    cv::Mat affine;
    
    //2次元回転を表すアフィン変換を求めます．
    cv::getRotationMatrix2D(center, degree, scale).copyTo(affine);
    
    //画像のアフィン変換を行います．
    cv::warpAffine(src_img, dst_img, affine, src_img.size(), cv::INTER_CUBIC);
    
    cv::imshow("SRC",src_img);
    cv::imshow("Affine",dst_img);
    cv::waitKey();
    
    return 0;
}
