//
//  main.cpp
//  SURF&FeatureDetection --- SURF特征点检测
//
//  Created by ZHHJemotion on 2016/11/3.
//  Copyright © 2016年 Lukas_Zhang. All rights reserved.
//

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <string>

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_RemapAndSURF/SURF&FeatureDetection/SURF&FeatureDetection/")

using namespace cv;
using namespace std;

//--------------------------- 全局函数申明部分 --------------------------
//  全局函数申明
//--------------------------------------------------------------------
static void showHelpText(); //输出帮助文字


//--------------------------- main() function -----------------------------

int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //显示帮助文字
    showHelpText();
    
    //载入源图片
    Mat srcImage1 = imread(PATH+string("1.jpg"),1);
    Mat srcImage2 = imread(PATH+string("2.jpg"),1);
    //异常处理
    if (!srcImage1.data || !srcImage2.data)
    {
        printf("error: we cannot read the source image!!! please check if it is effective!!! \n");
        return false;
    }
    //显示源图像
    namedWindow("the original image 1");
    namedWindow("the original image 2");
    imshow("the original iamge 1", srcImage1);
    imshow("the original image 2", srcImage2);
    
    //定义需要用到的变量和类
    int minHessian = 400; //定义 SURF 中的 hessian 阈值特征点检测算子
    SurfFeatureDetector detector(minHessian); //定义一个 SurfFeatureDetector(SURF)特征检测类对象
    std::vector<KeyPoint> keyPoints1, keyPoints2; //vector 模板类是能够存放任意类型的动态数组，能够增加和减少数据
    
    //调用detect函数
    detector.detect(srcImage1, keyPoints1);
    detector.detect(srcImage2, keyPoints2);
    
    //绘制特征点
    Mat imgKeyPoint1, imgKeyPoint2;
    drawKeypoints(srcImage1, keyPoints1, imgKeyPoint1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImage2, keyPoints2, imgKeyPoint2);
    
    //显示效果图
    imshow("the destination image 1", imgKeyPoint1);
    imshow("the destination image 2", imgKeyPoint2);
    
    waitKey(0);
    
    return 0;
}


//-----------------------------------【showHelpText( )函数】----------------------------------
//          描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void showHelpText()
{
    //输出一些帮助信息
    printf("\n\n\n\t欢迎来到【SURF特征点检测】示例程序~\n\n");
    //printf("\t当前使用的OpenCV版本为 OpenCV "CV_VERSION);
    std::cout<<"\t当前使用的OpenCV版本为 OpenCV"<<CV_VERSION;
    printf( "\n\n\t按键操作说明: \n\n"
           "\t\t键盘按键任意键- 退出程序\n\n"
           "\n\n\t\t\t\t\t\t\t\t byZHHJemotion\n\n\n");
    
}
