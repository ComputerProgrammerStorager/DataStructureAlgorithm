/*
There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean 
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean 
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean 
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
Example 2:

Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
 

Constraints:

m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 105
*/

// Find the set of cells that are reachable to pacific and atlantic separately. and then return the intersection of the two result sets. 
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if ( heights.size() == 0 || heights[0].size() == 0 )
            return {};
        int m = heights.size(), n = heights[0].size();
        queue<pair<int,int>> pacific_q, atlantic_q;
        pair<int,int> dirs[4] = {{0,1},{0,-1},{1,0},{-1,0}};
        vector<vector<int>> pacific_reachable(m,vector<int>(n,0)), atlantic_reachable(m,vector<int>(n,0));
        vector<vector<int>> res;
        auto bfs = [&](queue<pair<int,int>>& q, vector<vector<int>>& reachable)
        {
            while(!q.empty())
            {
                auto [x,y] = q.front();
                q.pop();
                for ( int d = 0; d < 4; d++)
                {
                    int next_x = x + dirs[d].first, next_y = y + dirs[d].second;
                    if ( next_x < 0 || next_x >= m || next_y < 0 || next_y >= n || reachable[next_x][next_y] || heights[next_x][next_y] < heights[x][y] )
                        continue;
                    reachable[next_x][next_y] = 1;
                    q.emplace(next_x,next_y);
                }
            }
        };
        for ( int i = 0; i < m; i++ )
        {
            pacific_reachable[i][0] = 1;
            pacific_q.emplace(i,0);
            atlantic_reachable[i][n-1] = 1;
            atlantic_q.emplace(i,n-1);
        }

        for ( int i = 0; i < n; i++ )
        {
            pacific_reachable[0][i] = 1;
            pacific_q.emplace(0,i);
            atlantic_reachable[m-1][i] = 1;
            atlantic_q.emplace(m-1,i);
        }

        bfs(pacific_q,pacific_reachable);
        bfs(atlantic_q,atlantic_reachable);

        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
                if ( pacific_reachable[i][j] && atlantic_reachable[i][j] )
                    res.push_back({i,j});
        return res;
    }
};


// we can also use DFS 

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        if ( heights.size() == 0 || heights[0].size() == 0 )
            return res;
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> pacific_reachable(m,vector<int>(n,0)), atlantic_reachable(m,vector<int>(n,0));
        for ( int i = 0; i < m; i++ )
        {
            dfs(heights,i,0,pacific_reachable);
            dfs(heights,i,n-1,atlantic_reachable);
        }

        for ( int i = 0; i < n; i++ )
        {
            dfs(heights,0,i,pacific_reachable);
            dfs(heights,m-1,i,atlantic_reachable);
        }

        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
                if ( pacific_reachable[i][j] && atlantic_reachable[i][j] )
                    res.push_back({i,j});
        return res;
    }
private:
    void dfs(const vector<vector<int>> &heights, int x, int y, vector<vector<int>> &reachable, int cur_h = 0)
    {
        int m = heights.size(), n = heights[0].size(); 
        if ( x < 0 || x >= m || y < 0 || y >= n || reachable[x][y] || heights[x][y] < cur_h )
            return ;
        reachable[x][y] = 1;
        dfs(heights,x+1, y, reachable, heights[x][y]);
        dfs(heights,x,y+1, reachable, heights[x][y]);
        dfs(heights,x-1,y, reachable, heights[x][y]);
        dfs(heights,x,y-1,reachable, heights[x][y]);
    }
};