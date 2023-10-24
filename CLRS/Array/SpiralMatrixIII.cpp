/*
You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.

You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.

Return an array of coordinates representing the positions of the grid in the order you visited them.

 

Example 1:


Input: rows = 1, cols = 4, rStart = 0, cStart = 0
Output: [[0,0],[0,1],[0,2],[0,3]]
Example 2:


Input: rows = 5, cols = 6, rStart = 1, cStart = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
 

Constraints:

1 <= rows, cols <= 100
0 <= rStart < rows
0 <= cStart < cols
*/

// consider four directions: the len for each cycle is 1,1,2,2, 3,3, 4,4, etc ...
// which means the start len of each cycle is 1, 3, 5, and the east and south direction has the same len as the start len, while the west and north has one more length than the 
// start length. 
// Following this pattern, if the current position is valid, then this is the next position visited 
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> res;
        int total = rows * cols, r = rStart, c = cStart;
        vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        res.push_back({r,c});
        if ( total == 1 )
            return res;
        for ( int start = 1; start < 2 * (rows + cols); start += 2 )
        {
            for ( int d = 0; d < 4; d++ )
            {
                int steps = start + d/2;
                for ( int i = 0; i < steps; i++ )
                {
                    r = r + dirs[d][0];
                    c = c + dirs[d][1];
                    if ( r >= 0 && r < rows && c >= 0 && c < cols )
                    {
                        res.push_back({r,c});
                        if ( res.size() == total )
                            return res;
                    }
                }
            }
        }

        return res;
    }
};