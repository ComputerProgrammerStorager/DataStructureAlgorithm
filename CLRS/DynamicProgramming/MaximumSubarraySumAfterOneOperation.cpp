/*
You are given an integer array nums. You must perform exactly one operation where you can replace one element nums[i] with nums[i] * nums[i]. 

Return the maximum possible subarray sum after exactly one operation. The subarray must be non-empty.

 

Example 1:

Input: nums = [2,-1,-4,-3]
Output: 17
Explanation: You can perform the operation on index 2 (0-indexed) to make nums = [2,-1,16,-3]. Now, the maximum subarray sum is 2 + -1 + 16 = 17.
Example 2:

Input: nums = [1,-1,1,1,-1,-1,1]
Output: 4
Explanation: You can perform the operation on index 1 (0-indexed) to make nums = [1,1,1,1,-1,-1,1]. Now, the maximum subarray sum is 1 + 1 + 1 + 1 = 4.
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
*/

// we know how to find the maximum subarray, so we check each of them 
// O(n^2)
class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int max_sum = 0;
        int n = nums.size();
        for ( int i = 0; i < n; i++ )
        {
            int val = nums[i];
            nums[i] *= nums[i];
            max_sum = max(max_sum,MaxSubarray(nums,n));
            nums[i] = val;
        }
        
        return max_sum;
    }
    
    int MaxSubarray( vector<int> const &nums, int n )
    {
        if ( n == 0 )
            return 0;
        int cur_sum = nums[0];
        int max_sum = nums[0];
        for ( int i = 1; i < n; i++ )
        {
            if ( cur_sum < 0 )
            {
                cur_sum = 0;
            }
            cur_sum += nums[i];
            max_sum = max(cur_sum,max_sum);
        }
        
        return max_sum;
    }
};

// use dynamic programming:  in natrue it's simiar to the assemble line problem in the test book. 
// dp_change[i] represents the maximum subarray sum  of a[0..i] with only one change (square operation), dp_nochange[i] represents the maximum subarray sum without any changes. 
// then to calculate dp_change[i], it has two options:
// we square nums[i]: then val_change = dp_nochange[i-1] >= 0 ? dp_nochange[i-1] + nums[i] * nums[i] : nums[i] * nums[i];
// we don't sqaure nums[i]: then val_nochange = dp_change[i-1] >= 0 ? dp_change[i-1] >= 0 : dp_change[i-1] + nums[i] : nums[i];
// then do_change[i] = max(val_change,val_nochange)
class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int max_sum = INT_MIN;
        int n = nums.size();
        if ( n == 0 )
            return 0;
        vector<int> dp_nochange(n,0), dp_change(n,0);
        dp_nochange[0] = nums[0];
        for ( int i = 1; i < n; i++ )
        {
            if ( dp_nochange[i-1] >= 0 )
                dp_nochange[i] = dp_nochange[i-1] + nums[i];
            else 
                dp_nochange[i] = nums[i]; 
        }
        
        max_sum = dp_change[0] = nums[0] * nums[0];
        for ( int i = 1; i < n; i++ )
        {
            int val_change_i = dp_nochange[i-1] >= 0? dp_nochange[i-1] + nums[i] * nums[i] : nums[i] * nums[i];
            int val_nochange_i = dp_change[i-1] >= 0 ? dp_change[i-1] + nums[i] : nums[i];
            dp_change[i] = max(val_change_i, val_nochange_i);
            max_sum = max(max_sum,dp_change[i]);
        }
        
        return max_sum;
    }
};