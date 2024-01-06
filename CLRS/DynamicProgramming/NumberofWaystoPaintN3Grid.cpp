/*
You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).

Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.

 

Example 1:


Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown.
Example 2:

Input: n = 5000
Output: 30228214
 

Constraints:

n == grid.length
1 <= n <= 5000

*/

// Each row has only two states, which has 2 colors and 3 colors respectively. 
// For each state, it can be reached from previous possible two states.. 
// (Color2_prev, color3_prev) ---> color2_cur
// (color2_prev, color3_prev) ---> color3_cur
// ABA ---> (CAC, BAB, BCB) color2 --> color2 
// ABA ---> ( BAC, CAB) color2 ---> color3
// ABC ---> (CAB, BCA)  color3 ---> color3 
// ABC ---> (BAB, BCB)  color3 ---> color2 
// color2_cur = 3 * color2_prev + 2 * color3_prev
// color3_cur = 2 * color3_prev + 2 * color2_prev 

class Solution {
public:
    int numOfWays(int n) {
        long color2 = 6, color3 = 6;
        int MOD = 1e9+7;
        for ( int i = 1; i < n; i++ ) {
            long tmp2 = color2, tmp3 = color3;
            color2 = ((2*tmp3) % MOD  + (3*tmp2)%MOD)  % MOD;
            color3 = ((2*tmp2)%MOD + (2*tmp3)%MOD) % MOD;
        }

        return (color2+color3) % MOD;
    }
};