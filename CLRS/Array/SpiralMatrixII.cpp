/*
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

 

Example 1:


Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]
Example 2:

Input: n = 1
Output: [[1]]
 

Constraints:

1 <= n <= 20
*/

// Same as boundar method
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n));
        int left = 0, right = n-1, up = 0, down = n - 1, val = 1;
        while( val <= n*n )
        {
            for ( int c = left; c <= right; c++ )
                res[up][c] = val++;
            for ( int r = up+1; r <= down; r++ )
                res[r][right] = val++;
            if ( up != down )
            {
                for ( int c = right-1; c >= left; c-- )
                    res[down][c] = val++;
            }
            if ( left != right )
            {
                for ( int r = down-1; r > up; r-- )
                    res[r][left] = val++;
            }
            left++;
            right--;
            up++;
            down--;
        }

        return res;
    }
};