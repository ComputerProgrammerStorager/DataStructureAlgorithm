/*
Given strings s1 and s2, return the minimum contiguous substring part of s1, so that s2 is a subsequence of the part.

If there is no such window in s1 that covers all characters in s2, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:

Input: s1 = "abcdebdde", s2 = "bde"
Output: "bcde"
Explanation: 
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of s2 in the window must occur in order.
Example 2:

Input: s1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl", s2 = "u"
Output: ""
 

Constraints:

1 <= s1.length <= 2 * 104
1 <= s2.length <= 100
s1 and s2 consist of lowercase English letters.
*/

// dp[i][j]: denotes the start position of s1 susbstring ending at position i such that the substring s1[0:i] contains subsequece of s2[0:j].
// therefore we reache a qualified answer whenever j equals to n-1
// the recurrence is as follows:
//              dp[i-1][j-1] if s1[i] == s2[j]
// dp[i][j] =  
//              dp[i-1][j] if s1[i] != s2[j]

class Solution {
public:
    string minWindow(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m,vector<int>(n,-1));
        int start_idx = -1, min_len = INT_MAX;
        // dp[i][j]: means the start position of substring of [0,i] that contains the subsequence of [0,j] of T
        // dp[i][j] == dp[i-1][j-1] if s1[i] == s2[j]
        // dp[i][j] == dp[i-1][j] if s1[i] != s2[j]
        // set up first column 
        int last_idx = -1;
        for ( int i = 0; i < m; i++ )
        {
            if (s1[i] == s2[0])
                last_idx = i;
            dp[i][0] = last_idx;
        }
        
        if ( n == 1 )
        {
            start_idx = last_idx;
            min_len = 1;
        }
        
        for ( int i = 1; i < m; i++ )
            for ( int j = 1; j < n; j++ )
            {
                if ( i >= j)
                {
                    if ( s1[i] == s2[j] )
                        dp[i][j] = dp[i-1][j-1];
                    else
                        dp[i][j] = dp[i-1][j];
                    if ( j == n-1 && dp[i][j] != -1 )
                    {
                        int cur_len = i - dp[i][j] + 1;
                        if ( cur_len < min_len )
                        {
                            start_idx = dp[i][j];
                            min_len = cur_len;
                        }
                    }
                }
            }
        
        return start_idx == -1 ? "" : s1.substr(start_idx,min_len);
    }
};