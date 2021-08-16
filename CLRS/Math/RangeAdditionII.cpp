/*
You are given an m x n matrix M initialized with all 0's and an array of operations ops, where ops[i] = [ai, bi] means M[x][y] should be incremented by one for all 0 <= x < ai and 0 <= y < bi.

Count and return the number of maximum integers in the matrix after performing all the operations.

 

Example 1:


Input: m = 3, n = 3, ops = [[2,2],[3,3]]
Output: 4
Explanation: The maximum integer in M is 2, and there are four of it in M. So return 4.
Example 2:

Input: m = 3, n = 3, ops = [[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3]]
Output: 4
Example 3:

Input: m = 3, n = 3, ops = []
Output: 9
 

Constraints:

1 <= m, n <= 4 * 104
1 <= ops.length <= 104
ops[i].length == 2
1 <= ai <= m
1 <= bi <= n

*/

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        vector<vector<int>> data(m,vector<int>(n,0));
        for ( auto &v : ops )
        {
            int x = v[0];
            int y = v[1];
            for ( int i = 0; i < x; i++ )
                for ( int j = 0; j < y; j++ )
                {
                    data[i][j]++;
                }
        }
        
        
        int cnt = 0;
        for ( int i = 0; i < m; i++)
            for ( int j = 0; j < n; j++ )
            if ( data[i][j] == data[0][0] )
                cnt++;
    
        return cnt;
    }
};


// the number of maximum number equals to the most overlapped area
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int min_x = m, min_y = n;
        for ( auto &op : ops )
        {
            min_x = min(min_x,op[0]);
            min_y = min(min_y,op[1]);
        }
        
        return min_x * min_y;
    }
};