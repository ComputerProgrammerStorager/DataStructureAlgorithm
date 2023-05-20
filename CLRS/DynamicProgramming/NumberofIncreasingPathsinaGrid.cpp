/*
You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.

Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.

Two paths are considered different if they do not have exactly the same sequence of visited cells.

 

Example 1:


Input: grid = [[1,1],[3,4]]
Output: 8
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [1], [3], [4].
- Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
- Paths with length 3: [1 -> 3 -> 4].
The total number of paths is 4 + 3 + 1 = 8.
Example 2:

Input: grid = [[1],[2]]
Output: 3
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [2].
- Paths with length 2: [1 -> 2].
The total number of paths is 2 + 1 = 3.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
1 <= grid[i][j] <= 105
*/

// thought process: 
// If a cell is a valley, then the number of paths is 1. 
// If a cell has known it's paths, then it can be used to update the its neighbors (which are larger than its value)
// When we say a cell "has known it's number of paths", it means this cell has already been updated and it's no going to be updated again in any case
// this implies we could do the update in the order of the given cell values. In doing so, once a cell has been processed, it would be updated again. 
class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        if ( grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int m = grid.size(), n = grid[0].size(), res = 0, mod = 1000000007;
        vector<vector<int>> value2pos;
        vector<vector<int>> dp(m,vector<int>(n,1));
        int dirs[] = {0,1,0,-1,0};
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                value2pos.push_back({grid[i][j],i,j});
            }
        sort(value2pos.begin(),value2pos.end());
        for (auto pos : value2pos )
        {
            int x = pos[1], y = pos[2], val = pos[0];
            for ( int d = 0; d < 4; d++ )
            {
                int n_x = x + dirs[d], n_y = y + dirs[d+1];
                if ( n_x < 0 || n_x == m || n_y < 0 || n_y == n || grid[n_x][n_y] <= grid[x][y] )
                    continue;
                dp[n_x][n_y] += dp[x][y];
                dp[n_x][n_y] %= mod;
            }
        }

        for ( int i = 0; i < m; i++)
            for ( int j = 0; j < n; j++ )
            {
                res += dp[i][j];
                res %= mod;
            }
        return res;
    }
};


// we can use dfs and memorization 
class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        if ( grid.size() == 0 || grid[0].size() == 0 )
            return 0;
        int m = grid.size(), n = grid[0].size(), sum = 0, mod = 1000000007;
        vector<vector<int>> dp(m,vector<int>(n,0));
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                sum += dfs(grid,i,j,dp);
                sum %= mod;
            }
        return sum;
    }
private:
    int dfs(const vector<vector<int>>& grid, int x, int y, vector<vector<int>>& dp)
    {
        if ( dp[x][y] != 0 )
            return dp[x][y];
        int cnt = 1;
        int dirs[] = {0,1,0,-1,0};
        for (int d = 0; d < 4; d++ )
        {
            int n_x = x + dirs[d], n_y = y + dirs[d+1];
            if ( n_x < 0 || n_x == grid.size() || n_y < 0 || n_y == grid[0].size() || grid[x][y] >= grid[n_x][n_y] )
                continue;
            cnt += dfs(grid,n_x,n_y,dp);
        }

        return dp[x][y] = cnt % 1000000007;
    }
};