/*
Given a string s, return true if the s can be palindrome after deleting at most one character from it.

 

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
*/

class Solution {
public:
    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while( l < r )
        {
            if ( s[l] !=s [r] )
                return check(s,l+1,r) || check(s,l,r-1);
            l++;
            r--;
        }

        return true;
    }
private:
    bool check(string s, int l, int r)
    {
        while( l < r )
        {
            if ( s[l] != s[r] )
                return false;
            l++;
            r--;
        }
        return true;
    }
};