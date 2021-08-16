/*
Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
 

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.

*/

// two passes
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        if ( n < 2 )
            return true;
        for ( int i = 0, j = n-1; i < j; i++, j-- )
        {
            while( !isalnum(s[i]) && i < j )
                i++;
            while( !isalnum(s[j]) && i < j ) 
                j--;
            if ( toupper(s[i]) != toupper(s[j]) )
                return false;
        }
        
        return true;
    }
};