/*
Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
 

Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".
 

Constraints:

1 <= s.length <= 1000
s consists only of lowercase English letters.
*/

#include "../Common/common_api.h"

// dp[i][j] represent the longest palindromic subsequence of substring s[i...j]
// dp[i][j] = dp[i+1][j-1] + 2; if s[i] == s[j]
// dp[i][j] = max(dp[i+1][j],dp[i][j-1]); if s[i] != s[j]
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        if ( n == 0 )
            return 0;
        vector<vector<int>> dp(n,vector(n,0));
        for ( int i = 0; i < n; i++ )
            dp[i][i] = 1;

        for ( int len = 2; len <= n; len++ )
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i + len - 1;
                if ( s[i] == s[j] )
                    dp[i][j] = dp[i+1][j-1] + 2;
                else 
                    dp[i][j] = max(dp[i][j-1],dp[i+1][j]);
            }
        
        return dp[0][n-1];
    }
};

// Recursion 
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size(); 
        if ( n == 0 )
            return 0;
        vector<vector<int>> memo(n,vector(n,-1));
        return helper(s,0,n-1,memo);
    }
    int helper(string const &s, int i, int j, vector<vector<int>> &memo)
    {
        if ( memo[i][j] != -1 )
            return memo[i][j];
        if ( i == j )
        {
            return 1;
        }
        else if ( i > j )
        {
            return 0;
        }
        else if ( s[i] == s[j] )
        {
            memo[i][j] = helper(s,i+1,j-1,memo) + 2;
        }
        else 
        {
            memo[i][j] = max(helper(s,i+1,j,memo), helper(s,i,j-1,memo));
        }
        
        return memo[i][j];
    }
};

int main()
{
    string str = "abcdef";
    Solution sol;
    sol.longestPalindromeSubseq(str);
}