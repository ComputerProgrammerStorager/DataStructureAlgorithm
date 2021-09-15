/*
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
Example 2:

Input: nums = [5], k = 1
Output: 5.00000
 

Constraints:

n == nums.length
1 <= k <= n <= 105
-104 <= nums[i] <= 104

*/

// Use sliding window to maintain the current sum of the numbers in the window 
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sum_win = 0.0, res = -DBL_MAX;
        int left = 0, right = 0;
        while( right < nums.size() )
        {
            sum_win += nums[right];
            if ( right - left + 1 == k )
            {
                res = max(res,sum_win/k);
                sum_win -= nums[left++];
            }
            right++;
        }
        
        return res;
    }
};

// use cumulative sum 
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sum_win = 0.0, res = -DBL_MAX;
        for ( int i = 1; i < nums.size(); i++ )
        {
            nums[i] += nums[i-1];
        }
        res = nums[k-1] * 1.0 / k;
        for ( int i = k; i < nums.size(); i++ )
        {
            res = max(res,(nums[i]-nums[i-k])*1.0/k);
        }
        
        return res;
    }
};