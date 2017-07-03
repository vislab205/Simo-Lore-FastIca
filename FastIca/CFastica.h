/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFastica.h
 * Author: vislab
 *
 * Created on 3 luglio 2017, 15.12
 */

#ifndef CFASTICA_H
#define CFASTICA_H
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

class CFastica {
public:
    CFastica();
    CFastica(const CFastica& orig);
    virtual ~CFastica();
    
    void runFastica(cv::Mat &m);
    
    cv::Mat GetW();
    cv::Mat GetS();
    
private:
    
    void remean(cv::Mat input,cv::Mat & output);
    void remean(cv::Mat& input,cv::Mat& output,cv::Mat & mean);
    void whiten(cv::Mat input,cv::Mat &output);
    void whiten(cv::Mat input,cv::Mat &output,cv::Mat &E,cv::Mat &D);
    void runICA(cv::Mat input, cv::Mat &output,cv::Mat &W,int snum); 
    
    cv::Mat D,E,W,S;

};

#endif /* CFASTICA_H */

