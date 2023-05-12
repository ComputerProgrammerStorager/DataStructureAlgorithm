/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/

// swap each num following the current idx with idx, and then backtrack 
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(res,nums,0);
        return res;
    }

private:
    void backtrack(vector<vector<int>> &res, vector<int> &nums, int start)
    {
        if ( start == nums.size() )
            res.push_back(nums);
        for ( int idx = start; idx < nums.size(); idx++ )
        {
            swap(nums[start],nums[idx]);
            backtrack(res,nums,start+1);
            swap(nums[start],nums[idx]);
        }
    }
};