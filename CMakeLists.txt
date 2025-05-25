cmake_minimum_required(VERSION 3.26)
project(AIZO_SORT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(AIZO_SORT main.cpp
        include/DataReader.h
        include/DataWriter.h
        include/RandomData.h
        include/Sort.h
        include/Timer.h
        Timer.cpp
        include/DataFile.h
        include/CheckSort.h
        include/DataDistr.h)

# Statyczne linkowanie bibliotek libgcc i libstdc++, żeby skrypt .bat działal
set_target_properties(AIZO_SORT PROPERTIES
        LINK_FLAGS "-static -pthread -static-libgcc -static-libstdc++"
)
