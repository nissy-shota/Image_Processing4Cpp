//
//  main.cpp
//  Puff_ROI
//
//  Created by Shota Nishiyama on 2019/11/24.
//  Copyright © 2019 Shota Nishiyama. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_PATH "/Users/shotanishiyama/Puff_Project/puff_images/dirt_image/6.JPG"

int main(int argc, const char * argv[]) {
    
    int ITER = 0;
    while(ITER < 8){
        
    std::string dir_path = "/Users/shotanishiyama/Puff_Project/puff_images/dirt_image/";
    std::string file_number = std::to_string(ITER+1);
    std::string file_extension = ".JPG";
    std::string file_path = dir_path + file_number + file_extension;

    cv::Mat src_img = cv::imread(file_path,cv::IMREAD_GRAYSCALE);
    if (src_img.empty()) {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }
    cv::imshow("source image.",src_img);
    
    cv::Mat bin;
    cv::threshold(src_img, bin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    cv::Mat LabelImg;
    cv::Mat stats;
    cv::Mat centroids;
    
    
    int nLab = cv::connectedComponentsWithStats(bin, LabelImg, stats, centroids);
    
    // ラベリング結果の描画色を決定
    std::vector<cv::Vec3b> colors(nLab);
    colors[0] = cv::Vec3b(0, 0, 0);
    for (int i = 1; i < nLab; ++i) {
        colors[i] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
    }
    
    // ラベリング結果の描画
    cv::Mat Dst(src_img.size(), CV_8UC3);
    for (int i = 0; i < Dst.rows; ++i) {
        int *lb = LabelImg.ptr<int>(i);
        cv::Vec3b *pix = Dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < Dst.cols; ++j) {
            pix[j] = colors[lb[j]];
        }
    }
        
    cv::Mat Roi_img;
    for (int i = 1; i < nLab; ++i) {
        int *param = stats.ptr<int>(i);
        
        size_t bb_size = param[cv::ConnectedComponentsTypes::CC_STAT_AREA];
        std::cout << bb_size <<std::endl;
//        小さい領域を削除する．
        if (bb_size < 100) continue;
        
        int x = param[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
        int y = param[cv::ConnectedComponentsTypes::CC_STAT_TOP];
        int height = param[cv::ConnectedComponentsTypes::CC_STAT_HEIGHT];
        int width = param[cv::ConnectedComponentsTypes::CC_STAT_WIDTH];

        cv::rectangle(Dst, cv::Rect(x, y, width, height), cv::Scalar(0, 255, 0), 2);
           
        cv::Rect roi(x,y,width,height);
        Roi_img= src_img(roi);
           
    }
    
    cv::imshow("Src", src_img);
    cv::imshow("Labels", Dst);
    cv::imshow("ROI", Roi_img);
    cv::waitKey();
    
    std::string save_path = "/Users/shotanishiyama/Puff_Project/puff_images/output_d/" + std::to_string(ITER+1) + ".JPG";
    cv::imwrite(save_path, Roi_img);
    
     ITER++;
    }
    return 0;
}
