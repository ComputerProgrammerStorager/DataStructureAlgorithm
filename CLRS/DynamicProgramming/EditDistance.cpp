/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size(); 
        vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
        for ( int i = 0; i <= n1; i++ )
            dp[i][0] = i;
        for ( int i = 0; i <= n2; i++ )
            dp[0][i] = i;
        if ( n1 == 0 )
            return n2;
        if ( n2 == 0)
            return n1;
        // dp[i][j] = dp[i-1][j-1] is word1[i] == word2[j]
        // otherwise: dp[i-1][j] word1[i] is added relative to word2
        // dp[i][j-1]: word2[j] is added relative to word1
        // dp[i-1][j-1]: word1[i] <---> word2[j] is replaced 
        for ( int i = 1; i <= n1; i++ )
            for ( int j = 1; j <= n2; j++ )
            {
                if ( word1[i-1] == word2[j-1] )
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1])) + 1;
                }
            }

        return dp[n1][n2];
    }
};


class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        if ( n1 == 0 )
            return n2;
        if ( n2 == 0 )
            return n1;
        vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
        for ( int i = 0; i <= n1; i++ )
            dp[i][0] = i;
        for ( int i = 0; i <= n2; i++ )
            dp[0][i] = i;
        for ( int i = 1; i <= n1; i++ )
            for ( int j = 1; j <= n2; j++ )
            {
                if ( word1[i-1] == word2[j-1] )
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
                }
            }

        return dp[n1][n2];
    }
};