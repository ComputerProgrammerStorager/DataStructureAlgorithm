/*

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
Example 4:

Input: candidates = [1], target = 1
Output: [[1]]
Example 5:

Input: candidates = [1], target = 2
Output: [[1,1]]
 

Constraints:

1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500
*/

// backtracking problem typically involves making chioces at each step and move on (dfs), and then backtrack the already explored choice 
// and change to another choice. 
// In this case, at each step, we can consider all the numbers, but to reduce redundant paths, we limits out step to at least the current position 
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> can;
        dfs(res,candidates,can,0,target);
        return res;
    }
    
    void dfs(vector<vector<int>> &res, vector<int>& nums, vector<int>& cur_can, int pos, int rem)
    {
        if ( rem == 0 )
        {
            res.push_back(cur_can);
            return;
        }
        
        for ( int choice = pos; choice < nums.size(); choice++ )
        {
            if ( rem - nums[choice] < 0 )
                continue;
            cur_can.push_back(nums[choice]);
            dfs(res,nums,cur_can,choice,rem-nums[choice]);
            cur_can.pop_back();
        }
    }
};


// if we sort the numbers first, then we can cut branches quicker.. literally change "continue" to "break"

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> can;
        sort(candidates.begin(),candidates.end());
        dfs(res,candidates,can,0,target);
        return res;
    }
    
    void dfs(vector<vector<int>> &res, vector<int>& nums, vector<int>& cur_can, int pos, int rem)
    {
        if ( rem == 0 )
        {
            res.push_back(cur_can);
            return;
        }
        
        for ( int choice = pos; choice < nums.size(); choice++ )
        {
            if ( rem - nums[choice] < 0 )
                break;
            cur_can.push_back(nums[choice]);
            dfs(res,nums,cur_can,choice,rem-nums[choice]);
            cur_can.pop_back();
        }
    }
};