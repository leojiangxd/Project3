#include "sorting.h"

void Sorting::readWeatherCSV() {
    const int categoryMap[] = {0, 10, 11, 12, 14};
    const string monthMap[] = {"January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November","December"};

    int categoryCol = categoryMap[category-1];
    ifstream file("weather.csv");

    string timeframeString = to_string(timeframe);

    string line;
    getline(file, line); // ignore header
    while (getline(file, line)) {
        vector<string> col;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            // check if the value is enclosed in quotes and remove them
            if (!value.empty() && value.front() == '\"' && value.back() == '\"') {
                value = value.substr(1, value.size() - 2);
            }
            col.push_back(value);
        }

        // add only data of chosen category in chosen month of 2016
        if ((timeframeString == "13" || col[2] == timeframeString) && col[4] != "2017") {
            unordered_map<string, string> row;
            row["Category"] = col[categoryCol];
            row["City"] = col[5];
            row["State"] = col[9];
            row["Month"] = monthMap[stoi(col[2])-1];
            row["WeekOf"] = col[3];
            weatherData.push_back(row);
        }
    }
    file.close(); // finished
}

void Sorting::printData(vector<unordered_map<string, string>>& vec) const {
    const string map[] = {"precipitation", "average temperature", "maximum temperature", "minimum Temp",
                          "wind speed","January", "February", "March", "April", "May", "June",
                          "July","August", "September", "October", "November", "December",
                          "all of 2016", "ascending", "descending"};
    cout << "Enter number of lines to display (Max: " << vec.size() << ")" << endl;
    int numLines = 0;
    readInput(numLines, vec.size());
    cout << "Displaying " << map[category-1] << " during " << map[timeframe+4] << " in " << map[sort+17] << " order:\n";
    for (int i = 0; i < numLines; i++) {
        cout << left << setw(5) << vec[i]["Category"] << " " << vec[i]["City"] << " " << vec[i]["State"] << " (" << vec[i]["Month"] << " " << vec[i]["WeekOf"] << ")" << endl;
    }
}

void Sorting::mergeSortAscending(vector<unordered_map<string, string>>& vec, int left, int right) {
    if (left < right) {
        int mid = left+(right-left)/2;
        mergeSortAscending(vec, left, mid);
        mergeSortAscending(vec, mid+1, right);
        mergeAscending(vec, left, mid, right);
    }
}
void Sorting::mergeAscending(vector<unordered_map<string, string>>& vec, int left, int mid, int right) {
    int n1 = mid-left+1;
    int n2 = right-mid;
    vector<unordered_map<string, string>> l(n1), r(n2);
    for (int i = 0; i < n1; i++)
        l[i] = vec[left+i];
    for (int i = 0; i < n2; i++)
        r[i] = vec[mid+1+i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (stod(l[i]["Category"]) <= stod(r[j]["Category"])) {
            vec[k] = l[i];
            i++;
        }
        else {
            vec[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vec[k] = l[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = r[j];
        j++;
        k++;
    }
}
void Sorting::mergeSortDescending(vector<unordered_map<string, string>>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortDescending(vec, left, mid);
        mergeSortDescending(vec, mid + 1, right);
        mergeDescending(vec, left, mid, right);
    }
}
void Sorting::mergeDescending(vector<unordered_map<string, string>>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<unordered_map<string, string>> l(n1), r(n2);
    for (int i = 0; i < n1; i++)
        l[i] = vec[left + i];
    for (int i = 0; i < n2; i++)
        r[i] = vec[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (stod(l[i]["Category"]) >= stod(r[j]["Category"])) {  // Change the comparison to >= for descending order
            vec[k] = l[i];
            i++;
        } else {
            vec[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vec[k] = l[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = r[j];
        j++;
        k++;
    }
}

void Sorting::quickSortAscending(vector<unordered_map<string, string>>& vec, int low, int high) { //vector should be a city data point pair
    if (high <= low) {
        return;
    }
    double pivot = stod(vec[low]["Category"]);
    int up = low + 1;
    int down = high;
    while (up <= down) {
        while (up <= high && stod(vec[up]["Category"]) <= pivot) {
            up++;
        }
        while (down >= low && stod(vec[down]["Category"]) > pivot) {
            down--;
        }
        if (up < down) {
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low],vec[down]);
    quickSortAscending(vec,low,down - 1);
    quickSortAscending(vec,down + 1, high);
}
void Sorting::quickSortDescending(vector<unordered_map<string, string>>& vec, int low, int high) {
    if (high <= low) {
        return;
    }
    double pivot = stod(vec[low]["Category"]);
    int up = low + 1;
    int down = high;
    while (up <= down) {
        while (up <= high && stod(vec[up]["Category"]) >= pivot) {
            up++;
        }
        while (down >= low && stod(vec[down]["Category"]) < pivot) {
            down--;
        }
        if (up < down) {
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low], vec[down]);
    quickSortDescending(vec, low, down - 1);
    quickSortDescending(vec, down + 1, high);
}

void Sorting::readInput(int& result, int max) {
    if (max < 1)
        return;
    while (true) {
        string userInput;
        cin >> userInput;
        bool validInput = true;
        for (char c : userInput) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }
        if (!validInput) {
            cout << "Enter a number between 1 and " << max << "\n";
            continue;
        }
        int inputNumber = stoi(userInput);
        if (inputNumber < 1 || inputNumber > max) {
            cout << "Enter a number between 1 and " << max << "\n";
        } else {
            result = inputNumber;
            return;
        }
    }
}