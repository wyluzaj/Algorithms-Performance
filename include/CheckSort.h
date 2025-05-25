#ifndef AIZO_SORT_CHECKSORT_H
#define AIZO_SORT_CHECKSORT_H

//template class to check if an array is sorted
template <typename T>
class CheckSort{
public:
    //isSorted returns true if array is sorted asc
    static bool isSorted(T* data, int size) {
        //iterate through array and checks if el - 1 > el
        for (int i = 1; i < size; ++i) {
            if (data[i - 1] > data[i]) {
                //el-1 > 1. its nos sorted array -> false
                return false;
            }
        }
        return true;
    }
};

#endif //AIZO_SORT_CHECKSORT_H
