/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]
 

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.
*/

#include "../Common/common_api.h"

// dynamic programming used for preprocess the string and then dfs 
class Solution {

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> ans;
        int n = s.size();
        vector<vector<bool>> dp(n,vector<bool>(n));
        preprocess(s,dp);
        dfs(s,0,res,ans,dp);
        return res;
    }
    
    void preprocess(string const& s, vector<vector<bool>> &dp)
    {
        int n = s.size();
        for ( int i = 0; i < n; i++ )
            dp[i][i] = true;
        for ( int i = 0; i < n-1; i++ )
            dp[i][i+1] = s[i] == s[i+1];
        
        for ( int len = 3; len <= n; len++ )
        {
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i+len-1;
                dp[i][j] = (s[i] == s[j] && dp[i+1][j-1]);
                // note we can include the above len 1 and 2 cases in the loop using the following recurrence equation
                // dp[i][j] = (s[i] == s[j] && (j-i <= 2 || dp[i+1][j-1]));
            }
        }
    }
    
    void dfs(string const& s, int cur, vector<vector<string>> &res, vector<string> &ans, vector<vector<bool>> &dp)
    {
        if ( cur == s.size() )
        {
            res.push_back(ans);
            return;
        }
        
        for ( int i = cur; i < s.size(); i++ )
        {
            if ( dp[cur][i] )
            {
                ans.push_back(s.substr(cur,i-cur+1));
                dfs(s,i+1,res,ans,dp);
                ans.pop_back();
            }
        }
    }
};

int main()
{
    int a = 20;
    int **p;
    p = &(&a); 
    cout << **p << endl;
}