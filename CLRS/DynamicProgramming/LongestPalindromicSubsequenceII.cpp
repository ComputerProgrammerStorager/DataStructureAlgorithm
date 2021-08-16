/*
A subsequence of a string s is considered a good palindromic subsequence if:

It is a subsequence of s.
It is a palindrome (has the same value if reversed).
It has an even length.
No two consecutive characters are equal, except the two middle ones.
For example, if s = "abcabcabb", then "abba" is considered a good palindromic subsequence, while "bcb" (not even length) and "bbbb" (has equal consecutive characters) are not.

Given a string s, return the length of the longest good palindromic subsequence in s.

Example 1:

Input: s = "bbabab"
Output: 4
Explanation: The longest good palindromic subsequence of s is "baab".
Example 2:

Input: s = "dcbccacdb"
Output: 4
Explanation: The longest good palindromic subsequence of s is "dccd".
 

Constraints:

1 <= s.length <= 250
s consists of lowercase English letters.
*/

#include "../Common/common_api.h"

/*
 dp[i][j][0...26] represents the max len of substring s[i...j] with end char of [0...26], i.e., a...z.
 then the transfer equation is: 
  if s[i] == s[j], then 
    dp[i][j][s[i]-'a'] = max(dp[i][j][s[i]-'a'],dp[i+1][j-1][k-'a']+2) for all k != s[i] because the updated string have two consecutive chars the same, so we use other values to replace this. 
    dp[i][j][k-'a'] = dp[i+1][j-1][k-'a'] for all k != s[i]..because the new pair wounldn't increase the length 
  else 
    dp[i][j][s[i]-'a'] = dp[i][j-1][s[i]-'a'];   we know s[j] != s[i], so the longest ending with s[i] will be the same as the substring without s[j]
    dp[i][j][s[j]-'a'] = dp[i+1][j][s[j]-'a];    we know s[i] != s[j], so the longest ending with s[j] will be the same as the substring without s[i]
    dp[i][j][k-'a'] = dp[i+1][j-1][k-'a'];       we know the longest ending neither s[i] or s[j] remain the same as the substring without either s[i] or s[j]. 

Base cases: 
    single char substrings have 0 
    two char substrings are equal to 2 
    and we iterate using len-dominating method
 */

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size(); 
        int res = 0;
        if ( n == 0 )
            return 0;
        vector<vector<vector<int>>> dp(n,vector(n,vector(26,0)));
        for ( int i = 0; i < n - 1; i++ )
            if ( s[i] == s[i+1] )
                dp[i][i+1][s[i]-'a'] = 2;
        
        for ( int len = 3; len <= n; len++ )
            for ( int i = 0; i <= n - len; i++ )
            {
                int j = i + len - 1;
                if ( s[i] == s[j] )
                {  
                    for ( char ch = 'a'; ch <= 'z'; ch++ )
                    {
                        if ( ch != s[i] )
                            dp[i][j][s[i]-'a'] = max(dp[i][j][s[i]-'a'],dp[i+1][j-1][ch-'a']+2);
                    }
                    for ( char ch = 'a'; ch <= 'z'; ch++ )
                    {
                        if ( ch != s[i] )
                            dp[i][j][ch-'a'] = dp[i+1][j-1][ch-'a'];
                    }
                }
                else 
                {
                    char left = s[i], right = s[j];
                    dp[i][j][left-'a'] = dp[i][j-1][left-'a'];
                    dp[i][j][right-'a'] = dp[i+1][j][right-'a'];
                    for ( int ch = 'a'; ch <= 'z'; ch++ )
                    {
                        if ( ch != left && ch != right )
                        {
                            dp[i][j][ch-'a'] = dp[i+1][j-1][ch-'a'];
                        }
                    }
                }
            }
        for ( char ch = 'a'; ch <= 'z'; ch++ )
            if ( dp[0][n-1][ch-'a'] > res )
                res = dp[0][n-1][ch-'a'];
        return res;
    }
};

int main()
{
    string s("boob"); 
    Solution sol;
    sol.longestPalindromeSubseq(s);
}