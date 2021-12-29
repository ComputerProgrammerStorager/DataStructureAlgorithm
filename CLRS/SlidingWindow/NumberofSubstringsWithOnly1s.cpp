/*
Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.
Example 2:

Input: s = "101"
Output: 2
Explanation: Substring "1" is shown 2 times in s.
Example 3:

Input: s = "111111"
Output: 21
Explanation: Each substring contains only 1's characters.
Example 4:

Input: s = "000"
Output: 0
 

Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.

*/

// we remember the last left zero, and then move right to expand the window
class Solution {
public:
    int numSub(string s) {
        int n = s.size(), zero_idx = -1;
        long res = 0;
        for ( int i = 0; i < n; i++ )
        {
            if ( s[i] == '0' )
            {
                zero_idx = i;
            }
            else 
            {
                res += i - zero_idx;
                res %= 1000000007;
            }
        }
        
        return res;
    }
};