/*
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

 

Example 1:

Input: nums = [1,2,2,3,1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:

Input: nums = [1,2,2,3,1,4,2]
Output: 6
Explanation: 
The degree is 3 because the element 2 is repeated 3 times.
So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.
 

Constraints:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.

*/

// Basically we need to find the shortest subarray that has one of the most frequent values in the array 
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        int res = INT_MAX, max_freq = 0, n = nums.size();
        vector<int> max_freq_val; 
        unordered_map<int,int> val2freq;
        for ( auto n : nums )
            if ( ++val2freq[n] > max_freq )
                max_freq = val2freq[n];
        for (auto it : val2freq )
            if ( it.second == max_freq )
                max_freq_val.push_back(it.first);
        
        for ( auto mx : max_freq_val )
        {
            int len = 0, degree = 0, i = 0;
            while( nums[i] != mx )
                i++;
            while( i < n && degree < max_freq )
            {
                if ( nums[i] == mx )
                {
                    degree++;
                }
                len++;
                i++;
            }
            res = min(res,len);
        }
        
        return res;
    }
};

// we could also record each most frequent num's first and last indexs and use them to calculate the length of the subarray that has all of its occurrence 

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        int res = INT_MAX, max_freq = 0; 
        unordered_map<int,int> val2freq; 
        unordered_map<int,vector<int>> valfirstlastindex;
        vector<int> max_freq_val;
        for (auto n : nums )
            if( ++val2freq[n] > max_freq )
                max_freq = val2freq[n];
        for ( auto it : val2freq )
            if ( it.second == max_freq )
                max_freq_val.push_back(it.first);
        for (int i = 0; i < nums.size(); i++ )
        {
            if ( valfirstlastindex[nums[i]].size() < 2 )
                valfirstlastindex[nums[i]].push_back(i);
            else
                valfirstlastindex[nums[i]].back() = i;
        }
        
        
        for ( auto can : max_freq_val )
        {
            if ( valfirstlastindex[can].size() ==  1 )
                res = min(res,1);
            else
                res = min(res,valfirstlastindex[can][1]- valfirstlastindex[can][0]+1);
        }
        return res;
    }
};