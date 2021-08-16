/*
You are given a 2D integer array groups of length n. You are also given an integer array nums.

You are asked if you can choose n disjoint subarrays from the array nums such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0, the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).

Return true if you can do this task, and false otherwise.

Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray. A subarray is a contiguous sequence of elements within an array.

 

Example 1:

Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
Output: true
Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
These subarrays are disjoint as they share no common nums[k] element.
Example 2:

Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
Output: false
Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and [1,2,3,4,10,-2] is incorrect because they are not in the same order as in groups.
[10,-2] must come before [1,2,3,4].
Example 3:

Input: groups = [[1,2,3],[3,4]], nums = [7,7,1,2,3,4,7,7]
Output: false
Explanation: Note that choosing the subarrays [7,7,1,2,3,4,7,7] and [7,7,1,2,3,4,7,7] is invalid because they are not disjoint.
They share a common elements nums[4] (0-indexed).
 

Constraints:

groups.length == n
1 <= n <= 103
1 <= groups[i].length, sum(groups[i].length) <= 103
1 <= nums.length <= 103
-107 <= groups[i][j], nums[k] <= 107
*/

#include "../Common/common_api.h"

// brute force solution 
class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int pos = 0, res;
        for ( int i = 0; i < groups.size(); i++ )
        {
            res = find(nums,groups[i],pos);
            if ( res == -1 )
                return false;
            pos = res + groups[i].size();
        }
        
        return true;
    }
    
    int find(vector<int> const &nums, vector<int> const &target, int start_pos)
    {
        int m = nums.size(), n = target.size(), res = -1;
        int j;
        for ( int i = start_pos; i <= m-n; i++ )
        {
            for ( j = 0; j < n; j++ )
            {
                if ( nums[i+j] != target[j] )
                    break;
            }
            if ( j == n )
            {
                res = i;
                break;
            }
        }
        return res;
    }
};

// KMP idea
class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int pos = 0, res;
        vector<vector<int>> lsp = preprocess(groups);
        for ( int i = 0; i < groups.size(); i++ )
        {
            if ( pos >= nums.size() )
                return false;
            pos = find(nums,groups[i],pos,lsp[i]);
            if ( pos == -1 )
                return false;
            pos += groups[i].size();
        }
        
        return true;
    }
    
    int find(vector<int> const &nums, vector<int> const &target, int start_pos, vector<int> const& lsp)
    {
        int res = -1, m = nums.size(), n = target.size();
        vector<int> dp(m);
        if ( start_pos >= m )
            return -1;
        dp[start_pos] = (target[0] == nums[start_pos]);
        if ( n == 1 && dp[start_pos] == 1 )
            return start_pos;
        for ( int i = start_pos + 1; i < m; i++ )
        {
            int j = dp[i-1];
            while ( j > 0 && nums[i] != target[j] )
                j = lsp[j-1];
            dp[i] = j + (target[j] == nums[i]);
            if ( dp[i] == n )
                return i-n+1;
        }
        return -1;
    }
    
    vector<vector<int>> preprocess(vector<vector<int>> &groups)
    {
        vector<vector<int>> res;
        for ( auto &g : groups )
        {
            int n = g.size();
            vector<int> dp(n);
            dp[0] = 0;
            for ( int i = 1; i < n; i++ )
            {
                int j = dp[i-1];
                while ( j > 0 && g[j] != g[i] )
                    j = dp[j-1];
                dp[i] = j + (g[j] == g[i]);
            }
            res.push_back(dp);
        }
        
        return res;
    }
};


int main()
{
    vector<vector<int>> groups = {{1,2,3},{3,4}};
    vector<int> nums{7,7,1,2,3,4,7,7};
    Solution s;
    s.canChoose(groups,nums);
}