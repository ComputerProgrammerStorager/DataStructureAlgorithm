/*
You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.
 

Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
*/

// perceive it consists of two dp problems 
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int mx = 0, mn = 0;
        int res = 0;
        for ( auto num : nums )
        {
            mx = max(num,mx+num);
            mn = min(num,mn+num);
            res = max(res,max(abs(mx),abs(mn)));
        }
        
        return res;
    }
};

// the sum of any subarry A[i,j] is equal to prefix[j] - prefix[i+1] 
// and asb(sum(A[i,j])) could either be prefix[j]-prefix[i+1] or prefix[i+1] - prefix[j]..
// so the problem becomes find the max and min prefix. 
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int prefix_sum = 0, max_prefix_sum = 0, min_prefix_sum = 0;
        for ( auto x : nums )
        {
            prefix_sum += x;
            max_prefix_sum = max(max_prefix_sum,prefix_sum);
            min_prefix_sum = min(min_prefix_sum,prefix_sum);
        }
        
        return max_prefix_sum - min_prefix_sum;
    }
};