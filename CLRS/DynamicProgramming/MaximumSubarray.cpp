/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Example 2:

Input: nums = [1]
Output: 1
Example 3:

Input: nums = [0]
Output: 0
Example 4:

Input: nums = [-1]
Output: -1
Example 5:

Input: nums = [-100000]
Output: -100000
 

Constraints:

1 <= nums.length <= 3 * 104
-105 <= nums[i] <= 105
 

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// the key point is to identify the inflection point, it's the current sum is less than 0 
// dynamic programming: dp[i]: represent the maximum sum of nums[0...i].
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if ( n == 0 )
            return 0;
        int global_sum = nums[0];

        for ( int i = 1; i < n; i++)
        {
            if ( nums[i-1] >= 0 )
            {
                nums[i] += nums[i-1];
            }
            global_sum = max(global_sum,nums[i]);
        }
        
        return global_sum;
    }
};

// whenever we have a currently accumulative sum is less then 0, then we reset the current sum 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if ( n == 0 )
            return 0;
        int global_sum = INT_MIN;
        int cur_sum = 0;

        for ( int i = 0; i < n; i++)
        {   
            if ( cur_sum < 0 )
            {
                cur_sum = 0;
            }
            cur_sum += nums[i];
            global_sum = max(global_sum,cur_sum);
        }
        
        return global_sum;
    }
};


// Greedy algorithm: constantly maintain a local optimal and update the global sum every time the local optimal is updated
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if ( n == 0 )
            return 0;
        int global_sum = nums[0];
        int cur_sum = nums[0];

        for ( int i = 1; i < n; i++)
        {   
            cur_sum = max(nums[i],cur_sum+nums[i]);
            global_sum = max(cur_sum,global_sum);
        }
        
        return global_sum;
    }
};

// Divide and conquer
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return helper(nums,0,nums.size()-1);
    }
    
    int CrossSum( vector<int> const &nums, int l, int h, int c )
    {
        if ( l == h )
            return nums[l];
        int left_sum = INT_MIN, right_sum = INT_MIN;
        int cur_sum = 0;
        for ( int i = c; i >= l; i-- )
        {
            cur_sum += nums[i];
            left_sum = max(cur_sum,left_sum);
        }
        cur_sum = 0;
        for ( int i = c + 1; i <= h; i++ )
        {
            cur_sum += nums[i];
            right_sum = max(cur_sum,right_sum);
        }
        
        return left_sum + right_sum;
    }
    
    int helper( vector<int> const &nums, int l, int h)
    {
        if ( l == h )
            return nums[l];
        int mid = (l+h)/2;
        int left_sum = helper(nums,l,mid);
        int right_sum = helper(nums, mid+1,h);
        int cross_sum = CrossSum(nums,l,h,mid);
        return max(left_sum,max(right_sum,cross_sum));
    }
};