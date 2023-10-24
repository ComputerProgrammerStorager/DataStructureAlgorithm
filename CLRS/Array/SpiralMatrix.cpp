/*
Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
*/


// maintain the current boundaries, traverse and update the boundaries for the next round 
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        int left = 0, right = col-1, up = 0, down = row-1;
        vector<int> res;
        while( res.size() < row * col )
        {
            for ( int c = left; c <= right; c++ )
                res.push_back(matrix[up][c]);
            for ( int r = up+1; r <= down; r++ )
                res.push_back(matrix[r][right]);
            if ( up != down )
            {
                for ( int c = right - 1; c >= left; c-- )
                    res.push_back(matrix[down][c]);
            }
            if ( left != right )
            {
                for ( int r = down-1; r > up; r-- )
                    res.push_back(matrix[r][left]);
            }

            left++;
            right--;
            up++;
            down--;
        }

        return res;
    }
};


// stick to one direction until it hits boundary and terminate when direction is changed twice 
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        int mark = 101;
        int rows = matrix.size(), cols = matrix[0].size(); 
        int cur_dir = 0, change_dir = 0;
        vector<int> res;
        res.push_back(matrix[0][0]);
        int cur_row = 0, cur_col = 0;
        matrix[0][0] = mark;
        while( change_dir < 2 )
        {
            int new_row = cur_row + dirs[cur_dir][0], new_col = cur_col + dirs[cur_dir][1];
            while( new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols && matrix[new_row][new_col] != mark )
            {
                res.push_back(matrix[new_row][new_col]);
                matrix[new_row][new_col] = mark;
                change_dir = 0;
                cur_row = new_row;
                cur_col = new_col;
                new_row = cur_row + dirs[cur_dir][0];
                new_col = cur_col + dirs[cur_dir][1];
            }
            change_dir++;
            cur_dir = (cur_dir+1) % 4;
        }

        return res;
    }
};