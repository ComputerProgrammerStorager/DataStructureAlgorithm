/*
Write a program to count the number of days between two dates.

The two dates are given as strings, their format is YYYY-MM-DD as shown in the examples.

 

Example 1:

Input: date1 = "2019-06-29", date2 = "2019-06-30"
Output: 1
Example 2:

Input: date1 = "2020-01-15", date2 = "2019-12-31"
Output: 15
 

Constraints:

The given dates are valid dates between the years 1971 and 2100.
*/

// calculate the days from the same year 1971 and return the absolute difference 
class Solution {
public:
    int daysBetweenDates(string date1, string date2) {
        return abs(daysfrom1971(date1)-daysfrom1971(date2));
    }

    int daysfrom1971(string date) { 
        int year = stoi(date.substr(0,4)), month = stoi(date.substr(5,2)), day = stoi(date.substr(8,2));
        int year_diff = year - 1971; 
        vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
        int cur_year = 1971, days_diff = 0;
        while( cur_year < year) {
            days_diff += isleap(cur_year) ? 366 : 365;
            cur_year++;
        }

        days_diff += (isleap(year) && month > 2) + accumulate(days.begin(),days.begin()+month-1,0) + day;
        return days_diff;
    }

    bool isleap(int y) {
        return (y%4==0 && y%100) || (y%400==0);
    }
};