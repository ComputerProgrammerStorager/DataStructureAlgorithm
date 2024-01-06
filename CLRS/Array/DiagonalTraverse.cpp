/*
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

 

Example 1:


Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]
Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
-105 <= mat[i][j] <= 105
*/


class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        unordered_map<int,vector<int>> m;
        vector<int> res;
        for ( int row = mat.size() - 1; row >= 0; row-- ) 
            for ( int col = 0; col < mat[row].size(); col++ ) {
                int id = row + col;
                if ( id & 1 ) {
                    m[id].insert(m[id].begin(),mat[row][col]);
                } else {
                    m[id].push_back(mat[row][col]);
                }
            }

        for ( int id = 0; m.count(id); id++ ) {
            res.insert(res.end(),m[id].begin(),m[id].end());
        }
        return res;
    }
};

// use bfs 
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> res;
        queue<pair<int,int>> q;
        int m = mat.size(), n = mat[0].size();
        q.push({0,0});
        while(!q.empty()) {
            vector<int> tmp;
            for (int i = q.size(); i > 0; i-- ) {
                auto [row, col] = q.front();
                q.pop();
                int id = row+col;
                if ( col == 0 && row+1 < m ) 
                    q.push({row+1,col});
                if ( col+1 < mat[row].size() )
                    q.push({row,col+1});
                if ( id & 1 ) {
                    tmp.insert(tmp.begin(),mat[row][col]);
                } else {
                    tmp.push_back(mat[row][col]);
                }
            }
            res.insert(res.end(),tmp.begin(),tmp.end());
        }

        return res;
    }
};