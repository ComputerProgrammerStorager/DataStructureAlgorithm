/*
Given an integer array nums and an integer k, return the maximum length of a subarray that sums to k. If there is not one, return 0 instead.

Example 1:

Input: nums = [1,-1,5,-2,3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
Example 2:

Input: nums = [-2,-1,2,1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
 

Constraints:

1 <= nums.length <= 2 * 105
-104 <= nums[i] <= 104
-109 <= k <= 109
*/

// As we accumulate the sum, we check if the sum difference already exists
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int,int> prefixsum2idx;
        prefixsum2idx[0] = -1;
        int prefixsum = 0, longest_len = 0, n = nums.size();
        for ( int r = 0; r < n; r++ )
        {
            prefixsum += nums[r];
            if ( prefixsum2idx.count(prefixsum-k) )
            {
                longest_len = max(longest_len,r-prefixsum2idx[prefixsum-k]);
            }
            if ( prefixsum2idx.count(prefixsum) == 0 )
            {
                prefixsum2idx[prefixsum] = r;
            }
        }
        
        return longest_len;
    }
};