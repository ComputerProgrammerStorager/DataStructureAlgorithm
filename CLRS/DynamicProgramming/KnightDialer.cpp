/*
The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagaram:

A chess knight can move as indicated in the chess diagram below:


We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).


Given an integer n, return how many distinct phone numbers of length n we can dial.

You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.

As the answer may be very large, return the answer modulo 109 + 7.

 

Example 1:

Input: n = 1
Output: 10
Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
Example 2:

Input: n = 2
Output: 20
Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
Example 3:

Input: n = 3131
Output: 136006598
Explanation: Please take care of the mod.
 

Constraints:

1 <= n <= 5000
*/

// top down dynamic programming 
// dp[i][j]: represents the ways to with i remaining moves starting from square j
class Solution {
public:
    int knightDialer(int n) {
        vector<vector<int>> neighbors = {
            {4,6},
            {6,8},
            {7,9},
            {4,8},
            {0,3,9},
            {},
            {0,1,7},
            {2,6},
            {1,3},
            {2,4},
        };
        vector<vector<int>> dp(n+1,vector<int>(10,-1));
        int ans = 0;
        for ( int i = 0; i < 10; i++ )
        {
            ans += help(n-1,i,dp,neighbors);
            ans %= int(1e9+7);
        }
        return ans;
    }

    int help(int remain, int square, vector<vector<int>>& dp, const vector<vector<int>>& neighbors)
    {
        if ( remain == 0 )
            return 1;
        if ( dp[remain][square] != -1 )
            return dp[remain][square];
        int ans = 0;
        for ( int next : neighbors[square] )
        {
            ans = (ans + help(remain-1,next,dp,neighbors)) % int(1e9+7);
        }
        dp[remain][square] = ans;
        return ans;
    }
};

// bottom up approach 
// dp[step][square]: represents the ways of using *step steps from cell square
class Solution {
public:
    int knightDialer(int n) {
        vector<vector<int>> neighbors = {
            {4,6},
            {6,8},
            {7,9},
            {4,8},
            {0,3,9},
            {},
            {0,1,7},
            {2,6},
            {1,3},
            {2,4},
        };
        int result = 0;
        vector<vector<int>> dp(n,vector<int>(10,0));
        for ( int i = 0; i < 10; i++ )
            dp[0][i] = 1;
        for ( int i = 1; i < n; i++ )
        {
            for ( int j = 0; j < 10; j++ )
            {
                int ans = 0;
                for ( int n : neighbors[j] ) {
                    ans += dp[i-1][n];
                    ans %= (int)(1e9+7);
                }      
                dp[i][j] = ans; 
            }
        }

        for ( int i = 0; i < 10; i++ )
        {
            result += dp[n-1][i];
            result %= int(1e9+7);
        }

        return result;
    }
};