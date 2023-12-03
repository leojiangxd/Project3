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
    const int categoryMap[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
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
            cout << value.first << " " << value.second << endl;
        }
        cout << endl;
    }
}

vector<pair<string,int>> Sorting::testParse(int category, int timeframe, int sort) {
    vector<pair<string,int>> vec;
    string city = "";
    for (const auto& row : weatherData) {
        city = row.at("\"Station.City\"");
        for (const auto& value : row) {
            if (value.first.find("Precipitation") != string::npos){
                vec.push_back(make_pair(city,stoi(value.second)));
            }
        }
    }
    return vec;
}

void Sorting::quickSort(vector<pair<string,int>>& vec, int low, int high) { //vector should be a city data point pair
    if (high <= low) {
        return;
    }
    int pivot = vec[low].second;
    int up = low + 1;
    int down = high;
    while (up <= down) {
        while (up <= high && vec[up].second <= pivot) {
            up++;
        }
        while (down >= low && vec[down].second > pivot) {
            down--;
        }
        if (up < down) {
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low],vec[down]);
    quickSort(vec,low,down - 1);
    quickSort(vec,down + 1, high);
}

void Sorting::mergeSort(int category, int timeframe, int sort) {
    dealData();
    vector<unordered_map<string,string>> tmp = chooseTimeframe(timeframe, weatherData);
    vector<pair<double, string>> data = chooseCategory(category, tmp);
    clock_t start, finish;
    start = clock();
    mergeSort(data, sort);
    finish = clock();
    for (const auto& row : data) {
        cout << row.second << " " << row.first << endl;
    }
    cout << "Time: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}

vector<unordered_map<string, string>> Sorting::chooseTimeframe(int timeframe, vector<unordered_map<string, string>>& data) {
    vector<unordered_map<string, string>> result;
    if (timeframe == 13) {
        for (const auto& row : data) {
            if (row.at("\"Date.Year\"") == "2016") {
                unordered_map<string, string> temp;
                temp.insert({"\"Data.Precipitation\"", row.at("\"Data.Precipitation\"")});
                temp.insert({"\"Data.Temperature.Avg Temp\"", row.at("\"Data.Temperature.Avg Temp\"")});
                temp.insert({"\"Data.Temperature.Max Temp\"", row.at("\"Data.Temperature.Max Temp\"")});
                temp.insert({"\"Data.Temperature.Min Temp\"", row.at("\"Data.Temperature.Min Temp\"")});
                temp.insert({"\"Data.Wind.Speed\"", row.at("\"Data.Wind.Speed\"")});
                temp.insert({"\"Station.City\"", row.at("\"Station.City\"")});
                result.push_back(temp);
            }
        }
    } else {
        for (const auto& row : data) {
            if (row.at("\"Date.Month\"") == to_string(timeframe)) {
                unordered_map<string, string> temp;
                temp.insert({"\"Data.Precipitation\"", row.at("\"Data.Precipitation\"")});
                temp.insert({"\"Data.Temperature.Avg Temp\"", row.at("\"Data.Temperature.Avg Temp\"")});
                temp.insert({"\"Data.Temperature.Max Temp\"", row.at("\"Data.Temperature.Max Temp\"")});
                temp.insert({"\"Data.Temperature.Min Temp\"", row.at("\"Data.Temperature.Min Temp\"")});
                temp.insert({"\"Data.Wind.Speed\"", row.at("\"Data.Wind.Speed\"")});
                temp.insert({"\"Station.City\"", row.at("\"Station.City\"")});
                result.push_back(temp);
            }
        }
    }

    return result;
}

vector<pair<double, string>> Sorting::chooseCategory(int category, vector<unordered_map<string, string>>& data) {
    vector<pair<double,string>> result;
    switch (category) {
        case 1:
            for (const auto& row : data) {
                result.emplace_back(stod(row.at("\"Data.Precipitation\"")), row.at("\"Station.City\""));
            }
            break;
        case 2:
            for (const auto& row : data) {
                result.emplace_back(stod(row.at("\"Data.Temperature.Avg Temp\"")), row.at("\"Station.City\""));
            }
            break;
        case 3:
            for (const auto& row : data) {
                result.emplace_back(stod(row.at("\"Data.Temperature.Max Temp\"")), row.at("\"Station.City\""));
            }
            break;
        case 4:
            for (const auto& row : data) {
                result.emplace_back(stod(row.at("\"Data.Temperature.Min Temp\"")), row.at("\"Station.City\""));
            }
            break;
        case 5:
            for (const auto& row : data) {
                result.emplace_back(stod(row.at("\"Data.Wind.Speed\"")), row.at("\"Station.City\""));
            }
            break;
    }
    return result;
}
void Sorting::mergeSort(vector<pair<double,string>>& data, int sort) {
    mergeSort(data, 0, data.size() - 1, sort);
}
void Sorting::mergeSort(vector<pair<double,string>> &data, int left, int right, int sort) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(data, left, mid, sort);
    mergeSort(data, mid + 1, right, sort);
    merge(data, left, mid, right, sort);
}
void Sorting::merge(vector<pair<double,string>>& data, int left, int mid, int right, int sort) {
    int i = left, j = mid + 1, k = 0;
    vector<pair<double,string>> temp(right - left + 1);
    while (i <= mid && j <= right) {
        if (sort == 1) {
            if (data[i].first <= data[j].first) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
            }
        } else {
            if (data[i].first >= data[j].first) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
            }
        }
    }
    while (i <= mid) {
        temp[k++] = data[i++];
    }
    while (j <= right) {
        temp[k++] = data[j++];
    }
    for (i = left, k = 0; i <= right; i++, k++) {
        data[i] = temp[k];
    }
}

void Sorting::dealData() {
    for (auto& row : weatherData) {
        string fullDate = row.at("\"Date.Full\"");
        string year = "";
        string month = "";
        stringstream ss(fullDate);
        getline(ss, year, '/');
        getline(ss, month, '/');
        row.insert({"\"Date.Year\"", year});
        row.insert({"\"Date.Month\"", month});
    }
}