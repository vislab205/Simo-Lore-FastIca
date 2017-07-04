/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CBagOfWord.cpp
 * Author: vislab
 * 
 * Created on 28 giugno 2017, 10.29
 */
#include "CBagOfWord.h"
#include <dirent.h>
#include <vector>
#include <limits>
#include <fstream>

template<typename T>
static Ptr<T> load_classifier(const string& filename_to_load)
{
    // load classifier from the specified file
    Ptr<T> model = StatModel::load<T>( filename_to_load );
    if( model.empty() )
        cout << "Could not read the classifier " << filename_to_load << endl;
    else
        cout << "The classifier " << filename_to_load << " is loaded.\n";

    return model;
}


CBagOfWord::CBagOfWord(cv::Mat &features ,  int numeroParole)
{
    //Calcolo il numero di parole
    arrayDescriptor = features.clone();
    
    //Addestro il vocabolario
    TrainVocabolary(numeroParole);
}

CBagOfWord::CBagOfWord(const CBagOfWord& orig) {
}

CBagOfWord::~CBagOfWord() {
}

void CBagOfWord::TrainVocabolary(int n)
{
    cv::BOWKMeansTrainer vocabulary(n);
    
    numberWord =  n;
   
    try
    {
        vocabulary.add(arrayDescriptor);
                
        voc = vocabulary.cluster();
        
    }
    catch(cv::Exception e)
    {
        cout << e.err << endl;
    }
    
}

void CBagOfWord::SaveVocabolarity(string name)
{
    cv::FileStorage fs;

    std::string g = name + ".yml";
	
    fs.open(g,cv::FileStorage::WRITE);

    fs << "MatrixVocabolary" << voc;

    fs.release();
}

cv::Mat CBagOfWord::CalculateHist(cv::Mat& featuresImg )
{
    //recupero dimensione vettore features
    int lenght = featuresImg.cols;
    
    cv::Mat local;
    
    local = cv::Mat::zeros(1,numberWord ,CV_32FC1);
    
    float *raster = (float*)local.data;
    
    for(int i = 0; i < lenght ; i++)    {
        
        float min = std::numeric_limits<float>::max();
        
        int pos;
        
        for(int j = 0; j < numberWord ; j++)    {
        
            float dist = cv::norm(featuresImg , voc.row(j) , cv::NORM_L2);
            
            if(dist < min)  {
                min = dist;
                pos = j;
            }
                
        }
        
        raster[pos]++;
    }
    
    return local;
}

void CBagOfWord::AddHist(cv::Mat &hist, float index)
{
    arrayHist.push_back(hist);
    
    cv::Mat local(1,1,CV_32FC1);
    local.at<float>(0,0) = index;
    arrayIndex.push_back(local);
}

bool CBagOfWord::Train(int t)
{
    //recupero il numero di classi
    numberClass = arrayIndex.rows;
    
    Ptr<ml::TrainData> prova = ml::TrainData::create(arrayHist , SampleTypes::ROW_SAMPLE,arrayIndex);
    
    type = t;
    
    switch(type)
    {
        case 0:
            svm = SVM::create();
            return svm->trainAuto(prova);//train(arrayHist ,SampleTypes::ROW_SAMPLE ,arrayIndex);
            break;
        case 1:
            boost = Boost::create();
            return boost->train( arrayHist ,SampleTypes::ROW_SAMPLE ,arrayIndex);
            break;
        case 2:
            rTree = ml::RTrees::create();
            return rTree->train( arrayHist ,SampleTypes::ROW_SAMPLE ,arrayIndex);
            break;
        default:
            cout << "learning machine non selezionata..." << endl;
            return false;
    }
       
}

void CBagOfWord::SetClass(vector<string> nameClass)
{
    classi = nameClass;
}

int CBagOfWord::Predict(Mat hist)
{
    cv::Mat local;
    
    switch(type)
    {
        case 0:
            return svm->predict(hist , local );
            break;
        case 1:
            return boost->predict(hist , local );
            break;
        case 2:
            return rTree->predict(hist , local );
            break;
        default:
            cout << "learning machine non selezionata..." << endl;
            return -1;
    }
}

string CBagOfWord::PredictStr(Mat hist)
{
    cv::Mat local;
    
    float number;
    
    switch(type)
    {
        case 0:
            number =  svm->predict(hist , local );
            break;
        case 1:
            number = boost->predict(hist , local );
            break;
        case 2:
            number =  rTree->predict(hist , local );
            break;
        default:
            cout << "learning machine non selezionata..." << endl;
            return "error nothing selected classificator";
    }
    
    
    if(classi.size() == 0)   {
        return string("Vettore classi non riempito...valore trovato = ") + std::to_string(number);
    }
    
    return classi[(int)number];
}