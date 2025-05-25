
#ifndef AIZO_SORT_DATAFILE_H
#define AIZO_SORT_DATAFILE_H

#include <iostream>
#include "RandomData.h"
#include "DataWriter.h"

//generates a data file with random values of given type
//0 = int, 1 = float, 2 = double

void generateDataFile(std::string& filename, int size, int type) {
    if (type == 0) {
        RandomData<int> gen(size);
        DataWriter<int> writer;
        writer.writeToFile(filename, gen.getData(), gen.getSize());
    } else if (type == 1) {
        RandomData<float> gen(size);
        DataWriter<float> writer;
        writer.writeToFile(filename, gen.getData(), gen.getSize());
    } else if (type == 2) {
        RandomData<double> gen(size);
        DataWriter<double> writer;
        writer.writeToFile(filename, gen.getData(), gen.getSize());
    } else {
        std::cout << "Unknown data type (0=int, 1=float, 2=double)\n";
    }
}

#endif //AIZO_SORT_DATAFILE_H
