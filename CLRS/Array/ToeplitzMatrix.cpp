/*
Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.

A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.

 

Example 1:


Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: true
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.
Example 2:


Input: matrix = [[1,2],[2,2]]
Output: false
Explanation:
The diagonal "[1, 2]" has different elements.
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 20
0 <= matrix[i][j] <= 99
 

Follow up:

What if the matrix is stored on disk, and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
What if the matrix is so large that you can only load up a partial row into the memory at once?
*/

// for each non first row/column element, check if it equals to it's up-left 
// O(M*N) O(1)
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for ( int r = 0; r < m; r++ )
            for ( int c = 0; c < n; c++ )
                if ( r > 0 && c > 0 && matrix[r][c] != matrix[r-1][c-1] )
                    return false;
        return true;
    }
};

// the sufficient and necessary condition for two elements of [r1,c1] and [r2,c2] being on the diagonal 
// is that r1-c1 = r2-c2. we can map the coordinate diffence to the value 
// O(M*N), O(M+N)
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        unordered_map<int,int> m;       // map the coordinate difference to element value
        int r = matrix.size(), c = matrix[0].size();
        
        for ( int i = 0; i < r; i++ )
            for ( int j = 0; j < c; j++ )
            {
                if ( m.find(i-j) != m.end() )
                {
                    if ( m[i-j] != matrix[i][j] )
                        return false;
                }
                else
                {
                    m[i-j] = matrix[i][j];
                }
            }
        return true;
    }
};