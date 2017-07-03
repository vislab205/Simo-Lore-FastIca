/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFolderClassListFile.h
 * Author: vislab
 *
 * Created on 29 giugno 2017, 10.30
 */

#ifndef CFOLDERCLASSLISTFILE_H
#define CFOLDERCLASSLISTFILE_H
#include <dirent.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class CFolderClassListFile {
public:
    //Inizializzo l'oggeto con il percorso
    
    //Trova tutte le cartelle nella cartella passata
    // -name = indirizzo dove trovare il database separato in cartelle
    // - riempie un vettore di vettori con le stringhe per ogni cartella  vector<vector<string>> vectorAllFile;
    CFolderClassListFile(std::string name);
   
    CFolderClassListFile(const CFolderClassListFile& orig);
    
    virtual ~CFolderClassListFile();
    
    //restituisce il numero di cartelle trovare    
    int GetNumberClass();
   
    //restituisce il vettore con le stringhe delle cartelle
    std::vector<std::string> GetListClass();
    
    //ritorna un vettore di vettori con cartelle e file
    std::vector<std::vector<std::string>> getListFile();
    
private:
    
    std::vector<std::string> vectorDir;
    std::string mainFolder;
    int numberClass;
    std::vector<std::vector<std::string>> vectorAllFile;
    
};

#endif /* CFOLDERCLASSLISTFILE_H */

