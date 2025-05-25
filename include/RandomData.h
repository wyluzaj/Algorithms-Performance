#ifndef AIZO_SORT_RANDOMDATA_H
#define AIZO_SORT_RANDOMDATA_H

#include <iostream>
#include <random>
#include <limits>
#include <type_traits>
#include <cstring>

//class to generate random values
template <typename T>
class RandomData {
private:
    T* data;
    int size;

public:
    RandomData(int s) {
        size = s;
        data = new T[size];

//        generate();
//    }
//
//    void generate<float>() {
//    }

        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> d64;
        std::uniform_int_distribution<uint32_t> d32;

        for ( int i=0; i < size; i++) {
            if (std::is_same<T, int>::value) {
                //generates random int in full range
                std::uniform_int_distribution<int> d(
                        std::numeric_limits<int>::min(),
                        std::numeric_limits<int>::max()
                );
                data[i] = d(gen);
            }

            else if (std::is_same<T, float>::value) {
                //generate random bits than copy to float
                //std::numeric_limits - doesn't work, with this approach values -> inf
                uint32_t bits = d32(gen);
                float f;
                std::memcpy(&f, &bits, sizeof(float)); // memcpy kopujemy z pamieci bity do adresu zmiennej f z adresu bits w ilośći 32
                if (std::isfinite(f)) {
                    data[i] = f;
                } else i--; //retry if not finit
            }

            else if (std::is_same<T, double>::value) {
                //generate random bits than copy to float
                //the reason to not use numeric limits is same as for float
                uint64_t bits = d64(gen);
                double d;
                std::memcpy(&d, &bits, sizeof(double));
                if (std::isfinite(d)) {
                    data[i] = d;
                } else i--;
            }
            else {
                throw std::runtime_error("Unknown data type in RandomData<T>");
            }
        }
    }

    T* getData() const {
        return data;
    }

    int getSize() const {
        return size;
    }

    ~RandomData() {
        delete[] data; //free memory
    }
};


#endif //AIZO_SORT_RANDOMDATA_H
