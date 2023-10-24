/*
Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
 

Constraints:

1 <= s.length, p.length <= 3 * 104
s and p consist of lowercase English letters.

*/

// Compare each possible window again p 
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int slen = s.size(), plen = p.size();
        int l = 0, r = 0;
        vector<int> res;
        vector<int> s_win(26,0), p_win(26,0);
        for ( auto c : p )
            p_win[c-'a']++;
        if ( plen > slen )
            return res;
        for ( int r = 0; r < slen; r++ )
        {
            s_win[s[r]-'a']++;
            if ( r >= plen )
            {
                s_win[s[l++]-'a']--;
            }
            if ( s_win == p_win )
                res.push_back(r-plen+1);
        }

        return res;
    }
};