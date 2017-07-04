/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CBagOfWord.h
 * Author: vislab
 *
 * Created on 28 giugno 2017, 10.29
 */

#ifndef CBAGOFWORD_H
#define CBAGOFWORD_H



#include "opencv2/xfeatures2d.hpp"
#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <functional>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace cv::ml;
using namespace std;

class CBagOfWord {
public:
    
    enum{
        supportVector,
        boosting ,
        randomtree};
    
    /*Inizializza il bag of features
     * features = matrice che contiene per riga ongi singola features
     * numeroParole = numero di parole che si vogliono generare 
     */
    CBagOfWord(cv::Mat &features ,  int numeroParole = 50);

    CBagOfWord(const CBagOfWord& orig);
    
    virtual ~CBagOfWord();

    //Salvataggio del vocabolario
    // name = nome assegnato al vocabolario
    void SaveVocabolarity(string name);
    
    /*
     * Calcolo dell'istogramma
     * featuresImg = array di features passato
     * restituisce una mat di una riga per il numero di aprole
     */
    cv::Mat CalculateHist(cv::Mat &featuresImg);
       
    //Aggiunge l'istogramma calcolato ad una matrice privata che servirà
    //per l'addestramento
    void AddHist(cv::Mat &hist , float index);
    
    /*Addestramento del classificato
     * ci sono tre possibilità:
     *   1.supportVector,
     *   2.boosting
     *   3.randomtree(defaults)
     */
    bool Train(int type = randomtree);
    
    //Setta il nome delle classi
    void SetClass(vector<string> nameClass);
    
    //Effettua la predizione ritornando il numero della classe
    int Predict(cv::Mat hist);    
    
    //Ritorna il nome di appartenenza della classe
    string PredictStr(cv::Mat hist);
private:
    //Immagine che contiene i punti da trovare
    cv::Mat src;
 
    Mat arrayDescriptor ,voc;
    
    Mat arrayHist , arrayIndex;
    
    vector<string> vectorDir;
    vector<vector<string>> vectorAllFile;

    //Numero di classi presenti
    int numberClass;
    
    int numberWord;
    
    Ptr<SVM> svm;
    Ptr<RTrees> rTree;
    Ptr<Boost>  boost;
    
    vector<string> classi;
    
    int type;
    
    
    void TrainVocabolary(int numberWord = 50);
};

#endif /* CBAGOFWORD_H */

