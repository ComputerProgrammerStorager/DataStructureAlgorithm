/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.
*/

#include "../Common/common_api.h"

class Solution_OutofPlace {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if ( obstacleGrid[m-1][n-1] == 1 || obstacleGrid[0][0] == 1 )
            return 0;
        int dp[m][n];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for ( int r = 0; r < m; r++ )
            for ( int c = 0; c < n; c++ )
            {
                if ( obstacleGrid[r][c] == 0 )
                {
                    if ( r-1 >= 0 && obstacleGrid[r-1][c] == 0 )
                    {
                        dp[r][c] += dp[r-1][c];
                    }
                    if ( c-1 >= 0 && obstacleGrid[r][c-1] == 0 )
                    {
                        dp[r][c] += dp[r][c-1];
                    }
                }
            }
        return dp[m-1][n-1];
    }
};

class SolutionInPlace{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if ( obstacleGrid[m-1][n-1] == 1 || obstacleGrid[0][0] == 1 )
            return 0;
        obstacleGrid[0][0] = 1;
        for ( int r = 0; r < m; r++ )
            for ( int c = 0; c < n; c++ )
            {
                if ( obstacleGrid[r][c] == 0 )
                {
                    if ( r-1 >= 0 )
                    {
                        obstacleGrid[r][c] += obstacleGrid[r-1][c];
                    }
                    if ( c-1 >= 0 )
                    {
                        obstacleGrid[r][c] += obstacleGrid[r][c-1];
                    }
                }
                else if ( r !=0 || c != 0 ) 
                {
                    obstacleGrid[r][c] = 0;
                }
            }
        return obstacleGrid[m-1][n-1];
    }
};

int main()
{
    vector<vector<int>> grid = {{0,0,0},{0,1,0},{0,0,0}};
    int res;
    Solution_OutofPlace s_outofplace;
    res = s_outofplace.uniquePathsWithObstacles(grid);
    cout << "using out of place method the answer is " << res << endl;
    SolutionInPlace s_inplace;
    res = s_inplace.uniquePathsWithObstacles(grid);
    cout << "using in-place method the answer is " << res << endl;

}