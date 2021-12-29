/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
 

Constraints:

1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.

*/

// dp[i][j]: represents the LCS between s[0...i-1] and t[0...j-1]
// dp[i][j] = dp[i-1][j-1] if s[i] == t[j]
// dp[i][j] = max(dp[i][j-1],dp[i-1][j])
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        
        for (int r = 1; r <= m; r++ )
        {
            for ( int c = 1; c <= n; c++ )
            {
                if ( text1[r-1] == text2[c-1] )
                {
                    dp[r][c] = dp[r-1][c-1] + 1;
                }
                else 
                {
                    dp[r][c] = max(dp[r][c-1],dp[r-1][c]);
                }
            }
        }
        
        return dp[m][n];
    }
};