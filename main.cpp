#include "sorting.h"

int main() {
    int category, timeframe, sort = 0;
    cout << "Select a category:\n"
            "1.  Precipitation \n"
            "2.  Average Temperature \n"
            "3.  Maximum Temperature\n"
            "4.  Minimum Temperature\n"
            "5.  Wind Speed\n";
    Sorting::readInput(category, 5);

    cout << "Select a timeframe:\n"
            "1.  January\t" "2.  February\t" "3.  March\n"
            "4.  April\t" "5.  May\t\t" "6.  June\n"
            "7.  July\t" "8.  August\t" "9.  September\n"
            "10. October\t" "11. November\t" "12. December\n"
            "13. All of 2016\n";
    Sorting::readInput(timeframe, 13);

    cout << "Select a sort order:\n"
            "1.  Sort by ascending order\n"
            "2.  Sort by descending order\n";
    Sorting::readInput(sort, 2);
    Sorting test(category, timeframe, sort);

    return 0;
}
