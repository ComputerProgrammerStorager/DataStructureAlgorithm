/*
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
Example 2:

Input: nums = [5], k = 9
Output: 0
 

Constraints:

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
2 <= k <= 104

*/

// use prefix sum to check each and every non-empty subarray 
// O(n^2)
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        vector<long> prefix_sum(n+1,0);
        for ( int i = 1; i <= n; i++ )
        {
            prefix_sum[i] = prefix_sum[i-1] + nums[i-1];
        }
        
        for ( int s = 0; s <= n; s++ )
            for ( int e = s+1; e <= n; e++ )
            {
                int sum = prefix_sum[e] - prefix_sum[s];
                if ( sum % k == 0 )
                    ans++;
            }
        
        return ans;
    }
};

// if we encounter a remainder, then we can have as many subarrays as how many times the same remainder has appeared before. 
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0, ans = 0;
        unordered_map<int,int> m;       // sum%p ---> freq
        m[0] = 1;
        for ( int i = 0; i < n; i++ )
        {
            sum = (sum + nums[i]%k + k) % k;
            ans += m[sum]++;
        }
        return ans;
    }
};