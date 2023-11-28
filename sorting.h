#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Sorting {
private:
    vector<vector<string>> weatherData;

    void readWeatherCSV(int category, int timeframe);
public:
    Sorting(int category, int timeframe, int sort) {
        readWeatherCSV(category, timeframe);
        // implement merge sort and time
        // implement quick sort and time
        // compare times and print output
        printData();
    }
    void printData() const;
};