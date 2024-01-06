/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

 

Example 1:


Input: grid = [[0,1],[1,0]]
Output: 2
Example 2:


Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4
Example 3:

Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 100
grid[i][j] is 0 or 1
*/

// BFS to find the shortest path 
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int res = 0, m = grid.size(), n = grid[0].size();
        queue<pair<int,int>> q;
        pair<int,int> dirs[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        if ( grid[0][0] || grid[m-1][n-1] ) 
            return -1;
        q.push({0,0});
        grid[0][0] = 2;
        bool reached = false;
        while( !q.empty() && !reached ) {
            int cur_sz = q.size();
            res++;
            for (int i = 0; i < cur_sz; i++ )
            {
                int cur_x = q.front().first, cur_y = q.front().second;
                q.pop();
                if ( cur_x == m-1 && cur_y == n-1 )
                {
                    reached = true;
                    break;
                }
                for ( auto d : dirs )
                {
                    int next_x = d.first + cur_x, next_y = d.second + cur_y;
                    if ( next_x < 0 || next_y < 0 || next_x == m || next_y == n )
                        continue;
                    if ( grid[next_x][next_y] == 0 )
                    {
                        grid[next_x][next_y] = 2;
                        q.push({next_x,next_y});
                    }
                }
            }
        }

        return reached ? res : -1 ;
    }
};