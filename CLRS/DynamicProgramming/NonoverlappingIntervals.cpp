/*
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

 

Example 1:

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
Example 2:

Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.
Example 3:

Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 

Constraints:

1 <= intervals.length <= 105
intervals[i].length == 2
-5 * 104 <= starti < endi <= 5 * 104

*/

// naive "take" or "not taken" approach 
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int res = 0;
        sort(intervals.begin(),intervals.end());
        return helper(-1,0,intervals);
    }
    int helper(int prev,int cur,vector<vector<int>> intervals)
    {
        if ( cur == intervals.size() ) 
            return 0;
        int taken = INT_MAX, nottaken;
        if ( prev == -1 || intervals[prev][1] <= intervals[cur][0] )
            taken = helper(cur,cur+1,intervals);
        nottaken = helper(prev,cur+1,intervals) + 1;
        return min(taken,nottaken);
    }
};

// dp on the start time of intervals, similar to the idea of LIS 
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size(), maxCompatible = 1;
        vector<int> dp(n,1);      // dp[i] represents the max compatible intervals upto interval[i]
        dp[0] = 1;
        sort(intervals.begin(),intervals.end());
        for ( int i = 1; i < n; i++ )
        {
            for ( int j = 0; j < i; j++ )
            {
                if ( !IsOverlapping(intervals[j],intervals[i]) )
                    dp[i] = max(dp[i],dp[j]+1);
            }
            maxCompatible = max(maxCompatible,dp[i]);
        }
        
        return n-maxCompatible;
    }
    
    
private:
    bool IsOverlapping(vector<int> const& interval1, vector<int> const& interval2)
    {
        // interval1 has earlier start time than interval2 
        return interval1[1] > interval2[0];
    }
    
};

// greedily construct. if compatible, keep it, otherwise, keep the shorter end time as the previous 
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int removal = 0, prev = 0, n = intervals.size();
        if ( n < 2 )
            return 0;
        sort(intervals.begin(),intervals.end());
        for ( int i = 1; i < n; i++ )
        {
            if ( intervals[prev][1] > intervals[i][0] )
            {
                if ( intervals[prev][1] > intervals[i][1] )
                {
                    prev = i;
                }
                removal++;
            }
            else    // compatible
            {
                prev = i;
            }
        }
        
        return removal;
    }
};