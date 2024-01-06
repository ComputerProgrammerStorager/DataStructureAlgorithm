/*
Given an m x n binary matrix mat, return the number of submatrices that have all ones.

 

Example 1:


Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
Output: 13
Explanation: 
There are 6 rectangles of side 1x1.
There are 2 rectangles of side 1x2.
There are 3 rectangles of side 2x1.
There is 1 rectangle of side 2x2. 
There is 1 rectangle of side 3x1.
Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
Example 2:


Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
Output: 24
Explanation: 
There are 8 rectangles of side 1x1.
There are 5 rectangles of side 1x2.
There are 2 rectangles of side 1x3. 
There are 4 rectangles of side 2x1.
There are 2 rectangles of side 2x2. 
There are 2 rectangles of side 3x1. 
There is 1 rectangle of side 3x2. 
Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.
 

Constraints:

1 <= m, n <= 150
mat[i][j] is either 0 or 1.
*/

// Dynamic programing approach 
// O(n*m^2), O(m*n)
// Idea is: every one cell can be the up left corner of a rectangle. So we choose one as the up-left corner, then we expand right and downward 
// To expand right, we need to know how many consecutive ones are there for each cell including itself. This is the number of rectangles there are if only the line is included 
// To expand downward, each row below would add the min of ones of every row includes, by expanding columns 
// for example, we have these ones : 
// Row1: 1 1 1 1 
// Row2: 1 1 
// Row3: 1 
// Row4: 1 1 1 1 
// Assume we are considering [0][0] as the up-left corner, the: 
// Row1: 4 rectangles, side length is 1 
// Row2: 2 rectangels, 2*1, 2*2 
// Row3: 1 rectangle, 3*1 
// Row4: 1 rectangle, 4*1 
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size(), res = 0;
        vector<vector<int>> rightones(m,vector<int>(n,0));
        for ( int i = 0; i < m; i++ ) {
            int ones = 0;
            for (int j = n-1; j >= 0; j-- ) {
                if ( mat[i][j] == 1 ) {
                    ones++;
                } else {
                    ones = 0;
                }
                rightones[i][j] = ones;
            }
        }

        for ( int i = 0; i < m; i++ ) 
            for ( int j = 0; j < n; j++ ) {
                int rect = 0;
                for ( int k = i; k < m; k++ ) {
                    rect = min(rect, rightones[k][j]);
                    res += rect;
                }
            }

        return res;
    }
};


// Perceive each histogram as the right bar.  
// Then if it is taller than its left neighbor, then the rectanges it can be part of will be that of the previous one, 
// plus its histogram (i.e., each of the cells can be a standalone submatrice). 
// If it is shorter than its left neighbor, then the rectangles it can be part of should be deduced by the taller part formulated by 
// its left neighbor. And this process needs to repeated to simulate expanding leftward. 

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size(), res = 0;
        vector<int> hist(n+1,0);
        for ( int i = 0; i < m; i++ ) {
            stack<int> stk;
            stk.push(0);
            int cnt = 0; 
            for (int j = 1; j <= n; j++ ) 
                hist[j] = mat[i][j-1] ? hist[j] + 1 : 0;

            for ( int j = 1; j <= n; j++ ) {
                while( !stk.empty() && hist[stk.top()] > hist[j] ) {
                    int tp1 = stk.top();
                    stk.pop();
                    cnt -= (tp1-stk.top()) * (hist[tp1]-hist[j]);
                }
                cnt += hist[j];
                res += cnt;
                stk.push(j);
            }
        }

        return res;
    }
};