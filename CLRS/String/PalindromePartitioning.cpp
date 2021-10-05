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

// backtrack to visit each and every substring 
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> curList;
        dfs(res,s,0,curList);
        return res;
    }
    
    void dfs(vector<vector<string>> &res, string s, int start, vector<string>& curList)
    {
        if ( start >= s.size() )
            res.push_back(curList);
        for( int e = start; e < s.size(); e++ )
        {
            if ( IsPalindrome(s,start,e) )
            {
                curList.push_back(s.substr(start,e-start+1));
                dfs(res,s,e+1,curList);
                curList.pop_back();
            }
        }
    }
    
    bool IsPalindrome(string &s, int l, int h)
    {
        while( l < h )
        {
            if (s[l++] != s[h--])
                return false;
        }
        return true;
    }
};



// To avoid repeating checking palindrome substrings, we can preprocess the palindrome information first, and then just check the array in the 
// dfs search calls

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<vector<bool>> dp(s.size(),vector<bool>(s.size(),false));
        vector<string> curList;
        getPalindromeDP(s,dp);
        dfs(res,s,0,curList,dp);
        return res;
    }
    
    void dfs(vector<vector<string>> &res, string s, int start, vector<string>& curList, vector<vector<bool>> const& dp)
    {
        if ( start >= s.size() )
            res.push_back(curList);
        for ( int e = start; e < s.size(); e++ )
        {
            if ( dp[start][e] )
            {
                curList.push_back(s.substr(start,e-start+1));
                dfs(res,s,e+1,curList,dp);
                curList.pop_back();
            }
        }
    }
    
    void getPalindromeDP( string const& s, vector<vector<bool>> &dp)
    {
        for ( int len = 1; len <= s.size(); len++ )
        {
            for ( int i = 0; i <= s.size() - len; i++ )
            {
                int j = i + len - 1;
                dp[i][j] = s[i] == s[j] && (j - i <= 2 || dp[i+1][j-1] );
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