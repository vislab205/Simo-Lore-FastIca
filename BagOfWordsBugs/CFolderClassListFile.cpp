/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFolderClassListFile.cpp
 * Author: vislab
 * 
 * Created on 29 giugno 2017, 10.30
 */

#include "CFolderClassListFile.h"

CFolderClassListFile::CFolderClassListFile(string name) {
    
    mainFolder = name;
    
    DIR *dir = opendir(name.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR)
            if(string(entry->d_name).find("."))
                vectorDir.push_back(string(entry->d_name));

        entry = readdir(dir);
    }

    closedir(dir);
    
    numberClass = vectorDir.size();
    
    for(int i = 0 ;i < numberClass ;i++)
    {
        //Ora trovo tutti i file nelle varie cartelle
        DIR           *d;
        struct dirent *dir2;
        d = opendir((name + vectorDir[i]).c_str());

        vector<string> localString;

        if (d)
        {
          while ((dir2 = readdir(d)) != NULL)
          {
              if(string(dir2->d_name).find("."))
                  localString.push_back(name + vectorDir[i] +"/" +string(dir2->d_name));
          }
          closedir(d);
        }

        vectorAllFile.push_back(localString);
    }
}

CFolderClassListFile::CFolderClassListFile(const CFolderClassListFile& orig) {
}

CFolderClassListFile::~CFolderClassListFile() {
}

int CFolderClassListFile::GetNumberClass()
{
    return numberClass;
}

vector<string> CFolderClassListFile::GetListClass()
{
    return vectorDir;
}

vector<vector<string>> CFolderClassListFile::getListFile()
{
    return vectorAllFile;
}