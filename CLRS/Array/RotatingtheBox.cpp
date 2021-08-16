/*
You are given an m x n matrix of characters box representing a side-view of a box. Each cell of the box is one of the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in box rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

 

Example 1:



Input: box = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]
Example 2:



Input: box = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]
Example 3:



Input: box = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]
 

Constraints:

m == box.length
n == box[i].length
1 <= m, n <= 500
box[i][j] is either '#', '*', or '.'.
*/

// The key observation is to note that matrix M(r,c) becomes M(c,r) and specially row i becomes col
// (m-1-i). 
// Approach we fill the rotated matrix row by row. And for each row, we calculate the number of stones above each
// possible obstacle or bottom. Then fill the amount of stones above the obstacle or bottom
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int r = box.size();
        int c = box[0].size();
        vector<vector<char>> res(c,vector<char>(r,'.'));
        // Note: the row i would become col(m - i - 1) (0->m-1);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
            {
                int stones = 0;
                int k = j, col = r - 1 - i;
                while (k < c && box[i][k] != '*')
                {
                    if ( box[i][k] == '#')
                        stones++;
                    k++;
                }
                
                if ( k < c )
                    res[k][col] = '*';
                for (int s = 0; s < stones; s++)
                    res[k-1-s][col] = '#';
                j = k;
            }
        
        return res;
    }
};