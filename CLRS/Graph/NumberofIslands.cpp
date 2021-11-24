/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/
// Bfs starting from any '1' pos and bfs all connected nodes. 
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int islands = 0;
        vector<pair<int,int>> dir{{0,1},{0,-1},{1,0},{-1,0}};
        int m = grid.size(), n = grid[0].size();
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            if ( grid[i][j] == '1' )
            {
                islands++;
                bfs(grid,i,j,dir);
            }
        
        return islands;
    }
    
    void bfs(vector<vector<char>> &grid, int i, int j, vector<pair<int,int>> const& dir)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int>> pos;
        pos.push({i,j});
        grid[i][j] = '0';
        while(!pos.empty())
        {
            int cur_x = pos.front().first;
            int cur_y = pos.front().second;
            pos.pop();
            for ( auto d : dir )
            {
                int next_x = cur_x + d.first;
                int next_y = cur_y + d.second;
                if ( next_x >= m || next_x < 0 || next_y >= n || next_y < 0 )
                    continue;
                if ( grid[next_x][next_y] == '1' )
                {
                    grid[next_x][next_y] = '0';
                    pos.push({next_x,next_y});
                }
            }
        }
    }
};

// DFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int islands = 0;
        vector<pair<int,int>> dir{{0,1},{0,-1},{1,0},{-1,0}};
        int m = grid.size(), n = grid[0].size();
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ ) 
            {
                if ( grid[i][j] == '1' )
                {
                    islands++;
                    dfs(grid,i,j,dir);
                }
            }
        return islands;
    }
    
    void dfs(vector<vector<char>> &grid, int i, int j, vector<pair<int,int>> const& dir)
    {
        int m = grid.size();
        int n = grid[0].size();
        grid[i][j] = '0';
        for ( auto d : dir )
        {
            int next_x = i + d.first;
            int next_y = j + d.second;
            if ( next_x >= m || next_x < 0 || next_y >= n || next_y < 0 )
                continue;
            if ( grid[next_x][next_y] == '1' )
            {
                dfs(grid,next_x,next_y,dir);
            }
        }
    }
};