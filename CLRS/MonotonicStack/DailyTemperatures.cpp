/*
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

 

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]
 

Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
*/

// Use a monotonic stack to find the next larger values for each and every element 
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temps) {
        int n = temps.size(); 
        vector<int> res(n,0); 
        stack<pair<int,int>> st;  // {value, and its idx} 
        for ( int i = 0; i < n; i++ )
        {
            if ( st.empty() ) 
            {
                st.push({temps[i],i});
            } else {
                while( !st.empty() && st.top().first < temps[i] )
                {
                    res[st.top().second] = i-st.top().second;
                    st.pop();
                }
                st.push({temps[i],i});
            }
        }

        while( !st.empty() )
        {
            auto top = st.top();
            res[top.second] = 0;
            st.pop();
        }

        return res;
    }
};