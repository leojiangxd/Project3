#include "sorting.h"

//void Sorting::readWeatherCSV(int category, int timeframe) {
//    const int categoryMap[] = {0, 10, 11, 12, 14};
//    category = categoryMap[category-1];
//
//    ifstream file("weather.csv");
//
//    string timeframeString = to_string(timeframe);
//
//    string line;
//    getline(file, line); // ignore header
//    while (getline(file, line)) {
//        vector<string> col;
//        stringstream ss(line);
//        string value;
//
//        while (getline(ss, value, ',')) {
//            // Check if the value is enclosed in quotes
//            if (!value.empty() && value.front() == '\"' && value.back() == '\"') {
//                // Remove the enclosing quotes
//                value = value.substr(1, value.size() - 2);
//            }
//            col.push_back(value);
//        }
//
//        // add only data of chosen category in chosen month of 2016
//        if ((timeframeString == "13" || col[2] == timeframeString) && col[4] != "2017") {
//            vector<string> row;
//            row.push_back(col[category]);
//            row.push_back(col[2]);  // 0 Date.Month
//            row.push_back(col[5]);  // 2 Station.City
//            row.push_back(col[9]);  // 3 Station.State
//            weatherData.push_back(row);
//        }
//    }
//    file.close(); // finished
//}

void Sorting::readWeatherCSV() {
    ifstream file("weather.csv");
    const int categoryMap[] = {0, 10, 11, 12, 14};
    string line;
    getline(file, line); // ignore header
    vector<string> header;
    stringstream s(line);
    string val;
    int index = 0, k = 0;
    while (getline(s, val, ',')) {
        if (index == categoryMap[k]) {
            header.push_back(val);
            k++;
        }
        index++;
    }
    header.push_back(val);

    while (getline(file, line)) {
        unordered_map<string, string> row;
        stringstream ss(line);
        string value;
        int i = 0;
        k = 0;
        while (getline(ss, value, ',')) {
            if (i == categoryMap[k]) {
                // Check if the value is enclosed in quotes
                if (!value.empty() && value.front() == '\"' && value.back() == '\"') {
                    // Remove the enclosing quotes
                    value = value.substr(1, value.size() - 2);
                }
                row.insert({header[k], value});
                k++;
            }
            i++;
        }
        weatherData.push_back(row);
    }
    file.close(); // finished
}

void Sorting::printData() const {
    for (const auto& row : weatherData) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}