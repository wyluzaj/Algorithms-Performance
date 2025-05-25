#ifndef AIZO_SORT_DATAREADER_H
#define AIZO_SORT_DATAREADER_H

#include <iostream>
#include <fstream>
#include <string>

//class to read data from a file into a dynamic array

template <typename T>
class DataReader{
private:
    T* data;     //pointer to dynamic array
    int size;    //number of elements

public:
    DataReader() {
        data = nullptr;
        size = 0;
    }
    ~DataReader() {
        delete[] data; //free allocated memory
    }
//reads file, 1st value - size, then elements
    bool readFromFile(std::string& filename){
        std::ifstream file(filename);
        if(!file.is_open()){
            std::cout << "Cannot open file" << filename << std::endl;
            return false;
        }
        file >> size; //read number of elements
         if (size <= 0){
             std::cout << "Empty:" << std::endl;
             file.close();
             return false;
         }
        data = new T[size]; // allocate array
         for (int i = 0; i < size; i++){
             file >> data[i];
         }
         file.close();
         return true;
    }

    int getSize() const {
        return size;
    }

    T *getData() const {
        return data;
    }

};

#endif //AIZO_SORT_DATAREADER_H
