/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFastica.cpp
 * Author: vislab
 * 
 * Created on 3 luglio 2017, 15.12
 */

#include "CFastica.h"

CFastica::CFastica() {
}

CFastica::CFastica(const CFastica& orig) {
}

CFastica::~CFastica() {
}

void CFastica::remean(cv::Mat input,cv::Mat & output)
{
   cv::Mat mean;
   cv::reduce(input,mean,0,CV_REDUCE_AVG);
   cv::Mat temp = cv::Mat::ones(input.rows, 1, CV_64FC1);
   output=input-temp*mean;
   
}


void CFastica::remean(cv::Mat& input,cv::Mat& output,cv::Mat & mean)
{
   
   cv::reduce(input,mean,0,CV_REDUCE_AVG);
   cv::Mat temp = cv::Mat::ones(input.rows, 1, CV_64FC1);
   output=input-temp*mean;
   
}


void CFastica::whiten(cv::Mat input,cv::Mat &output)
{
// need to be remean before whiten	

const int N=input.rows;  //num of data
const int M=input.cols;  //dimention	
    
 cv::Mat cov;
 cv::Mat D;
 cv::Mat E;
 cv::Mat temp=cv::Mat::eye(M,M,CV_64FC1);
 cv::Mat temp2;
 
 cov=input.t()*input/N;
 cv::eigen(cov,D,E);
 cv::sqrt(D,D);
 
 for(int i=0;i<M;i++)
 { temp.at<double>(i,i)=D.at<double>(i,0);}
 
 temp2=E*temp.inv()*E.t()*input.t();
 
 
output=temp2.t();
 

} 
 
 
void CFastica::whiten(cv::Mat input,cv::Mat &output,cv::Mat &E,cv::Mat &D)
{
 // need to be remean before whiten	

const int N=input.rows;  //num of data
const int M=input.cols;  //dimention	
    
 cv::Mat cov;
 cv::Mat D2;
 cv::Mat temp=cv::Mat::eye(M,M,CV_64FC1);
 cv::Mat temp2;
 cv::Mat E2;

 cov=input.t()*input/N;
 cv::eigen(cov,D,E2);
 cv::sqrt(D,D2);
 E=E2.t();

 for(int i=0;i<M;i++)
 { temp.at<double>(i,i)=D2.at<double>(i,0);}
 
   temp2=E2*temp.inv()*E2.t()*input.t();
 
 
  output=temp2.t();
 } 	 
 


void CFastica::runICA(cv::Mat input, cv::Mat &output,cv::Mat &W,int snum)     //output =Independent components matrix,W=Un-mixing matrix
 {      
       const  int M=input.rows;    // number of data
        const  int N=input.cols;    // data dimension
	
        const int maxIterations=1000;
        const double epsilon=0.0001;
        
        if(N<snum)
        { snum=M;
          printf(" Can't estimate more independent components than dimension of data ");}
       
       cv::Mat R(snum,N,CV_64FC1);
       cv::randn(R, cv::Scalar(0), cv::Scalar(1));
       cv::Mat ONE=cv::Mat::ones(M,1,CV_64FC1);
    
	   for(int i=0;i<snum;++i)
       {
         int iteration=0;
         cv::Mat P(1,N,CV_64FC1);
         R.row(i).copyTo(P.row(0));
               
          while(iteration<=maxIterations)
          { 
            iteration++;
           	cv::Mat P2;
			P.copyTo(P2);
           	cv::Mat temp1,temp2,temp3,temp4;
           	temp1=P*input.t();
           	cv::pow(temp1,3,temp2);
           	cv::pow(temp1,2,temp3);
           	temp3=3*temp3;
           	temp4=temp3*ONE;
           	P=temp2*input/M-temp4*P/M;
                      
            if(i!=0)
           {
			 cv::Mat temp5;
			 cv::Mat wj(1,N,CV_64FC1);
			 cv::Mat temp6=cv::Mat::zeros(1,N,CV_64FC1);			
			
			 for(int j=0;j<i;++j)
			 {
				R.row(j).copyTo(wj.row(0));
				temp5=P*wj.t()*wj;				
				temp6=temp6+temp5;
			    
			 }
			 P=P-temp6;
	     	}
			 double Pnorm=cv::norm(P,4);
                         P=P/Pnorm;	
			 
			 double j1=cv::norm(P-P2,4);
			 double j2=cv::norm(P+P2,4);
             if(j1<epsilon || j2<epsilon)
             {  
	            P.row(0).copyTo(R.row(i));
	            break;
	          }
	          else if( iteration==maxIterations)
	          {
				  P.row(0).copyTo(R.row(i));
			  }
            }
          }
          output=R*input.t();
          W=R;
  }        


cv::Mat CFastica::runFastica(cv::Mat& m1)
{   
   //
   remean(m1,m1);
   
    whiten(m1,m1,E,D);
   
   runICA(m1,S,W,m1.cols);
   
   cout<<W<<endl;
   cout<<S<<endl;

   return W;
   
}



