/*
Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
 

Example 1:

Input: timePoints = ["23:59","00:00"]
Output: 1
Example 2:

Input: timePoints = ["00:00","23:59","00:00"]
Output: 0
 

Constraints:

2 <= timePoints.length <= 2 * 104
timePoints[i] is in the format "HH:MM".
*/

// Sorting and check the adjcent difference.. Special value is the wrapped value 

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int res = INT_MAX, n = timePoints.size();
        vector<pair<int,int>>  times; // hour and min pairs 
        for ( const auto& t : timePoints)
        {
            times.push_back({stoi(t.substr(0,2)),stoi(t.substr(3))});
        } 

        sort(times.begin(),times.end());
        for ( int i = 1; i < n; i++ )
        {
            res = min(res,calculatediff(times[i-1],times[i]));
        }
        int last_diff = (24-times[n-1].first) * 60 - times[n-1].second + 60*times[0].first + times[0].second;
        return min(res,last_diff); 
    }
private:
    int calculatediff(pair<int,int> s, pair<int,int> e)
    {
        return (e.first-s.first) * 60 + (e.second-s.second);
    }
};

// use bucket sorting idea 
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int res = INT_MAX, mn_time = INT_MAX, mx_time = INT_MIN;
        bool buck[24*60] = {false};
        for ( auto& t : timePoints) 
        {
            int tmp = calcuMins(t);
            if ( buck[tmp] )
                return 0;
            mn_time = min(mn_time,tmp);
            mx_time = max(mx_time,tmp);
            buck[tmp] = true;
        }

        int prev = mn_time, next = prev+1;
        while(next <= mx_time)
        {
            while(!buck[next])
                next++;
            res = min(res,next-prev);
            prev = next++;
        }

        return min(res,24*60-mx_time + mn_time);
    }
private:
    int calcuMins(string& t)
    {
        return stoi(t.substr(0,2))*60 + stoi(t.substr(3));
    }
};