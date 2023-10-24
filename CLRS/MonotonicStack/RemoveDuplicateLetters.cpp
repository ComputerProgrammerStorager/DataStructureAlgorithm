/*
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is 
the smallest in lexicographical order
 among all possible results.

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
 

Constraints:

1 <= s.length <= 104
s consists of lowercase English letters.
 

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
*/

// idea: 
// for each char being considered to be included in the result, we can swap any existing chars which could be placed after it 
// on the conditions that the existing char has a later occurrence and it's larger than the char being considered. 
class Solution {
public:
    string smallestSubsequence(string s) {
        int n = s.size(); 
        string res;
        unordered_map<char,int> last;
        unordered_set<char> has; 
        for ( int i = 0; i < n; i++ )
            last[s[i]] = i;
        for ( int i = 0; i < n; i++ )
        {
            if ( !has.count(s[i]) )
            {
                while( !res.empty() && res.back() > s[i] && last[res.back()] > i ) 
                {
                    has.erase(res.back());
                    res.pop_back();
                }
                has.insert(s[i]);
                res += s[i];
            }
        }

        return res;
    }
};