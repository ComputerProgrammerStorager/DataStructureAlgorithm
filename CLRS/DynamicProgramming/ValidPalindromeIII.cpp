/*
Given a string s and an integer k, return true if s is a k-palindrome.

A string is k-palindrome if it can be transformed into a palindrome by removing at most k characters from it.

 

Example 1:

Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.
Example 2:

Input: s = "abbababa", k = 1
Output: true
 

Constraints:

1 <= s.length <= 1000
s consists of only lowercase English letters.
1 <= k <= s.length
*/

// We define a function that returns the min operations required to make a substring to be a palindrome 
// Then it is a recursive process to expand the string to its entirety 
class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        dp.resize(s.size(),vector<int>(s.size(),-1));
        return minRemove(s,0,s.size()-1) <= k;
    }
private:
    vector<vector<int>> dp;
    int minRemove(string s, int l, int r )
    {
        if ( l == r )
            return 0;
        if ( l + 1 == r )
            return s[l] != s[r];
        if ( dp[l][r] != -1 )
            return dp[l][r];
        if ( s[l] == s[r] )
            return dp[l][r] = minRemove(s,l+1,r-1);
        return dp[l][r] = 1+min(minRemove(s,l+1,r),minRemove(s,l,r-1));
    }
};


// we can use bottom-up filling order 
class Solution {
public:
    vector<vector<int>> memo;
    int isValidPalindrome(string &s, int i, int j) {

        // Base case, only 1 letter remaining.
        if (i == j)
            return 0;

        // Base case 2, only 2 letters remaining.
        if (i == j - 1)
            return s[i] != s[j];

        // Return the precomputed value if exists.
        if (memo[i][j] != -1)
            return memo[i][j];

        // Case 1: Character at `i` equals character at `j`
        if (s[i] == s[j])
            return memo[i][j] = isValidPalindrome(s, i + 1, j - 1);

        // Case 2: Character at `i` does not equal character at `j`.
        // Either delete character at `i` or delete character at `j`
        // and try to match the two pointers using recursion.
        // We need to take the minimum of the two results and add 1
        // representing the cost of deletion.
        return memo[i][j] = 1 + min(isValidPalindrome(s, i + 1, j), isValidPalindrome(s, i, j - 1));
    }
    bool isValidPalindrome(string s, int k) {
        memo.resize(s.length(), vector<int>(s.length(), -1));

        // Return true if the minimum cost to create a palindrome by only deleting the letters
        // is less than or equal to `k`.
        return isValidPalindrome(s, 0, s.length() - 1) <= k;
    }
};