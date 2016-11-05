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
#define WINDOW_NAME "the window of destination"

using namespace cv;
using namespace std;

//----------------------- 全局变量声明 ------------------------
Mat srcImage, dstImage;
Mat mapX,mapY;

//----------------------- 全局函数申明 ------------------------
int updateMap(int key);
static void showHelpText();

//----------------------- main() function --------------------------
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
    //===============================================================
    
    //========================= 综合范例 =============================
    
    showHelpText(); //显示帮助文字
    
    //载入原始图
    srcImage = imread(PATH+string("1.jpg"),1);
    //异常处理
    if (!srcImage.data)
    {
        printf("error: we cannot read the source image! \n");
        return false;
    }
    imshow("the original image", srcImage);
    //创建窗口并显示
    namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, srcImage);
    
    //创建和原始图一样的效果图，x重映射图，y重映射图
    dstImage.create(srcImage.size(), srcImage.type());
    mapX.create(srcImage.size(), CV_32FC1);
    mapY.create(srcImage.size(), CV_32FC1);
    
    //轮询按键，更新mapX和mapY的值，进行重映射操作并显示效果图
    while (1)
    {
        //获得键盘按键
        int key = waitKey(0);
        
        //判断ESC是否按下，若按下便退出
        if ((key & 255) == 27)
        {
            cout << "程序退出...........\n";
            break;
        }
        
        //根据按下的键盘来更新mapX和mapY的值，然后调用remap()进行映射
        updateMap(key);
        remap(srcImage, dstImage, mapX, mapY, CV_INTER_LINEAR);
        
        //显示效果图
        imshow(WINDOW_NAME, dstImage);
    }
    
    
    return 0;
}


//------------------------ updateMap() function ----------------------------
//   根据按键来更新mapX和mapY的值
//--------------------------------------------------------------------------
int updateMap(int key)
{
    //双层循环，遍历每一个像素点
    for (int j = 0; j < srcImage.rows; j++)
    {
        for (int i = 0; i < srcImage.cols; i++)
        {
            switch(key)
            {
                case '1': //按键1表示向内收缩的重映射
                    if (i > srcImage.cols*0.25 && i < srcImage.cols*0.75 && j > srcImage.rows*0.25 && j < srcImage.cols*0.75)
                    {
                        mapX.at<float>(j,i) = static_cast<float>(2*(i-srcImage.cols*0.25)+0.5);
                        //mapY.at<float>(j,i) = static_cast<float>(2*(j-srcImage.rows*0,25)+0.5);
                    }
                    else
                    {
                        mapX.at<float>(j,i) = 0;
                        mapY.at<float>(j,i) = 0;
                    }
                    break;
                case '2': //按键2表示关于竖直方向对称
                    mapX.at<float>(j,i) = static_cast<float>(i);
                    mapY.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
                    break;
                case '3': //按键3表示关于水平方向对称
                    mapX.at<float>(j,i) = static_cast<float>(srcImage.cols - i);
                    mapY.at<float>(j,i) = static_cast<float>(j);
                    break;
                case '4': //按键4表示关于中心点对称
                    mapX.at<float>(j,i) = static_cast<float>(srcImage.cols - i);
                    mapY.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
                    break;
            }
        }
    }
    return true;
}


//-----------------------------------【showHelpText( )函数】----------------------------------
//      描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void showHelpText()
{
    //输出一些帮助信息
    printf("\n\n\n\t欢迎来到重映射示例程序~\n\n");
    //printf("\t当前使用的OpenCV版本为 OpenCV "CV_VERSION);
    std::cout<<"\t当前使用的OpenCV版本为 OpenCV"<<CV_VERSION;
    printf( "\n\n\t按键操作说明: \n\n"
           "\t\t键盘按键【ESC】- 退出程序\n"
           "\t\t键盘按键【1】- 表示向内收缩的重映射\n"
           "\t\t键盘按键【2】- 表示关于竖直方向对称\n"
           "\t\t键盘按键【3】- 表示关于水平方向对称\n"
           "\t\t键盘按键【4】- 表示关于中心点对称\n"
           "\n\n\t\t\t\t\t\t\t\t by ZHHJemotion\n\n\n"
           );
}
