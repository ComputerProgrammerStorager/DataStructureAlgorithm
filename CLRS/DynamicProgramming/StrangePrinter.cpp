/*
There is a strange printer with the following two special properties:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
Given a string s, return the minimum number of turns the printer needed to print it.

 

Example 1:

Input: s = "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:

Input: s = "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
 

Constraints:

1 <= s.length <= 100
s consists of lowercase English letters.

*/

//idea:
// first identify this as an interval dp problem 
// then idenfity the recurrence equation:
// dp[i][j] = dp[i][k-1] + dp[k+1][j] for all s[k] == s[i] and i <= k <= j
// this means when we start to print s[i], which k position should I stop
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n,1));
        #if 0
        for (int i = 0; i < n; i++ )
            dp[i][i] = 1;
        #endif
        
        for ( int len = 2; len <= n; len++ )
            for ( int i = 0; i <= n - len; i++)
            {
                int j = i+len-1;
                dp[i][j] = 1 + dp[i+1][j];
                
                for ( int k = i+1; k <= j; k++)
                    if (s[k] == s[i] )
                      dp[i][j] = min(dp[i][j],dp[i][k-1]+((k+1) > j ? 0 :dp[k+1][j]));
            }
                      
        return dp[0][n-1];
    }
};