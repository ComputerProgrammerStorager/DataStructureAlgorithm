/*
Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/

// we can use bit manipulation to represent all subsets. 
// Note: first push the empty subset first 
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back({});
        int n = nums.size();
        for ( int i = 1; i < (1<<n); i++ )
        {
            vector<int> cur;
            for ( int j = 0; j < n; j++ )
            {
                if ( i & (1<<j) )
                    cur.push_back(nums[j]);
            }
            res.push_back(cur);
        }
        
        return res;
    }
};

// the above method has a problem if it size if larger than 32 or 64 due to the shift position,
// dfs for each position we could either select or not 
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        dfs(0,nums,cur,res);
        return res;
    }
    
    void dfs(int idx, vector<int> const& nums, vector<int> &cur, vector<vector<int>> &res)
    {
        if ( idx == nums.size() )
        {
            res.push_back(cur);
            return;
        }
        cur.push_back(nums[idx]);
        dfs(idx+1,nums,cur,res);
        cur.pop_back();
        dfs(idx+1,nums,cur,res);
    }
};

// similar to the dfs idea, but expanding the current subsets by including the next number, while also retaining the existing subsets to 
// eumulate the next number not selected
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res(1);
        for ( int i = 0; i < nums.size(); i++ )
        {
            int sz = res.size();
            for ( int j = 0; j < sz; j++ )
            {
                res.push_back(res[j]);
                res.back().push_back(nums[i]);
            }
        }
        
        return res;
    }
};