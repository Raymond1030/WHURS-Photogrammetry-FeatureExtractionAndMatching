// FeatureExtractionAndMatching.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/core/utils/logger.hpp> //opencv日志

#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#include"ImageSolution.h"
#define corner_threshol 700 //Moravec特征提取预设阈值
#define corr_window_size 25    // 相关系数匹配窗口大小
#define corr_threshold  0.85 // 相关系数匹配阈值
int main()
{
    cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);//不再输出opencv日志

    ImageSolution M;
    M.ReadImg();
 
    TicToc t = TicToc();
   
    t.tic();
    FeatureExtraction T1(M.leftImg);
    T1.SetThreshol(corner_threshol); T1.MoravecGetFuature();
    double time=t.toc();
    cout << "左图使用Moravec算子进行特征提取，阈值设置为" << T1.c_threshol<<endl;
    cout << "特征点有" << T1.numFE<<"个" << endl;
    cout << "用时：" << time << "秒\n" << endl;

    t.tic();
    FeatureExtraction T2(M.rightImg);
    T2.SetThreshol(corner_threshol); T2.MoravecGetFuature();
    time = t.toc();
    cout << "右图使用Moravec算子进行特征提取，阈值设置为" << T2.c_threshol << endl;
    cout << "特征点有" << T2.numFE << "个" << endl;
    cout << "用时：" << time << "秒\n" << endl;

    T1.WriteFeature("左图特征点.txt");//只输出特征点
    T2.WriteFeature("右图特征点.txt");
    imshow("左图特征提取后",T1.FeatureImg);
    imshow("右图特征提取后", T2.FeatureImg);
    waitKey(0);
    imwrite("左图特征提取.jpg", T1.FeatureImg);
    imwrite("右图特征提取.jpg", T2.FeatureImg);

    t.tic();
    ImageMatching K(T1, T2);
    K.setWindowSize(corr_window_size);
    K.setThreshold(corr_threshold);
    K.Matching();
    K.drawMatches();
    time = t.toc();
    cout << "使用基于相关的影像匹配,窗口设置大小为" << K.windowSize << "\t阈值为" << K.threshold << endl;
    cout << "相关系数匹配到同名点：" << K.matches.size() << endl;
    cout << "用时" << time << "秒\n";
    imshow("基于相关系数的影像匹配", K.outputImg);
    waitKey(0);
    imwrite("基于相关系数的影像匹配.jpg", K.outputImg);
    return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
