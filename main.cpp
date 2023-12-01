#include <iostream>
#include "sorting.h"

using namespace std;

void readInput(int& result, int max) {
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

int main() {
    int category, timeframe, sort = 0;
    cout << "Select a category:\n"
            "1.  Precipitation \n"
            "2.  Avg Temp \n"
            "3.  Max Temp\n"
            "4.  Min Temp\n"
            "5.  Wind Speed\n";
    readInput(category, 5);

    cout << "Select a timeframe:\n"
            "1.  Jan\t\t" "2.  Feb\t\t" "3.  Mar\n"
            "4.  Apr\t\t" "5.  May\t\t" "6.  Jun\n"
            "7.  Jul\t\t" "8.  Aug\t\t" "9.  Sep\n"
            "10. Oct\t\t" "11. Nov\t\t" "12. Dec\n"
            "13. All of 2016\n";
    readInput(timeframe, 13);

    cout << "Select a sort order:\n"
            "1.  Sort by ascending order\n"
            "2.  Sort by descending order\n";
    readInput(sort, 2);
    Sorting test(category, timeframe, sort);
    return 0;
}
