/*
Given a string s, find the length of the longest substring without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
Example 4:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

*/

// Sliding window maintaing the current char set in the window.. As we extend the right boudary, if the 
// char has appreared before, then we need to shrink the window untill the same char is shifted out from the 
// window. 
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> w;
        int l = 0, r = 0, res = 0, n = s.size();
        while( r < n )
        {
            if ( w.count(s[r]) )
            {
                while( s[l] != s[r] )
                {
                    w.erase(s[l++]);
                }
                w.erase(s[l++]);
            }
            
            w.insert(s[r]);
            res = max(res,(int)w.size());
            r++;
        }
        return res;
    }
};


// instead of moving out the chars from the sliding window one by one, we could move shrink the window using one step 
// by remembering each char's last seen position. 
// Note: we need to make sure m[s[r]] > left to consider only chars in the window 
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> m;
        int left = -1, n = s.size(), res = 0;
        for ( int r = 0; r < n; r++ )
        {
            if ( m.count(s[r]) && m[s[r]] > left )
            {
                left = m[s[r]];
            }
            res = max(res,r-left);
            m[s[r]] = r;
        }
        
        return res;
    }
};