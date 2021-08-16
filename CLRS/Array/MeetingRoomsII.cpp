/*
Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.


Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 104
0 <= starti < endi <= 106
*/

// For each timepoint increment by one if it's a start time and decrement by one if it's an endtime. 
// then we just find the maximum value every occurred
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int,int> m;
        for ( auto a : intervals )
        {
            m[a[0]]++;
            m[a[1]]--;
        }
        
        int res = 0, rooms = 0;
        
        for ( auto it : m )
        {
            res = max(res,rooms += it.second);
        }
        
        return res;
    }
};

// we use a priority_queue to maintain the currently on-going meetings' end time 
// and for a new meeting request, we just check on earlies ending time, if the earliest can be freed 
// then we can just reuse this room by poping it and pushing the next end time
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        priority_queue<int,vector<int>, greater<int>> pq; // end time priority queue
        sort(intervals.begin(),intervals.end());
        for ( auto a : intervals )
        {
            if ( !pq.empty() && pq.top() <= a[0] )
            {
                pq.pop();
            }
            pq.push(a[1]);
        }
        
        return pq.size();
    }
};

// sort the start and end time respectively and for each next meeting request, we decide if it needs a new room or not 
// by checking its start time against the earliest end time indicated by end_pos. It's essentially the same idea as of using priority queue

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> start_time, end_time;
        int endpos = 0, res = 0;
        
        for ( auto a : intervals )
        {
            start_time.push_back(a[0]);
            end_time.push_back(a[1]);
        }
        sort(start_time.begin(),start_time.end());
        sort(end_time.begin(),end_time.end());
        for ( int i = 0; i < intervals.size(); i++ )
        {
            if ( start_time[i] < end_time[endpos] )
                res++;
            else
                endpos++;
        }
        return res;
    }
};