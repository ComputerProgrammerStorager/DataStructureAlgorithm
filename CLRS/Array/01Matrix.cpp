/**
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:


Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
Example 2:


Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
There is at least one 0 in mat.
 * 
 */

// start from all 0s and BFS.. only push new postions which have just updated
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows= mat.size();
        if ( rows == 0 )
            return mat;
        int cols = mat[0].size();
        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        vector<vector<int>> res(rows,vector<int>(cols,INT_MAX));
        queue<pair<int,int>> q;
        for ( int i = 0; i < rows; i++ )
            for ( int j = 0; j < cols; j++ )
                if ( mat[i][j] == 0 )
                {
                    res[i][j] = 0;
                    q.push({i,j});
                }

        while(!q.empty())
        {
            int cur_r = q.front().first;
            int cur_c = q.front().second;
            q.pop();
            for ( int i = 0; i < 4; i++ )
            {
                int next_r = cur_r + dir[i][0];
                int next_c = cur_c + dir[i][1];
                if ( next_r >= 0 && next_c >= 0 && next_r < rows && next_c < cols )
                {
                    if ( res[next_r][next_c] > res[cur_r][cur_c] + 1 )
                    {
                        res[next_r][next_c] = res[cur_r][cur_c] + 1;
                        q.push({next_r,next_c});
                    }
                }
            }
        }

        return res;
    }
};


// Method 2: dynamic programming two passes 
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        if ( rows == 0 )
            return mat;
        int cols = mat[0].size();
        vector<vector<int>> res(rows,vector<int>(cols,INT_MAX-100));

        // First pass: left top to bottom right 
        for ( int i = 0; i < rows; i++ )
            for ( int j = 0; j < cols; j++ )
            {
                if ( mat[i][j] == 0 )
                {
                    res[i][j] = 0;
                }
                else 
                {
                    if ( i > 0 )
                        res[i][j] = min(res[i][j],res[i-1][j] + 1);
                    if ( j > 0 )
                        res[i][j] = min(res[i][j], res[i][j-1] + 1);
                }
            }
        // second pass: bottom and right 
        for ( int i = rows - 1; i >= 0; i-- )
            for ( int j = cols - 1; j >= 0; j--)
            {
                if ( i < rows-1)
                    res[i][j] = min(res[i][j],res[i+1][j] + 1);
                if ( j < cols-1)
                    res[i][j] = min(res[i][j], res[i][j+1] + 1 );
            }

        return res;
        
    }
};