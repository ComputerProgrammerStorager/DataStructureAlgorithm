/*
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
*/


// maintain a sliding window defined by the left side, then for each qualified left side, there will be n-r+1 substrings 
class Solution {
public:
    int numberOfSubstrings(string s) {
        int cnt[3] = {0}, r = 0, n = s.size(), res = 0;
        for ( int l = 0; l < n; l++ ) {
            while(r < n && cnt[0]*cnt[1]*cnt[2] == 0 )
            {
                cnt[s[r]-'a']++;
                r++;
            }
            if ( cnt[0] * cnt[1] * cnt[2] ) 
                res += n-r+1;
            cnt[s[l]-'a']--;
        }

        return res;
    }
};