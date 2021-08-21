/*
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.

*/

// this is classic BFS problem, with the initial state to contain all rotted oranges 
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        //1. calcualte the number of fresh oranges, if there is no fresh orange, then it takes zero time
        //2. Otherwise, use BFS to traverse
        queue<pair<int,int>> q; 
        int m = grid.size();
        int n = grid[0].size();
        int fresh_orange = 0, time = -1;
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        vector<pair<int,int>> dir = {{-1,0},{1,0},{0,-1},{0,1}};
        for ( int r = 0; r < m; r++ )
            for ( int c = 0; c < n; c++ )
            {
                switch(grid[r][c]) 
                {
                    case 2: 
                        q.push({r,c});
                        visited[r][c] = true;
                        break;
                    case 1:
                        fresh_orange++;
                        break;
                    default:
                        break;
                }
            }
        if ( fresh_orange == 0 )
            return 0;
        while ( fresh_orange && !q.empty() )
        {
            int cur_sz = q.size();
            for ( int i = 0; i < cur_sz; i++ )
            {
                int cur_x = q.front().first;
                int cur_y = q.front().second;
                q.pop();
                if ( grid[cur_x][cur_y] == 1 )
                    fresh_orange--;
                for ( int d = 0; d < 4; d++ )
                {
                    int next_x = cur_x + dir[d].first;
                    int next_y = cur_y + dir[d].second;
                    if ( next_x < 0 || next_x >= m || next_y < 0 || next_y >= n )
                        continue;
                    if ( !visited[next_x][next_y] && grid[next_x][next_y] == 1 )
                    {
                        visited[next_x][next_y] = true;
                        q.push({next_x,next_y});
                    }
                }
            }
            time++;
        }
        
        return fresh_orange == 0 ? time : -1;
    }
};

// we can modify the grid itself to avoid using additional memory for visited tracking
// Note: in this solution time is NOT initilialized to -1 one, because the last level of fresh orange is not enterred into the loop. 
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        //1. calcualte the number of fresh oranges, if there is no fresh orange, then it takes zero time
        //2. Otherwise, use BFS to traverse
        queue<pair<int,int>> q; 
        int m = grid.size();
        int n = grid[0].size();
        int fresh_orange = 0, time = 0;
        vector<pair<int,int>> dir = {{-1,0},{1,0},{0,-1},{0,1}};
        for ( int r = 0; r < m; r++ )
            for ( int c = 0; c < n; c++ )
            {
                switch(grid[r][c]) 
                {
                    case 2: 
                        q.push({r,c});
                        break;
                    case 1:
                        fresh_orange++;
                        break;
                    default:
                        break;
                }
            }
        if ( fresh_orange == 0 )
            return 0;
        while ( fresh_orange && !q.empty() )
        {
            int cur_sz = q.size();
            for ( int i = 0; i < cur_sz; i++ )
            {
                int cur_x = q.front().first;
                int cur_y = q.front().second;
                q.pop();
                for ( int d = 0; d < 4; d++ )
                {
                    int next_x = cur_x + dir[d].first;
                    int next_y = cur_y + dir[d].second;
                    if ( next_x < 0 || next_x >= m || next_y < 0 || next_y >= n )
                        continue;
                    if ( grid[next_x][next_y] == 1 )
                    {
                        grid[next_x][next_y] = 2;
                        q.push({next_x,next_y});
                        fresh_orange--;
                    }
                }
            }
            time++;
        }
        
        return fresh_orange == 0 ? time : -1;
    }
};