#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <chrono>

using namespace std;

class Sorting {
private:
    int category, timeframe, sort;
    vector<unordered_map<string, string>> weatherData;
    void printData(vector<unordered_map<string, string>>& vec) const;
    void readWeatherCSV();
    void mergeSortAscending(vector<unordered_map<string, string>>& vec, int left, int right);
    static void mergeAscending(vector<unordered_map<string, string>>& vec, int left, int mid, int right);
    void mergeSortDescending(vector<unordered_map<string, string>>& vec, int left, int right);
    static void mergeDescending(vector<unordered_map<string, string>>& vec, int left, int mid, int right);
    void quickSortAscending(vector<unordered_map<string, string>>& vec, int low, int high);
    void quickSortDescending(vector<unordered_map<string, string>>& vec, int low, int high);
public:
    Sorting(int category, int timeframe, int sort) {
        this->category = category;
        this->timeframe = timeframe;
        this->sort = sort;
        readWeatherCSV();
        vector<unordered_map<string, string>> weatherDataMerge = weatherData;
        vector<unordered_map<string, string>> weatherDataQuick = weatherData;

        // time mergesort
        auto start = chrono::high_resolution_clock::now();
        if (sort == 1) {
            mergeSortAscending(weatherDataMerge, 0, weatherDataMerge.size() - 1);
        }
        else {
            mergeSortDescending(weatherDataMerge, 0, weatherDataMerge.size() - 1);
        }
        auto end = chrono::high_resolution_clock::now();
        double t_merge = chrono::duration<double, milli>(end-start).count();

        // time quicksort
        start = chrono::high_resolution_clock::now();
        if (sort == 1) {
            quickSortDescending(weatherDataQuick, 0, weatherDataQuick.size() - 1);
        }
        else {
            quickSortAscending(weatherDataQuick, 0, weatherDataQuick.size() - 1);
        }
        end = chrono::high_resolution_clock::now();
        double t_quick = chrono::duration<double, milli>(end-start).count();

        // compare times and print output
        printData(weatherDataMerge);
        cout << "\nAlgorithm times:\nMerge Sort: " << fixed << t_merge << " ms\nQuick Sort: " << fixed << t_quick << " ms";
    }
    static void readInput(int& result, int max);
};