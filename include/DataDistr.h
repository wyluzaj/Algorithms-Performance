#ifndef AIZO_SORT_DATADISTR_H
#define AIZO_SORT_DATADISTR_H

#include <algorithm>
#include "Sort.h"
#include <iostream>

//template class to prepare an array based on specified distribution
//1 - sort asc
//2 - sort desc
//3 - sort 1/3
//4 - sort 2/3

template <typename T>
void prepareData(T* data, int size, int distribution){
    Sort<T> sorter;
    std::string alg = "QS"; // quick sort

//    std::cout << "[DataDistr] Po  sortowaniu: \n";
//    for(int i = 0; i < size; ++i) std::cout << data[i] <<" \n";
//    std::cout << '\n';

    if (distribution ==1){
        //sort asc
        sorter.sortAlg(alg, data, size);
    }else if (distribution == 2){
        //sort desc
        std::sort(data, data + size);
        std::reverse(data, data+size);
    }else if (distribution ==3){
        //sort only 33% 1/3 of array
        sorter.sortAlg(alg, data, size/3);
    }else if(distribution == 4){
        //sort only 66% 2/3 of an array
        sorter.sortAlg(alg, data, (size*2)/3);
    }

    //check if it works
//    std::cout << "[DataDistr] Po  sortowaniu: \n";
//    for(int i = 0; i < size; ++i)
//        std::cout << data[i] << " \n";
//    std::cout << "\n\n";
}

#endif //AIZO_SORT_DATADISTR_H
