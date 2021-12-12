/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
 

Constraints:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30

*/

// Idea: 
// Since we need unique combinations, we keep a start position from the candidates 
// Since the numbers can be duplicates, we thus need to maintain its frequency and update the status when select and backtracking 
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        vector<vector<int>> res;
        vector<int> ans;
        unordered_map<int,int> m;
        vector<pair<int,int>> cans;
        for ( auto n : nums )
            m[n]++;
        for ( auto it : m )
            cans.push_back({it.first,it.second});
        dfs(res,ans,cans,0,target);
        return res;
    }
    
    void dfs(vector<vector<int>> &res, vector<int> &ans, vector<pair<int,int>> &cans, int start, int rem)
    {
        if ( rem == 0 )
        {
            res.push_back(ans);
            return;
        }
        if ( start == cans.size() || rem < 0 )
        {
            return;
        }
        
        for ( int step = start; step < cans.size(); step++ )
        {
            if ( cans[step].first > rem || cans[step].second <= 0 )
                continue;
            cans[step].second--;
            ans.push_back(cans[step].first);
            dfs(res,ans,cans,step,rem-cans[step].first);
            cans[step].second++;
            ans.pop_back();
        }
    }
};