# 摄影测量-特征提取与影像匹配

The Program of image feature extraction and matching (Photogrammetry).

This is a Homework of Course Photogrammetry in Wuhan University.

武大遥感院摄影测量学作业-特征提取与影像匹配

`@date：2021.11.14` `@language：C++`

### Install & Usage:

- C++ 

  - Pre-requisite:`OpenCV 4.5.4`

**注意：此程序运行需先预先安装OpenCV库！本仓库已移除！**

**Attention：OpenCV is needed ! The repository is not included !**

### Method:

- Feature Extraction:**Moravec operator** (使用Moravec算子特征提取)
- Matching:**Correlation-based image matching** (使用基于相关系数的影像匹配)

**原理：**

**[特征提取影像匹配.xmind](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/%E7%89%B9%E5%BE%81%E6%8F%90%E5%8F%96%E5%BD%B1%E5%83%8F%E5%8C%B9%E9%85%8D.xmind)**

**[报告.pdf](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/%E6%8A%A5%E5%91%8A.pdf)**

## 项目文件:

##### 数据：

- **[RawImage](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/tree/main/RawImage)**

  > RawImage：Left Image & Right Image（.tif&.bmp can be used)
  >
  > (Please modify the path by yourself when inputing)
  >
  > 影像：左影像和右影像提供..tif和.bmp格式使用(读取时请自行修改路径)

##### 代码：

- **[FeatureExtraction.cpp](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/FeatureExtraction.cpp)**

  > main
  >
  > main函数

- **[ImageSolution.h](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/ImageSolution.h)**/**[ImageSolution.cpp](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/ImageSolution.cpp)**

  > Class of ImageSolution For Image Feature Extraction And Matching
  >
  > 类：进行读取图片、特征提取、影像匹配

- **[tic_toc.h](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/tic_toc.h)**

  > Timer
  >
  > 一个计时器

- **[进度条.cpp](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/%E8%BF%9B%E5%BA%A6%E6%9D%A1.cpp)**/**[进度条.h](https://github.com/Raymond1030/WHURS-Photogrammetry-FeatureExtractionAndMatching/blob/main/Code/FeatureExtractionAndMatching/%E8%BF%9B%E5%BA%A6%E6%9D%A1.h)**

  > Progress bar
  >
  > 显示在控制台的进度条
