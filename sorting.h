#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Sorting {
private:
    vector<unordered_map<string, string>> weatherData;
    vector<pair<double, string>> chooseCategory(int category, vector<unordered_map<string, string>>& data);
    vector<unordered_map<string, string>> chooseTimeframe(int timeframe, vector<unordered_map<string, string>>& data);
    void readWeatherCSV();
    void dealData();
public:
    Sorting(int category, int timeframe, int sort) {
        readWeatherCSV();
        // implement merge sort and time
        // implement quick sort and time
        // compare times and print output
    }
    void printData() const;

    vector<pair<string,int>> testParse(int category, int timeframe, int sort);
    void quickSort(vector<pair<string,int>>& vec, int low, int high);

    void mergeSort(int category, int timeframe, int sort);
    void mergeSort(vector<pair<double,string>>& data, int left, int right, int sort);
    void mergeSort(vector<pair<double,string>>& data, int sort);
    void merge(vector<pair<double,string>>& data, int left, int mid, int right, int sort);
};