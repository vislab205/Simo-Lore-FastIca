#include <cstdlib>
#include "lbp.hpp"
#include "histogram.hpp"
#include "CFolderClassListFile.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {

   CFolderClassListFile folder("/home/vislab/NetBeansProjects/Bugs/Difetti Sistema 1/"); 
   
   vector<vector<string>> dir = folder.getListFile();
   
   //Raggio di ricerca
   int radius = 1;
   //Numero di vicini
   int neighbors = 8;
   cv::Mat lbp , frame,dst;
   
   for(int i = 0 ; i < dir.size() ; i++)
   {
       for(int j = 0; j < dir[i].size() ; j++)  {
           
           frame = imread(dir[i][j]);
           
           cvtColor(frame, dst, CV_BGR2GRAY);
           GaussianBlur(dst, dst, Size(7,7), 5, 3, BORDER_CONSTANT);
           
           lbp::ELBP(dst, lbp, radius, neighbors);
           
           normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);
           
           cv::imshow("prova" , lbp);
           cv::imshow("hist" , hist);
           cv::waitKey();     
       }
   }
    
   
   return 0;
}

