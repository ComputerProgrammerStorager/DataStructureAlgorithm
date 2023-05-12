/*
You are given an n x n binary matrix grid where 1 represents land and 0 represents water.

An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.

You may change 0's to 1's to connect the two islands to form one island.

Return the smallest number of 0's you must flip to connect the two islands.

 

Example 1:

Input: grid = [[0,1],[1,0]]
Output: 1
Example 2:

Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:

Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 

Constraints:

n == grid.length == grid[i].length
2 <= n <= 100
grid[i][j] is either 0 or 1.
There are exactly two islands in grid.
*/

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        set<pair<int,int>> s,visited;
        queue<pair<int,int>> q;
        int dirs[] = {0,1,0,-1,0};
        if ( grid.size() == 0 || grid[0].size() == 0 )
            return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        int x, y; 
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                if ( grid[i][j] == 1 )
                {
                    x = i, y = j, i = m, j = n;
                }
            }
        dfs( grid,x,y,s);
        for ( auto it : s )
        {
            q.push(it);
            visited.insert(it);
        }

        while( !q.empty() )
        {
            int cur_sz = q.size();
            for ( int i = 0; i < cur_sz; i++ )
            {
                auto [x,y] = q.front();
                q.pop();
                for ( int d = 0; d < 4; d++ )
                {
                    int n_x = x+dirs[d], n_y = y+dirs[d+1];
                    if ( n_x < 0 || n_x >= m || n_y < 0 || n_y >= n || visited.count(make_pair(n_x,n_y)) )
                        continue;
                    if ( grid[n_x][n_y] == 1 )
                        return res;
                    q.push(make_pair(n_x,n_y));
                    visited.insert(make_pair(n_x,n_y));
                }
            }
            res++;
        }

        return -1;
    }

private:
    void dfs(vector<vector<int>>& grid, int x, int y, set<pair<int,int>>& s)
    {
        if ( x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()|| grid[x][y] == 0 || s.count(make_pair(x,y)) )
            return;
        s.insert(make_pair(x,y));
        dfs(grid,x+1,y,s);
        dfs(grid,x,y+1,s);
        dfs(grid,x-1,y,s);
        dfs(grid,x,y-1,s);
    }
};