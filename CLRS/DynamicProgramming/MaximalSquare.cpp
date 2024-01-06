/*
Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

 

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4
Example 2:


Input: matrix = [["0","1"],["1","0"]]
Output: 1
Example 3:

Input: matrix = [["0"]]
Output: 0
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.
*/

// Brute force solution: 
// check the squares defined by the upper-left position. We select a position and expand the length by one at a time. 
// It can formulate a new larger square only if the expanded row and column are all ones. 
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), maxsqlen = 0;
        
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                if ( matrix[i][j] == '0' )
                    continue;
                int sqlen = 1;
                bool stop = false;
                while( i+sqlen < m && j+sqlen < n && !stop )
                {
                    for ( int k = i; k <= i+sqlen; k++ )
                    {
                        if ( matrix[k][j+sqlen] == '0' )
                        {
                            stop = true;
                            break;
                        }
                    }
                    
                    for ( int k = j; k <= j+sqlen; k++ )
                    {
                        if ( matrix[i+sqlen][k] == '0' )
                        {
                            stop = true;
                            break;
                        }
                    }
                    
                    if ( !stop )
                        sqlen++;
                }
                maxsqlen = max(maxsqlen,sqlen);
            }
        
        return maxsqlen * maxsqlen;
    }
};

// we can use dynamical programming, dp[i][j] represents the lenght of square whose bottom right is matrix[i][j]
// then it can it's value depends on the values of the three neighboring cells. Imaging their intersection... 
// Recurrence is: dp[i][j] = min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1]) + 1 if matrix[i][j] == '1'.
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), maxsqlen = 0;
        vector<vector<int>> dp(m,vector<int>(n,0));
        for ( int r = 0; r < m; r++ )
        {
            dp[r][0] = matrix[r][0] - '0';
            if ( dp[r][0] )
                maxsqlen = 1;
        }
            
        for ( int c = 0; c < n; c++ )
        {
            dp[0][c] = matrix[0][c] - '0';
            if ( dp[0][c] )
                maxsqlen = 1;
        }
        
        // dp[i][j] = min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1]) + 1;
        
        for ( int r = 1; r < m; r++ )
            for ( int c = 1; c < n; c++ )
            {
                if ( matrix[r][c] == '1' )
                {
                    dp[r][c] = min(dp[r-1][c-1],min(dp[r-1][c],dp[r][c-1])) + 1;
                    maxsqlen = max(maxsqlen,dp[r][c]);
                }

            }
        
        return maxsqlen*maxsqlen;
    }
};

// use additional m+n space to demonstrate using concise code  
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), maxsqlen = 0;
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));     // dp[i][j] repesent length of square whose bottom-right is matrix[i-1][j-1]
        for ( int r = 1; r <= m; r++ )
            for ( int c = 1; c <= n; c++ )
            {
                if ( matrix[r-1][c-1] == '1' )
                {
                    dp[r][c] = min(dp[r-1][c-1],min(dp[r-1][c],dp[r][c-1])) + 1;
                    maxsqlen = max(maxsqlen,dp[r][c]);
                }
            }
        
        return maxsqlen * maxsqlen;
    }
};

// Use 1D array 
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), maxlen = 0, prev = 0;
        vector<int> dp(n+1,0);
        for ( int i = 1; i <= m; i++ ) {
            for (int j = 1; j <= n; j++ ) {
                int tmp = dp[j];
                if ( matrix[i-1][j-1] == '1' ) {
                    dp[j] = min(min(dp[j],dp[j-1]),prev) + 1;
                    maxlen = max(maxlen,dp[j]);
                } else {
                    dp[j] = 0;
                }
                prev = tmp;
            }
        }
        return maxlen * maxlen;
    }
};