/*
Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
Example 3:

Input: s = "a"
Output: "a"
Example 4:

Input: s = "ac"
Output: "a"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.

*/

// s[i][j] depends on s[i+1][j-1], so we can obtain the recurrence relation, using dp[i][j] to represent if s[i..j] is a palindrome or not
//            | true     j - i < 1, i.e., single char substring
// dp[i][j] ==| true     j - i < 2 && s[i] == s[j], i.e., two same char substring 
//            | true     s[i] == s[j] && dp[i+1][j-1]

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), maxlen = 1, start;
        vector<vector<int>> dp(n,vector<int>(n,0));
        for ( int i = 0; i < n; i++ )
        {
            dp[i][i] = 1;
            for ( int j = 0; j < i; j++ )
            {
                dp[j][i] = s[j] == s[i] && (i-j < 2 || dp[j+1][i-1] );
                if ( dp[j][i] && maxlen < i-j+1 )
                {
                    maxlen = i-j+1;
                    start = j;
                }
            }
        }
        
        return s.substr(start,maxlen);
    }
};