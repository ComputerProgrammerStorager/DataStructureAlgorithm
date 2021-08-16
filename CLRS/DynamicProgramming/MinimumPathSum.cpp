/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12
*/

// dynamical programming as it has suboptimal structure, i.e., to arrive grid[i][j], it must either come from the up(grid[i-1][j]) or the left grid[i][j-1]
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if ( m == 0 || n == 0 )
            return 0;
        vector<vector<int>> dp(m,vector(n,0));
        dp[0][0] = grid[0][0]; 
        for ( int r = 1; r < m; r++ )
        {
            dp[r][0] = dp[r-1][0] + grid[r][0];
        }
        for ( int c = 1; c < n; c++ )
        {
            dp[0][c] = dp[0][c-1] + grid[0][c];
        }
        
        for ( int r = 1; r < m; r++ )
            for ( int c = 1; c < n; c++ )
            {
                dp[r][c] = grid[r][c] + min(dp[r-1][c],dp[r][c-1]);
            }
        
        return dp[m-1][n-1];
    }
};

// recursion with memoization 
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        unordered_map<string,int> m;
        return helper(grid,0,0, m);
    }
    int helper( vector<vector<int>> const& grid, int r, int c, unordered_map<string,int> &m )
    {
        if ( m.count(to_string(r)+"+"+to_string(c)) )
            return m[to_string(r)+"+"+to_string(c)];
        if ( r == grid.size() || c == grid[0].size() )
            return INT_MAX;
        if ( r == grid.size()-1 && c == grid[0].size()-1 )
            return grid[r][c];
        return m[to_string(r)+"+"+to_string(c)] = grid[r][c] + min(helper(grid,r+1,c,m), helper(grid,r,c+1,m));
    }
};