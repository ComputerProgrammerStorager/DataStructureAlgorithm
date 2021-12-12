/*
Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.

Example 1:

Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:

Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 

Constraints:

The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
*/

// basically check all subarray sums and find a satisfied one 
// pay special attention when k == 0 in which case it returns true only if the sum is also 0
// O(n^2)
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n+1,0); // sum[i] means sum of num[0...i-1];

        for ( int i = 1; i <= n; i++ )
        {
            sum[i] = nums[i-1] + sum[i-1];
        }
        
        for ( int i = 0; i < n - 1; i++ )
            for ( int j = i+1; j <= n; j++ )
            {
                if ( j - i >= 2) 
                {
                    int s = sum[j] - sum[i];
                    #if 0 
                    if ( k == 0 && s == 0 )
                        return true;
                    if ( k && s % k == 0 )
                        return true;
                    #endif 
                    if ( s == k || (k && s%k == 0) )
                        return true;
                }
            }
        
        return false;
    }
};

// O(n)
// we maintain a map mapping a remainder to it's index.. if we have two same remainders, then it means 
// the elements between these two index sums up to a multipe of k, i.e., e - s.
// Note: we need to initially set m[0] to -1. 
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        m[0] = -1;
        int n = nums.size(), sum = 0;
        for ( int i = 0; i < n; i++ )
        {
            sum += nums[i];
            if ( k != 0 )
                sum %= k;
            if ( m.count(sum) )
            {
                if (m[sum] + 1 < i )
                {
                    return true;
                }
            }
            else 
            {
                m[sum] = i;
            }
        }
        return false;
    }
};