#ifndef AIZO_SORT_SORT_H
#define AIZO_SORT_SORT_H

#include <iostream>
#include <string>

//class contains sorting algorithms

template <typename T>
class Sort {
public:
    //select sorting alg by name
    void sortAlg(std::string& algorithm, T* data, int size) {
        if (algorithm == "IS") {
            insertion_sort(data, size);
        }
        else if (algorithm == "BIS") {
            binary_sort(data, size);
        }
        else if (algorithm == "HS") {
            heap_sort(data, size);
        }
        else if (algorithm == "QS") {
            quick_sort(data, 0, size - 1);
        }
        else {
            std::cout << "Unknown algorithm: " << algorithm << std::endl;
        }
    }

    int getComparisons() {
        return comparisons;
    }

    int getSwaps(){
        return swaps;
    }

    void resetCounters(){
        comparisons = 0;
        swaps = 0;
    }


private:
    int comparisons = 0;//number of comparisons
    int swaps = 0;//number of swaps

    //insertion sort IS
    void insertion_sort(T* data, int size) {
        for (int i = 1; i < size; ++i) {
            T key = data[i];//element to insert
            int j = i - 1; // previous el.
            while (j >= 0){
                comparisons++;
                if (data[j] > key){ //if current el > key
                    data[j + 1] = data[j]; //move el to right
                    swaps++;
                    j--; //move left
                } else {
                    break; //correct position have been found
                }
            }
            data[j + 1] = key; //insert key in correct place
            swaps++;
        }
    }
//binary search to place element in the right position
    int binary_search(T* data, T key, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;//mid index
            comparisons++;
            if (data[mid] == key) // pivot = key
                return mid;
            else if (data[mid] < key)//pivot < key
                left = mid + 1; //search in right sight (move left)
            else
                right = mid - 1;  //search in left sight (move right)
        }
        return left;
    }
//binary insertion sort BIS
    void binary_sort(T* data, int size) {
        for (int i = 1; i < size; ++i) {

            T key = data[i];
            int j = i - 1;

            int position = binary_search(data, key, 0, j);//find insertion position

            while (j >= position) {
                data[j + 1] = data[j]; //move right
                swaps++;
                j--; //move left
            }
            data[position] = key; //place key into position
            swaps++;
        }
    }

    void heapify(T* data, int size, int root) {
        int largest = root;
        int left = 2 * root + 1; //left child index
        int right = 2 * root + 2; //right child index

        if (left < size) {
            comparisons++;
            if (data[left] > data[largest]) //left child > largest
                largest = left; //update largest
        }
        if (right < size) {
            comparisons++;
            if (data[right] > data[largest])
                largest = right;}

            if (largest != root) { //root!= largest
            std::swap(data[root], data[largest]); //swap root and largest
            swaps++;
            heapify(data, size, largest); //recurse
        }
    }

    void heap_sort(T* data, int size) {
        for (int i = size / 2 - 1; i >= 0; i--) { //building max heap
            heapify(data, size, i);
        }

        for (int i = size - 1; i >= 0; i--) { //extracting elements
            std::swap(data[0], data[i]); //move max to the end
            swaps++;
            heapify(data, i, 0); //heapify
        }
    }

    void quick_sort(T* data, int left, int right) {
        int i, j;
        T pivot;

        i = (left + right) / 2;//pivot -> middle
        pivot = data[i];
        std::swap(data[i], data[right]); //move pivot to the end
        swaps++;

        for (j = i = left; i < right; i++) {
            comparisons++;
            if (data[i] < pivot) {
                std::swap(data[i], data[j]); //swap to front
                swaps++;
                j++;
            }
        }

        data[right] = data[j];
        data[j] = pivot; //place pivot in final position
        swaps++;
        if (left < j - 1) //sort left subarray
            quick_sort(data, left, j - 1);
        if (j + 1 < right) //sort right subarray
            quick_sort(data, j + 1, right);
    }
};


#endif //AIZO_SORT_SORT_H
