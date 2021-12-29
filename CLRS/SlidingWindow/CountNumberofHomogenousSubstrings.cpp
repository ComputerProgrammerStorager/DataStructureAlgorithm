/*
Given a string s, return the number of homogenous substrings of s. Since the answer may be too large, return it modulo 109 + 7.

A string is homogenous if all the characters of the string are the same.

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
Example 2:

Input: s = "xy"
Output: 2
Explanation: The homogenous substrings are "x" and "y".
Example 3:

Input: s = "zzzzz"
Output: 15
 

Constraints:

1 <= s.length <= 105
s consists of lowercase letters.
*/

// remember the left index, and if the newly expanded char is not the same, we update the left index 
class Solution {
public:
    int countHomogenous(string s) {
        int n = s.size(), l = 0, ans = 0;
        for ( int r = 0; r < n; r++ )
        {
            if ( s[r] != s[l] )
            {
                l = r;
                r--;
            }
            else 
            {
                ans += r-l+1;
                ans %= 1000000007;
            }
        }
        
        return ans;
    }
};