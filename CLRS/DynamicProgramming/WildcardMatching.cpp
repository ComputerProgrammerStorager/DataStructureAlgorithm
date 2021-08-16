/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input: s = "adceb", p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input: s = "acdcb", p = "a*c?b"
Output: false
*/


#include "../Common/common_api.h"

class Solution_Recur{
public:
    bool isMatch(string s, string p) {
        string tmp = RemoveDuplicateStars(p);
        unordered_map<string, bool> m;
        helper(s,tmp,m);
        return m[s+"+"+tmp];
    }
    
    bool helper( string s, string p, unordered_map<string,bool> &m )
    {
        string key = s+"+"+p;
        if (m.count(key))
            return m[key];
        if ( p == s || p == "*")
            m[key] = true;
        else if ( p.empty() || s.empty() )
        {
            m[key] = false;
        }
        else if ( p[0] == s[0] || p[0] == '?' )
        {
            m[key] = helper(s.substr(1),p.substr(1),m);
        }
        else if ( p[0] == '*' )
        {
            m[key] = helper(s,p.substr(1),m) || helper(s.substr(1),p,m);
        }
        else 
        {
            m[key] = false;
        }
        
        return m[key];
    }
    
    string RemoveDuplicateStars( string &p )
    {
        string tmp;
        for ( int i = 0; i < p.length(); i++ )
        {
            if ( p[i] != '*' || tmp.length() == 0 || (tmp.length() > 0 && tmp[tmp.length()-1] != '*' ) )
            {
                tmp.append(1,p[i]);
            }
        }

        return tmp;
    }
};


class Solution_dp {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m+1,vector(n+1,false));
        dp[0][0] = true;
        for ( int c = 1; c <= n; c++ )
        {
            dp[0][c] = dp[0][c-1] && p[c-1] == '*';
        }
        
        for ( int i = 1; i <= m; i++ )
            for ( int j = 1; j <= n; j++ )
            {
                if ( p[j-1] == s[i-1] || p[j-1] == '?' )
                    dp[i][j] = dp[i-1][j-1];
                else if ( p[j-1] == '*' )
                {
                    dp[i][j] = dp[i][j-1] || dp[i-1][j];        // "*" could represent 0 (then dp[i][j-1]) or one/more (dp[i-1][j])
                }
            }
        return dp[m][n];
    }
};


int main()
{
    string p = "***a";
    string str = "aaaa";
    Solution_dp s_dp;
    s_dp.isMatch(str,p);
}