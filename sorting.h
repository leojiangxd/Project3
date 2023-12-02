#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Sorting {
private:
//    vector<vector<string>> weatherData;
    vector<unordered_map<string, string>> weatherData;

//    void readWeatherCSV(int category, int timeframe);
    void readWeatherCSV();
public:
    Sorting(int category, int timeframe, int sort) {
//        readWeatherCSV(category, timeframe);
        readWeatherCSV();
        // implement merge sort and time
        // implement quick sort and time
        // compare times and print output
    }
    void printData() const;
    vector<pair<string,int>> testParse(int category, int timeframe, int sort);
    void quickSort(vector<pair<string,int>>& vec, int low, int high);

};