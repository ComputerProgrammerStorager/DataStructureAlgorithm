/*
Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

 

Example 1:



Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).
Example 2:



Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2
 

Constraints:

1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1
*/

// First, we use DFS(union find) to get all the islands consisting of all 0s components 
// Second, we check if an island is closed or not. if any of it's node is adjcent to boundary, then it's not closed

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        vector<set<pair<int,int>>> islands;
        set<pair<int,int>> visited;
        int res = 0;
        if ( grid.size() == 0 || grid[0].size() == 0 )
            return 0;
        int m = grid.size(), n = grid[0].size(); 
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                if ( grid[i][j] == 0 && !visited.count(make_pair(i,j)) )
                {
                    set<pair<int,int>> curisland;
                    dfs(grid,i,j,visited,curisland);
                    islands.push_back(curisland);
                }
            }

        for ( auto it : islands )
        {
           if ( islandclosed(it,m,n) )
                res++;
        }
        return res;
    }
private: 
    void dfs(const vector<vector<int>>& grid, int x, int y, set<pair<int,int>>& visited, set<pair<int,int>>& curisland)
    {
        if ( x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || visited.count(make_pair(x,y)) || grid[x][y] == 1 )
            return;
        curisland.insert(make_pair(x,y));
        visited.insert(make_pair(x,y));
        int dirs[] = {0,1,0,-1,0};
        for ( int d = 0; d < 4; d++ )
        {
            dfs(grid,x+dirs[d],y+dirs[d+1],visited, curisland);
        }
    }
    bool islandclosed(const set<pair<int,int>>& pos, int m, int n)
    {
        int dirs[] = {0,1,0,-1,0};
        for ( auto cur : pos )
        {
            for ( int d = 0; d < 4; d++ )
            {
                int n_x = cur.first + dirs[d];
                int n_y = cur.second + dirs[d+1];
                if ( n_x < 0 || n_x == m || n_y < 0 || n_y == n )
                    return false;
            }
        }

        return true;
    }
};