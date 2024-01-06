/*
Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

Note that:

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).
 

Example 1:

Input: nums = [3,6,9,12]
Output: 4
Explanation:  The whole array is an arithmetic sequence with steps of length = 3.
Example 2:

Input: nums = [9,4,7,2,10]
Output: 3
Explanation:  The longest arithmetic subsequence is [4,7,10].
Example 3:

Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation:  The longest arithmetic subsequence is [20,15,10,5].
 

Constraints:

2 <= nums.length <= 1000
0 <= nums[i] <= 500
*/

/// dp[i][d] denotes the max subsequence length of subarray [0,i] with difference being d 
// since d could be negative values, so it's convenient to use a hash map to store the results. 
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size(), max_len = 2;
        vector<unordered_map<int,int>> dp(n);
        for (int i = 0; i < n; i++ ) 
            for ( int j = 0; j < i; j++ ) {
                int d = nums[i]-nums[j];
                if ( dp[j].count(d) == 0 ) {
                    dp[i][d] = 2;
                } else {
                    dp[i][d] = dp[j][d] + 1;
                }

                max_len = max(dp[i][d], max_len);
            }

        return max_len;
    }
};