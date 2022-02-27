/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

// Sort the numbers and fix the first number and check the remaining two numbers 
// Note: when we find a triplet, then we need to move both l and r, because move 
// only one would not lead to a zero sum. 
// Also: if we find duplicate of first and second number, we need to just skip it, 
// as it would only lead to duplicate triplet.
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for ( int i = 0; i < n && nums[i] <= 0; i++ )
        {
            int l = i+1, r = n-1;
            if ( i > 0 && nums[i] == nums[i-1] )
                continue;
            while( l < r )
            {
                int sum = nums[i] + nums[l] + nums[r];
                if ( sum == 0 )
                {
                    res.push_back({nums[i],nums[l++],nums[r--]});
                    while( l < r && nums[l] == nums[l-1] )
                        l++;
                }
                else if ( sum > 0 )
                {
                    r--;
                }
                else 
                {
                    l++;
                }
            }
        }
        
        return res;
    }
}; 