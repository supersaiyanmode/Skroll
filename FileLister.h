#ifndef FILE_LISTER_H
#define FILE_LISTER_H

#include <string>
#include <vector>

class FileLister{
public:
    FileLister(const std::string&, const std::string&);
    
    std::vector<std::string> list();
private:
    bool recursive;
    std::string baseDir;
    std::vector<std::string> endsWithArr;
    int count;
};


#endif