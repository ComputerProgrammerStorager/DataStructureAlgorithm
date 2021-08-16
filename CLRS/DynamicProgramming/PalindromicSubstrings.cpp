/*
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Note:

The input string length won't exceed 1000.
*/

// check if any of the substring is a palindromic individually 
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int res = 0;
        vector<vector<int>> dp(n,vector(n,0));
        for ( int i = 0; i < n; i++ )
        {
            dp[i][i] = 1;
            res += dp[i][i];
        }
        
        for ( int len = 2; len <= n; len++ )
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i + len - 1;
                if ( s[i] == s[j] )
                {
                    if ( len == 2 )
                        dp[i][j] = 1;
                    else 
                        dp[i][j] = dp[i+1][j-1];
                }
                
                res += dp[i][j];
            }
        return res;
    }
};

// Expand around center (could be singe char or dual same chars )
class Solution {
public:
    int countSubstrings(string s) {
        int res = 0;
        int n = s.size();
        for ( int i = 0; i < n; i++ )
        {
            res += CountCenter(s,i,i,n);
            res += CountCenter(s,i,i+1,n);
        }
        return res;
    }
    
    int CountCenter( string const &ss, int s, int e, int len )
    {
        int ans = 0;
        while ( s >= 0 && e < len )
        {
            if ( ss[s] != ss[e] )
                break;
            s--;
            e++;
            ans++;
        }
        
        return ans;
    }
};