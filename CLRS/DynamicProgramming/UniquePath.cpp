/* 
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/

#include "../Common/common_api.h"

class SolutionDP {
public:
    int uniquePaths(int m, int n) {
        int dp[m][n];
        if ( m == 0 || n == 0 )
        {
            return 0;
        }
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for ( int i = 0; i < m; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                if ( i - 1 >= 0 )
                    dp[i][j] += dp[i-1][j];
                if ( j - 1 >= 0 )
                    dp[i][j] += dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
};

class SolutionFrugal {
public:
    int uniquePaths(int m, int n) {
        int dp[n];
        if ( m < 1 || n < 1 )
            return 0;
        memset(dp,0,sizeof(dp));
        dp[0] = 1;
        for ( int i = 0; i < m; i++ )
            for ( int j = 1; j < n; j++ )
                dp[j] += dp[j-1];
        return dp[n-1];
    }
};

class SolutionRecur {
public:
    int uniquePaths(int m, int n) {
        if ( m == 1 || n == 1 )
            return 1;
        return uniquePaths(m-1,n) + uniquePaths(m,n-1);
    }
};

class SolutionCombinatorial {
public:
    int uniquePaths(int m, int n) {
        double num = 1, denom = 1;
        int small = m < n ? m : n;
        for ( int i = 1; i <= small - 1; i++ )
        {
            denom *= i;
            num *= m + n - 1 - i;
        }
        
        return (int) (num / denom );
    }
};


int main()
{
    int m = 7, n = 3;
    long res;
    cout << "The unique paths of " << m << "x" << n << "grid is" << endl;
    SolutionDP s_dp;
    res = s_dp.uniquePaths(m,n);
    cout << "using dp method: " << res << endl;
    SolutionRecur s_recur;
    s_recur.uniquePaths(m,n);
    cout << "using recursion method: " << res << endl;
    SolutionFrugal s_frugal;
    res = s_frugal.uniquePaths(m,n);
    cout << "using frugal dp method: " << res << endl;
    SolutionCombinatorial s_comb;
    res = s_comb.uniquePaths(m,n);
    cout << "using combinatorial math method: " << res << endl;

}