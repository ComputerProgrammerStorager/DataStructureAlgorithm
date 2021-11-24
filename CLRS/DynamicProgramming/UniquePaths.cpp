/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

 

Example 1:


Input: m = 3, n = 7
Output: 28
Example 2:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
Example 3:

Input: m = 7, n = 3
Output: 28
Example 4:

Input: m = 3, n = 3
Output: 6
 

Constraints:

1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 109.

*/

// The results of [m,n] depends on [m-1,n] and [m,n-1].
//  So recursion + memo 
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> memo(m,vector<int>(n,0));
        return dfs(m-1,n-1,memo);
    }

    int dfs(int m, int n,vector<vector<int>> &memo)
    {
        if ( m == 0 || n == 0 )
            return memo[m][n] = 1;
        if ( memo[m][n] != 0 )
            return memo[m][n];
        return memo[m][n] = dfs(m-1,n,memo) + dfs(m,n-1,memo);
    }
};

// can easily translate it to dynamic programming solution 
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,0));
        if ( m == 0 || n == 0 )
            return 0;
        for ( int r = 0; r < m; r++ )
            dp[r][0] = 1;
        for ( int c = 0; c < n; c++ )
            dp[0][c] = 1;
        for ( int r = 1; r < m; r++ )
            for ( int c = 1; c < n; c++ )
                dp[r][c] = dp[r-1][c] + dp[r][c-1];
        
        return dp[m-1][n-1];
    }
};