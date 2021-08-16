/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

 

Example 1:


Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:


Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Example 3:

Input: matrix = [[1]]
Output: 1
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1
*/

#if 0
// we define a helper function dfs to calculate the max increasing len starting from a given position
class Solution {
    int m;
    int n;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int ret = 0;
        m = matrix.size();
        n = matrix[0].size();
        vector<vector<int>> memo(m,vector<int>(n,-1));
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
                ret = max(ret,dfs(matrix,i,j,memo));
        return ret;
    }
    
    int dfs(vector<vector<int>> &matrix, int i, int j, vector<vector<int>> &memo)
    {
        vector<pair<int,int>> dir{{1,0},{-1,0},{0,1},{0,-1}};
        int ret = 1;
        if ( memo[i][j] != -1)
            return memo[i][j];
        for ( int d = 0; d < 4; d++ )
        {
            int x = i + dir[d].first;
            int y = j + dir[d].second;
            if ( x < 0 || x >= m || y < 0 || y >= n || matrix[i][j] >= matrix[x][y] ) 
                continue;
            ret = max(ret, 1+dfs(matrix,x,y,memo));
        }
        
        return memo[i][j] = ret;
    }
};
#endif 

#include "../Common/common_api.h"


// we can use gready-like BFS to peel off the layers starting from the end of the path which includes the positions being the local max. 
// We first need to preprocess the matrix to obtain the "outdegree" of each position, i.e., the neighbors that are less then itself. 
// The tricky part is to determine which positions are to be added to the next layer ? 
// Since we are trying to find maximal len of the increasing path, we should be conservative to add poistions to the next level, meaning we only add
// the positions currently having zero outdegrees. The heuristic is that we might add the remaining neighbors first to get a possibly longer path
class Solution {
    static vector<pair<int,int>> dir;
    int m;
    int n;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        if ( m == 0 )
            return 0;
        vector<pair<int,int>> level;
        vector<vector<int>> outdegrees(m,vector<int>(n,0));
        int len = 0;
        
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j ++)
            {
                int outdegree = 0;
                for ( int d = 0; d < 4; d++ )
                {
                    int x = i + dir[d].first;
                    int y = j + dir[d].second;
                    if ( x < 0 || x >= m || y < 0 || y >= n )
                        continue;
                    if ( matrix[x][y] > matrix[i][j] )
                        outdegree++;
                }
                outdegrees[i][j] = outdegree;
                if ( outdegree == 0 )
                    level.push_back({i,j});
            }
        
        while ( !level.empty() )
        {
            printVec(level);
            len++;
            vector<pair<int,int>> tmp;
            for ( auto pos : level )
                pushNeighbor(pos.first,pos.second,tmp,matrix,outdegrees);
            level = tmp;
        }
        
        return len;
    }
    
    void pushNeighbor(int i, int j, vector<pair<int,int>> &level, vector<vector<int>> const &matrix, vector<vector<int>> &outdegrees) 
    {
        for ( int d = 0; d < 4; d++ )
        {
            int x = i + dir[d].first;
            int y = j + dir[d].second;
            if ( x < 0 || x >= m || y < 0 || y >= n )
                continue;
            if ( matrix[x][y] < matrix[i][j] && --outdegrees[x][y] == 0 )
            {
                level.push_back({x,y});
            }
        }
    }
    
    void printVec(vector<pair<int,int>> const &v )
    {
        cout << "[";
        for ( int i = 0; i < v.size()-1; i++)
        {
            cout << "{" << v[i].first << "," << v[i].second <<"}, ";
        }
        cout << "{" << v.back().first << "," << v.back().second <<"}]" << endl;
    }
};

vector<pair<int,int>> Solution::dir = {{-1,0},{1,0},{0,1},{0,-1}};

int main()
{
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    Solution s;
    s.longestIncreasingPath(matrix);
}