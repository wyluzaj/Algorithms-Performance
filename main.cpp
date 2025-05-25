#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include "include/Sort.h"
#include "include/RandomData.h"
#include "include/DataReader.h"
#include "include/DataWriter.h"
#include "include/Timer.h"
#include "include/DataFile.h"
#include "include/CheckSort.h"
#include "include/DataDistr.h"


//prints usage instructions for the program
void showHelp(){
    std::cout << "Usage:\n";
    std::cout << " --file <algorithm> <type> <distribution> <inputFile> [outputFile]\n";
    std::cout << " --test <algorithm> <type> <repetitions> <size> <distribution> <outputFile>\n";
    std::cout << " --gen <typ> <rozmiar> <plik wyjsciowy>\n";
    std::cout << " --help\n";
    std::cout << "<algorithm>:\n 0 - QS;\n 1 - IS; \n 2 - BIS; \n 3 - HP\n <type>: \n 0 - INT;\n 1 - FLOAT;\n 2 - DOUBLE \n";
    std::cout << "<distribution>:\n 0 - random;\n 1 - sorted asc; \n 2 - sorted desc; \n 3 - 33%\n 4 - 66%;\n";
}



int main(int argc, const char** argv) {

    if (argc == 1 || std::string(argv[1]) == "--help") {
        showHelp();
        return 0;
    }

    std::string mod = argv[1];

    if (mod == "--gen") {
        //Generate mode: type, size, filename
        if (argc < 5) {
            std::cout <<  "Not enough arguments!\n";
            return 1;
        }

        int type = std::stoi(argv[2]);
        int size = std::stoi(argv[3]);
        std::string filename = argv[4];

        generateDataFile(filename, size, type);
        std::cout << "Generated file with random data: " << filename << "\n";
        return 0;
    }
    //mode to generate files with random data with given distribution
    else if (mod == "--file") {
        //file mode:read, sort, check, write
        if (argc < 6) {
            std::cout << "Not enough arguments!\n";
            showHelp();
            return 1;
        }

        int algorithm = std::stoi(argv[2]);
        int type = std::stoi(argv[3]);
        int distribution = std::stoi(argv[4]);
        std::string inputFile = argv[5];
        std::string outputFile = (argc >= 7) ? argv[6] : "";

        std::string method;
        if (algorithm == 0)  method = "QS";
        else if (algorithm == 1)  method = "IS";
        else if (algorithm == 2) method = "HS";
        else if (algorithm == 3) method = "BIS";
        else {
            std::cout << "Unknown algorithm!\n";
            return 1;
        }

        if (type == 0) { // int
            DataReader<int> reader;
            if (!reader.readFromFile(inputFile)) return 1;

            int *data = reader.getData();
            int size = reader.getSize();
            prepareData<int>(data, size, distribution); //apply distribution


            Sort<int> sorter;
            sorter.sortAlg(method, data, size); // sort

            //verify sorting result
            if (!CheckSort<int>::isSorted(data, size)) {
                std::cout << " Data is NOT sorted.\n";
            } else {
                std::cout << "Data sorted correctly.\n";
            }

            if (!outputFile.empty()) {
                DataWriter<int> writer;
                writer.writeToFile(outputFile, data, size); //write sorted data to file
            }
        } else if (type == 1) { // float
            DataReader<float> reader;
            if (!reader.readFromFile(inputFile)) return 1;

            float *data = reader.getData();
            int size = reader.getSize();
            prepareData<float>(data, size, distribution);

            Sort<float> sorter;

            sorter.sortAlg(method, data, size);

            if (!CheckSort<float>::isSorted(data, size)) {
                std::cout << " Data is NOT sorted.\n";
            } else {
                std::cout << "Data sorted correctly.\n";
            }

            if (!outputFile.empty()) {
                DataWriter<float> writer;
                writer.writeToFile(outputFile, data, size);
            }
        } else if (type == 2) { // double
            DataReader<double> reader;
            if (!reader.readFromFile(inputFile)) return 1;

            double *data = reader.getData();
            int size = reader.getSize();
            prepareData<double>(data, size, distribution);

            Sort<double> sorter;
            sorter.sortAlg(method, data, size);

            if (!CheckSort<double>::isSorted(data, size)) {
                std::cout << "Data is NOT sorted.\n";
            } else {
                std::cout << "Data sorted correctly.\n";
            }

            if (!outputFile.empty()) {
                DataWriter<double> writer;
                writer.writeToFile(outputFile, data, size);
            }
        } else {
            std::cout << "Unknown data type!\n";
            return 1;
        }
    } else if (mod == "--test") {
        //test mode: benchmark
        if (argc < 8) {
            std::cout << "Not enough parameters!\n";
            showHelp();
            return 1;
        }

        int algorithm = std::stoi(argv[2]);
        int type = std::stoi(argv[3]);
        int repetitions = std::stoi(argv[4]);
        int size = std::stoi(argv[5]);
        int distribution = std::stoi(argv[6]);
        std::string outputFile = argv[7];

        std::string method;
        if (algorithm == 0)  method = "QS";
        else if (algorithm == 1)  method = "IS";
        else if (algorithm == 2) method = "HS";
        else if (algorithm == 3) method = "BIS";
        else {
            std::cout << "Unknown algorithm!\n";
            return 1;
        }

        int N = repetitions;
        int *timeMs = new int[N];//allocate array
        double avgTime = 0.0; //avgTime time
        double medianTime = 0.0; //medianTime time
        int minTime = 0;
        int maxTime = 0;
        double totalComparisons = 0.0;
        double totalSwaps = 0.0;
        double avgComparisons = 0.0;
        double avgSwaps = 0.0;
        Timer timer;

        if (type == 0) {
            Sort<int> sorter;
            for (int i = 0; i < N; i++) {
                RandomData<int> gen(size);
                int *data = gen.getData();
                prepareData<int>(data, size, distribution);

                sorter.resetCounters();

                timer.start(); // start timer
                sorter.sortAlg(method, data, size); // sort
                timer.stop(); //stop timer


                timeMs[i] = timer.result();
                totalComparisons += sorter.getComparisons();
                totalSwaps += sorter.getSwaps();

            }

            //compute stats (avg, median, min, max)
            std::sort(timeMs, timeMs + repetitions);
            double sum = std::accumulate(timeMs, timeMs + repetitions, 0.0);
            avgTime = sum / static_cast<double>(repetitions);

            if (repetitions % 2 == 0) {
                int mid1 = repetitions / 2 - 1;
                int mid2 = repetitions / 2;
                medianTime = (static_cast<double>(timeMs[mid1]) + timeMs[mid2]) / 2.0;
            } else {
                int mid = repetitions / 2;
                medianTime = static_cast<double>(timeMs[mid]);
            }

            minTime = timeMs[0];
            maxTime = timeMs[repetitions - 1];

            avgComparisons = totalComparisons / repetitions;
            avgSwaps = totalSwaps / repetitions;

        } else if (type == 1) {
            Sort<float> sorter;
            for (int i = 0; i < N; i++) {
                RandomData<float> gen(size);
                float *data = gen.getData();
                prepareData<float>(data, size, distribution);

                sorter.resetCounters();
                timer.start();
                sorter.sortAlg(method, data, size);
                timer.stop();
                timeMs[i] = timer.result();

                totalComparisons += sorter.getComparisons();
                totalSwaps += sorter.getSwaps();


            }
            std::sort(timeMs, timeMs + repetitions);
            double sum = std::accumulate(timeMs, timeMs + repetitions, 0.0);
            avgTime = sum / static_cast<double>(repetitions);

            if (repetitions % 2 == 0) {
                int mid1 = repetitions / 2 - 1;
                int mid2 = repetitions / 2;
                medianTime = (static_cast<double>(timeMs[mid1]) + timeMs[mid2]) / 2.0;
            } else {
                int mid = repetitions / 2;
                medianTime = static_cast<double>(timeMs[mid]);
            }

            minTime = timeMs[0];
            maxTime = timeMs[repetitions - 1];
            avgComparisons = totalComparisons / repetitions;
            avgSwaps = totalSwaps / repetitions;

        } else if (type == 2) {
            Sort<double> sorter;
            for (int i = 0; i < N; i++) {
                RandomData<double> gen(size);
                double *data = gen.getData();
                prepareData<double>(data, size, distribution);

                sorter.resetCounters();
                timer.start();
                sorter.sortAlg(method, data, size);
                timer.stop();
                timeMs[i] = timer.result();

                totalComparisons += sorter.getComparisons();
                totalSwaps += sorter.getSwaps();

            }
            std::sort(timeMs, timeMs + repetitions);
            double sum = std::accumulate(timeMs, timeMs + repetitions, 0.0);
            avgTime = sum / static_cast<double>(repetitions);

            if (repetitions % 2 == 0) {
                int mid1 = repetitions / 2 - 1;
                int mid2 = repetitions / 2;
                medianTime = (static_cast<double>(timeMs[mid1]) + timeMs[mid2]) / 2.0;
            } else {
                int mid = repetitions / 2;
                medianTime = static_cast<double>(timeMs[mid]);
            }

            minTime = timeMs[0];
            maxTime = timeMs[repetitions - 1];
            avgComparisons = totalComparisons / repetitions;
            avgSwaps = totalSwaps / repetitions;


        } else {
            std::cout << "Unknown data type!\n";
            return 1;
        }

//        std::cout << "Zakonczono test:\n";
//        std::cout << "   Algorytm     : " << method << "\n";
//        std::cout << "   Typ danych   : " << (type == 0 ? "int" : (type == 1 ? "float" : "double")) << "\n";
//        std::cout << "   Powtorzenia  : " << repetitions << "\n";
//        std::cout << "   Rozmiar      : " << size << "\n";
//        std::cout << "   Sredni czas  : " << avgTime << " ms\n";
//        std::cout << "   Mediana      : " << medianTime << " ms\n";
//        std::cout << "   Min czas     : " << minTime << " ms\n";
//        std::cout << "   Max czas     : " << maxTime << " ms\n";
//        std::cout << "   Porownania   : " << avgComparisons << "\n";
//        std::cout << "   Przestawienia: " << avgSwaps << "\n";
//        std::cout << " Rozkład: " << distribution << "\n";

        //append results to file
        namespace fs = std::filesystem;
        bool file_empty = !fs::exists(outputFile) || fs::file_size(outputFile) == 0;
        std::ofstream out(outputFile, std::ios::app);
        if (!out.is_open()) {
            std::cout << "Cannot open file: " << outputFile << "\n";
            return 1;
        }
        if (file_empty) {
            out << "Algorytm Typ Powtorzenia Rozmiar Dist Srednia Mediana Max Min PorownaniaAvg PrzestawieniaAvg\n";
        }

        out << method << " "
            << type << " "
            << repetitions << " "
            << size << " "
            << distribution << " "
            << avgTime << " "
            << medianTime << " "
            << maxTime << " "
            << minTime << " "
            << avgComparisons << " "
            << avgSwaps << "\n";
        out.close();
        delete[] timeMs;
    }
}
