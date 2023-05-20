/*
Given a string s, return the length of the longest repeating substrings. If no repeating substring exists, return 0.

 

Example 1:

Input: s = "abcd"
Output: 0
Explanation: There is no repeating substring.
Example 2:

Input: s = "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.
Example 3:

Input: s = "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.
 

Constraints:

1 <= s.length <= 2000
s consists of lowercase English letters.
*/

// Essentially, it asks for the longest repeating substring between s[0...i] and s[0...j], where j > i, as they have to differ 
// dp[i][j] represent that and thus the recurrence relationship is:
// dp[i][j] = dp[i-1][j-1] + 1 if i > 0, else 1, if s[i] == s[j]. otherwise, 0, since s[i] != s[j], meaning they could not be repeating 
class Solution {
public:
    int longestRepeatingSubstring(string s) {
        // dp[i][j] = dp[i-1][j-1] + 1 subject to the condition that j should be larger than i, as we are expanding the substring for the second one 
        int n = s.size();
        if ( n == 0 )
            return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        int maxlen = 0;
        for ( int i = 0; i < n; i++ )
            for ( int j = i+1; j < n; j++ )
            {
                if ( s[i] == s[j] )
                {
                    dp[i][j] = i > 0 ? dp[i-1][j-1] + 1 : 1; 
                    maxlen = max(maxlen,dp[i][j]);
                }
            }

        return maxlen;
    }
};
