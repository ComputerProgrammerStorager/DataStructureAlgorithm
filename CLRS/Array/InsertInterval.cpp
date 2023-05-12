/*
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 105
intervals is sorted by starti in ascending order.
newInterval.length == 2
0 <= start <= end <= 105

*/

// Method 1: use linear search to insert the new interval to the list first, and then merge any possible overlapping intervals 

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        bool isInserted = false;
        vector<vector<int>> res;
        for ( int i = 0; i < intervals.size(); i++ )
        {
            if ( intervals[i][0] > newInterval[0] )
            {
                isInserted = true;
                intervals.insert(intervals.begin()+i,newInterval);
                break;
            }
        }
        if ( !isInserted )
        {
            intervals.push_back(newInterval);
        }

        for ( int i = 0; i < intervals.size(); i++ )
        {
            auto cur = intervals[i];
            while( i < intervals.size() && isOverlap(cur,intervals[i]) )
            {
                cur = mergeInterval(cur,intervals[i]);
                i++;
            }
            i--;
            res.push_back(cur);
        }

        return res;
    }

private:
    vector<int> mergeInterval(vector<int> const& a, vector<int> const& b)
    {
        return {min(a[0],b[0]),max(a[1],b[1])};
    }

    bool isOverlap(vector<int> const& a, vector<int> const& b)
    {
        return min(a[1],b[1]) >= max(a[0],b[0]);
    }
};


// Method 2: user binary search to find the insertion position
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        auto it = upper_bound(intervals.begin(),intervals.end(),newInterval);
        intervals.insert(it,newInterval);

        for ( int i = 0; i < intervals.size(); i++ )
        {
            auto cur = intervals[i];
            while(i < intervals.size() && isOverlap(cur,intervals[i]) )
            {
                cur = merge(cur,intervals[i]);
                i++;
            }

            res.push_back(cur);
            i--;
        }

        return res;
    }
private:
    bool isOverlap(vector<int> const& a, vector<int> const& b)
    {
        return min(a[1],b[1]) >= max(a[0],b[0]);
    }

    vector<int> merge(vector<int> const& a, vector<int> const& b)
    {
        return {min(a[0],b[0]),max(a[1],b[1])};
    }
};