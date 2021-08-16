/*
Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti < endi <= 106
*/

/*
Basically it checks if any two intervals overlap

*/

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        int n = intervals.size();
        if ( n < 2 )
            return true;
        for ( int i = 0; i < intervals.size() - 1; i++ )
        {
            if ( intervals[i][1] > intervals[i+1][0] )
                return false;
        }
        
        return true;
    }
};