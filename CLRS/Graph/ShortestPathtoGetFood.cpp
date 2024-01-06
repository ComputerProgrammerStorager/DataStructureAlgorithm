/*
You are starving and you want to eat food as quickly as possible. You want to find the shortest path to arrive at any food cell.

You are given an m x n character matrix, grid, of these different types of cells:

'*' is your location. There is exactly one '*' cell.
'#' is a food cell. There may be multiple food cells.
'O' is free space, and you can travel through these cells.
'X' is an obstacle, and you cannot travel through these cells.
You can travel to any adjacent cell north, east, south, or west of your current location if there is not an obstacle.

Return the length of the shortest path for you to reach any food cell. If there is no path for you to reach food, return -1.

 

Example 1:


Input: grid = [["X","X","X","X","X","X"],["X","*","O","O","O","X"],["X","O","O","#","O","X"],["X","X","X","X","X","X"]]
Output: 3
Explanation: It takes 3 steps to reach the food.
Example 2:


Input: grid = [["X","X","X","X","X"],["X","*","X","O","X"],["X","O","X","#","X"],["X","X","X","X","X"]]
Output: -1
Explanation: It is not possible to reach the food.
Example 3:


Input: grid = [["X","X","X","X","X","X","X","X"],["X","*","O","X","O","#","O","X"],["X","O","O","X","O","O","X","X"],["X","O","O","O","O","#","O","X"],["X","X","X","X","X","X","X","X"]]
Output: 6
Explanation: There can be multiple food cells. It only takes 6 steps to reach the bottom food.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[row][col] is '*', 'X', 'O', or '#'.
The grid contains exactly one '*'.


*/

class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int res = 0, m = grid.size(), n = grid[0].size();
        queue<pair<int,int>> q;
        pair<int,int> dirs[] = {{-1,0},{1,0},{0,1},{0,-1}};
        bool found = false;
        for ( int i = 0; i < m && !found; i++ ) 
            for ( int j = 0; j < n; j++ ) {
                if ( grid[i][j] == '*' ) {
                    grid[i][j] = 'X';
                    q.emplace(i,j);
                    found = true;
                    break;
                }
            }

        while(!q.empty()) {
            int q_sz = q.size();
            for ( int i = 0; i < q_sz; i++ ) {
                auto [x,y] = q.front();
                q.pop();
                for ( auto d : dirs ) {
                    int n_x = d.first + x, n_y = d.second + y;
                    if ( n_x < 0 || n_y < 0 || n_x == m || n_y == n )
                        continue;
                    if ( grid[n_x][n_y] == '#' )
                        return res + 1;
                    if ( grid[n_x][n_y] == 'O' ) {
                        grid[n_x][n_y] = 'X';
                        q.emplace(n_x,n_y);
                    }
                } 
            }
            res++;
        }
        return -1;
    }
};