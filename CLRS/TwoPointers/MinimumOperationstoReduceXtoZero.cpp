/*
You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.

Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.

 

Example 1:

Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
Example 2:

Input: nums = [5,6,7,8,9], x = 4
Output: -1
Example 3:

Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104
1 <= x <= 109
*/

// Two key insights that have important implications:
// 1. all nums are positive: this means sliding window sum is monotically increasing 
// 2. minimal removals to sum x means longest subarray sums to total_sum - x, due to removals only happening on the ends 
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total_sum = accumulate(nums.begin(),nums.end(),0);
        int l = 0, r = 0, current_sum = 0, max_len = -1, n = nums.size();
        for ( ; r < n; r++ )
        {
            current_sum += nums[r];
            while( current_sum > total_sum - x && l <= r )
            {
                current_sum -= nums[l];
                l++;
            }
            
            if ( current_sum == total_sum - x )
                max_len = max(max_len,r-l+1);
        }
        
        return max_len == -1 ? -1 : n - max_len;
    }
};

// Same idea, but  we can also maintain and check the sum on the left and right sides. 
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total_sum = accumulate(nums.begin(),nums.end(),0), current_sum = total_sum;
        int l = 0, res = INT_MAX, n = nums.size();
        for ( int r = 0; r < n; r++ )
        {
            current_sum -= nums[r];
            while( current_sum < x && l <= r )
            {
                current_sum += nums[l++];
            }
            
            if ( current_sum == x )
            {
                res = min(res,n - r + l - 1);
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};