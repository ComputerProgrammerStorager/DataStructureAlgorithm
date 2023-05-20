/*
Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.

A good subarray is a subarray where:

its length is at least two, and
the sum of the elements of the subarray is a multiple of k.
Note that:

A subarray is a contiguous part of the array.
An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.
 

Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
0 <= sum(nums[i]) <= 231 - 1
1 <= k <= 231 - 1

*/

// subarray sums can be computed conveniently using prefix sum, e.g., prefix_sum[j+1] - prefix_sum[i] denotes the sum of arr[i...j], assuming prefix_sum[i] denotes arr[0..i)
// (prefix_sum[j+1] - prefix_sum[i]) % k would mean prefix_sum[j+1]%k == prefix_sum[i]%k 
// if we find the same appears already, but the size if less than 2, then we keep the leftmost. Basically, in cases where there are two consecutive 0s. 
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if ( n == 0 || k == 0 )
            return 0;
        unordered_map<int,int> m;       // map remainder to prefix sum idx
        int prefix_sum = 0;
        m[0] = 0;

        for ( int i = 0; i < n; i++ )
        {
            prefix_sum += nums[i]; 
            if ( m.count(prefix_sum % k) )
            {
                if ( m[prefix_sum%k] < i )
                    return true;
            }
            else {
                m[prefix_sum%k] = i+1;
            }
        }

        return false;
    }
};