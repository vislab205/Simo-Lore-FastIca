/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: vislab
 *
 * Created on 3 luglio 2017, 15.16
 */
#include "CFastica.h"

int main()
{
    
   cv::Mat m1=(cv::Mat_<double>(4,3)<<1,5,3,4,0,6,1,8,9,100,11,12);
    
   CFastica obj;
 
   obj.runFastica(m1);
   
  
   return 0;
}
