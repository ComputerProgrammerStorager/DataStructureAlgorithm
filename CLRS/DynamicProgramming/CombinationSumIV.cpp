/*
Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.

 

Example 1:

Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
Example 2:

Input: nums = [9], target = 3
Output: 0
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 1000
All the elements of nums are unique.
1 <= target <= 1000
 

Follow up: What if negative numbers are allowed in the given array? How does it change the problem? What limitation we need to add to the question to allow negative numbers?

*/

// since the order matters, then the current choice would impact the next choice. 
// we remember the number of valid combinations for a target sum 
// top-down 
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        unordered_map<int,int> sum2comb;
        return combsum(nums,sum2comb,target);
    }
    
    int combsum(vector<int> const& nums, unordered_map<int,int> &sum2comb, int rem)
    {
        if ( rem == 0 )
            return 1;
        if ( sum2comb.count(rem) )
            return sum2comb[rem];
        int cnt = 0;
        for ( int n : nums )
        {
            if ( n > rem )
                continue;
            cnt += combsum(nums,sum2comb,rem-n);
        }
        
        return sum2comb[rem] = cnt;
    
    }
};

// if we sort the nums, then we can break early 
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        unordered_map<int,int> sum2comb;
        sort(nums.begin(),nums.end());
        return combsum(nums,sum2comb,target);
    }
    
    int combsum(vector<int> const& nums, unordered_map<int,int> &sum2comb, int rem)
    {
        if ( rem == 0 )
            return 1;
        if ( sum2comb.count(rem) )
            return sum2comb[rem];
        int cnt = 0;
        for ( int n : nums )
        {
            if ( n > rem )
                break;
            cnt += combsum(nums,sum2comb,rem-n);
        }
        
        return sum2comb[rem] = cnt;
    }
};

// bottom-up build up the dp array: can sum problem 
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target+1,0);
        dp[0] = 1;
        for ( int i = 1; i <= target; i++ )
        {
            for ( auto n : nums )
            {
                if ( i >= n )
                    dp[i] += dp[i-n];
            }
        }
        
        return dp[target];
    }
};

// Regarding the follow-up, if we allow negative numbers in the array, then we could run into infinite number of combinations that sum up to 
// a given target sum. However, if we impose the limit each number may be used, we can have valid results. 