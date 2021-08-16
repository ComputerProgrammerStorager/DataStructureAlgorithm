/*
You are given two strings, word1 and word2. You want to construct a string in the following manner:

Choose some non-empty subsequence subsequence1 from word1.
Choose some non-empty subsequence subsequence2 from word2.
Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.

A palindrome is a string that reads the same forward as well as backward.

 

Example 1:

Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
Example 2:

Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a palindrome.
Example 3:

Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so return 0.
 

Constraints:

1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.
*/

#include "../Common/common_api.h"

class Solution {
public:
    int longestPalindrome(string word1, string word2) {
        string tmp = word1+word2;
        int n = tmp.size(), res = 0, m = word1.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        
        for ( int i = 0; i < n; i++ )
            dp[i][i] = 1;
        for ( int len = 2; len <= n; len++ )
        {
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i + len - 1;
                if ( tmp[i] == tmp[j] )
                {
                    dp[i][j] = dp[i+1][j-1] + 2;
                    if ( i < m && j >= m )
                    {
                        res = max(res,dp[i][j]);
                    }
                }
                else 
                {
                    dp[i][j] = max(dp[i+1][j],dp[i][j-1]);
                }
            }
        }
        PrintVector2(dp);
        return res;
    }
};

class Solution2 {
public:
    int longestPalindrome(string word1, string word2) {
        string tmp = word1+word2;
        int n = tmp.size(), res = 0, m = word1.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        
        for ( int i = 0; i < n; i++ )
            dp[i][i] = 1;
        for ( int len = 2; len <= n; len++ )
        {
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i + len - 1;
                if ( tmp[i] == tmp[j] )
                {
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
                else 
                {
                    dp[i][j] = max(dp[i+1][j],dp[i][j-1]);
                }
                if ( i < m && j >= m )
                {
                    res = max(res,dp[i][j]);
                }
            }
        }
        PrintVector2(dp);
        return res;
    }
};

int main()
{
    string w1 = "aa", w2 = "bb";
    string w3 = "cccb", w4 = "cbba";
    Solution s;
    Solution2 s2;
    cout << "Using Solution " << endl;
    cout << s.longestPalindrome(w1,w2) << endl;
    cout << "Using Solution2 " << endl;
    cout << s2.longestPalindrome(w1,w2) << endl;
}