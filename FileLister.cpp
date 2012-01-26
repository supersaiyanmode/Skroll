#include <iostream>
#include <sstream>
#include <dirent.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "FileLister.h"

bool endsWith(std::string const &fullString, std::string const &ending){
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::vector<std::string> split(const std::string& str, char split){
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    std::string item;
    while (std::getline(ss,item,split)){
        tokens.push_back(item);
    }
    return tokens;
}

FileLister::FileLister(const std::string& base, const std::string& f): baseDir(base){
    endsWithArr = split(f, '|');
}

std::vector<std::string> FileLister::list(){
    std::vector<std::string> files;
    struct dirent **nameList;
    int numberOfFiles;

    numberOfFiles = scandir(baseDir.c_str(), &nameList, 0, 0);

    if (numberOfFiles > 0){
        while (numberOfFiles--){
            if (std::strcmp(nameList[numberOfFiles]->d_name, ".")  &&
                            std::strcmp(nameList[numberOfFiles]->d_name, "..")){
                for (std::vector<std::string>::iterator it=endsWithArr.begin(); it!= endsWithArr.end();
                                            it++){
                    if (endsWith(nameList[numberOfFiles]->d_name,*it)){
                        std::cout<<"Found: "<<nameList[numberOfFiles]->d_name<<std::endl;
                        files.push_back(nameList[numberOfFiles]->d_name);
                        break;
                    }
                }
                std::free(nameList[numberOfFiles]);
            }
        }
        std::free(nameList);
    }
    std::cout<<"Returned "<<files.size()<<std::endl;
    return files;
}
