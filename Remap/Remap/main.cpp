//
//  main.cpp
//  Remap --- 重映射
//
//  Created by ZHHJemotion on 2016/11/3.
//  Copyright © 2016年 Lukas_Zhang. All rights reserved.
//

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_RemapAndSURF/Remap/Remap/")

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //===================== small exercise =====================
    //定义变量
    Mat src, dst;
    Mat map_x,map_y;
    
    //载入原始图
    src = imread(PATH+string("1.jpg"),1);
    //异常处理
    if (!src.data)
    {
        std::cout<<"error: we cannot read the source image!!! \n";
        return false;
    }
    imshow("the source image", src);
    
    //创建和原始图一样的效果图，x重映射图，y重映射图
    dst.create(src.size(), src.type());
    map_x.create(src.size(), CV_32FC1);
    map_y.create(src.size(), CV_32FC1);
    
    //双层循环，遍历每一个像素点，改变map_x和map_y的值
    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            //改变map_x和map_y的值
            map_x.at<float>(j,i) = static_cast<float>(i);
            map_y.at<float>(j,i) = static_cast<float>(src.rows-j);
            // (i,j)表示的与(x,y)相反，且在 opencv 中原点在图的左上角
        }
    }
    
    //进行重映射操作
    remap(src, dst, map_x, map_y, CV_INTER_LINEAR);
    
    //显示效果图
    imshow("the result", dst);
    
    waitKey(0);
    
    
    return 0;
}
