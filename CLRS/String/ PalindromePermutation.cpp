/*
Given a string s, return true if a permutation of the string could form a 
palindrome
 and false otherwise.

 

Example 1:

Input: s = "code"
Output: false
Example 2:

Input: s = "aab"
Output: true
Example 3:

Input: s = "carerac"
Output: true
 

Constraints:

1 <= s.length <= 5000
s consists of only lowercase English letters.
*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int cnt[26] = {0}, odd_cnt = 0;
        for ( auto c : s ) {
            cnt[c-'a']++;
            if ( cnt[c-'a'] & 1 ) {
                odd_cnt++;
            } else {
                odd_cnt--;
            }
        }

        return odd_cnt < 2;
    }
};