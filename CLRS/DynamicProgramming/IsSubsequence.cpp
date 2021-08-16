/*
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true
Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false
 

Constraints:

0 <= s.length <= 100
0 <= t.length <= 104
s and t consist only of lowercase English letters.
 

Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109, and you want to check one by one to see if t has its subsequence. In this scenario, how would you change your code?

*/

// straightforward approach using two pointers 
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_len = s.size(), t_len = t.size();
        int i = 0, j = 0;
        while ( i < s_len && j < t_len )
        {
            if ( s[i] == t[j] )
                i++;
            j++;
        }
        
        return i == s_len;
    }
};

// move involved, but less efficient using dynamic programming 
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_len = s.size(), t_len = t.size();
        vector<vector<bool>> dp(t_len+1,vector<bool>(s_len+1,false));      // dp[i][j]: denotes if s[0,j) is subsequence of t[0,i)
        if ( s_len == 0 )
            return true;
        if ( t_len == 0 )
            return false;
        s = "*" + s;
        t = "*" + t;
        for ( int col = 1; col <= s_len; col++ )
            dp[0][col] = false;
        for ( int row = 0; row <= t_len; row++ )
            dp[row][0] = true;
        for ( int i = 1; i <= t_len; i++ )
            for ( int j = 1; j <= s_len; j++ )
                dp[i][j] = s[j] == t[i] ? dp[i-1][j-1] : dp[i-1][j];
        
        return dp[t_len][s_len];
    }
};


// we can process he target string t first to get the next array which faciliates the advancing when a match is found 
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_len = s.size(), t_len = t.size();
        vector<vector<int>> next(t_len+1,vector<int>(26,-1));   // next[i][ch]: denote the first position of char i to the right of position i 
        t = "*" + t;
        for ( int i = t_len; i >= 1; i--)
        {
            for ( int ch = 0; ch < 26; ch++ )
                next[i-1][ch] = next[i][ch];
            next[i-1][t[i]-'a'] = i;
        }
        int pos = 0;
        for ( int i = 0; i < s_len; i++ )
        {
            pos = next[pos][s[i]-'a'];
            if ( pos == -1 )
                return false;
        }
        
        return true;
    }
};

// recurisve solution works as well 
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if ( s.empty() )
            return true;
        if ( t.empty() )
            return false;
        
        if ( s.front() == t.front() )
            return isSubsequence(s.substr(1),t.substr(1));
        else
            return isSubsequence(s,t.substr(1));
    }
};