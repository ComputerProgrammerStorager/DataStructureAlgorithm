/*
There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.

Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.

 

Example 1:


Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
Output: 6
Example 2:


Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
Output: 12
 

Constraints:

1 <= m, n <= 50
0 <= maxMove <= 50
0 <= startRow < m
0 <= startColumn < n

*/

// we can perceive it as a bfs problem, i.e., each step can have severa positions that consist of its current "state"
// Note that we should not use a visited array to track if a cell has been visited or not, because a cell should be allowed to visit multiple times 
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        int ans = 0;
        queue<pair<int,int>> q;
        q.push({startRow,startColumn});
        pair<int,int> dirs[4] = {{1,0},{-1,0},{0,1},{0,-1}};
        for ( int i = 1; i <= maxMove; i++ )
        {
            int q_sz = q.size();
            for ( int j = 0; j < q_sz; j++ )
            {
                auto cur = q.front();
                q.pop();
                for ( auto d : dirs )
                {
                    int next_x = cur.first + d.first;
                    int next_y = cur.second + d.second;
                    if ( next_x < 0 || next_x >= m || next_y < 0 || next_y >= n )
                    {
                        ans++;
                        ans %= 1000000007;
                    }
                    else
                    {
                        q.push({next_x,next_y});
                    }
                }
            }
        }
        
        return ans;
    }
};

// We could use recursion 
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        if ( startRow < 0 || startColumn < 0 || startRow == m || startColumn == n )
            return 1;
        if ( maxMove == 0 )
            return 0;
        return findPaths(m,n,maxMove-1,startRow+1,startColumn)
              + findPaths(m,n,maxMove-1,startRow-1,startColumn)
              + findPaths(m,n,maxMove-1,startRow,startColumn+1)
              + findPaths(m,n,maxMove-1,startRow,startColumn-1);
    }
};

// we can add memoization to improve complexity 
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        unordered_map<string,long> memo;
        return dfs(m,n,maxMove,startRow,startColumn, memo);
    }
    int dfs(int m, int n, int N, int i, int j, unordered_map<string,long> &memo)
    {
        string key = to_string(i) + "+" + to_string(j) + "+" + to_string(N);
        if ( i < 0 || i >= m || j < 0 || j >= n )
            return 1;
        if ( N == 0 )
            return 0;
        if ( memo.count(key) ) 
            return memo[key];
        memo[key] = (((dfs(m,n,N-1,i+1,j,memo) % 1000000007)
                   + (dfs(m,n,N-1,i-1,j,memo) % 1000000007)) % 1000000007)
                   + (((dfs(m,n,N-1,i,j+1,memo) % 1000000007)
                   + (dfs(m,n,N-1,i,j-1,memo) % 1000000007)) % 1000000007);
        memo[key] %= 1000000007;
        return memo[key];
    }
};

// we can convert the above recursion + memo to dynamic programming solution 
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        int M = 1e9 + 7;
        int cnt = 0;
        vector<vector<int>> dp(m,vector<int>(n,0));
        dp[startRow][startColumn] = 1;
        for ( int step = 1; step <= maxMove; step++ )
        {
            vector<vector<int>> tmp(dp);
            for ( int i = 0; i < m; i++ )
                for ( int j = 0; j < n; j++ )
                {
                    if ( i == m-1 )
                        cnt = (cnt+dp[i][j]) % M;
                    if ( j == n-1 )
                        cnt = (cnt+dp[i][j]) % M;
                    if ( i == 0 )
                        cnt = (cnt+dp[i][j]) % M;
                    if ( j == 0 )
                        cnt = (cnt+dp[i][j]) % M;
                    tmp[i][j] = (((i>0 ? dp[i-1][j] : 0) + (i < m-1 ? dp[i+1][j] : 0 )) % M 
                                + ((j>0 ? dp[i][j-1] : 0) + (j < n-1 ? dp[i][j+1] : 0)) % M) % M;
                }
            dp.swap(tmp);
        }
        
        return cnt;
    }

};