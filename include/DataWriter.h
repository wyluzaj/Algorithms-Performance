#ifndef AIZO_SORT_DATAWRITER_H
#define AIZO_SORT_DATAWRITER_H

#include <iostream>
#include <fstream>
#include <string>


//class to write an array to a file
template <typename T>
class DataWriter{
public:
    bool writeToFile(std::string& filename, T* data, int size){
        std::ofstream file(filename);
        if(!file.is_open()){
            std::cout << "Cannot open file" << filename << std::endl;
            return false;
        }
        file << size << "\n";
        for (int i = 0; i < size; i++){
            file << data[i] << "\n";
        }
        file.close();
        return true;
    }
};

#endif //AIZO_SORT_DATAWRITER_H
