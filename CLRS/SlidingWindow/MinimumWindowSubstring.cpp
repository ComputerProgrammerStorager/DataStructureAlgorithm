/*
Given two strings s and t of lengths m and n respectively, return the minimum window 
substring
 of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 

Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
 

Follow up: Could you find an algorithm that runs in O(m + n) time?
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int slen = s.size(), tlen = t.size(); 
        unordered_map<char,int> t_m, s_m;
        if ( slen < tlen || (slen == 0) && (tlen == 0) )
            return "";
        for ( auto c : t )
            t_m[c]++;
        int checks = t_m.size(), formed = 0, l = 0, min_len = INT_MAX, min_start;
        for (int r = 0; r < slen; r++ )
        {
            s_m[s[r]]++;
            if ( t_m.find(s[r]) != t_m.end() && t_m[s[r]] == s_m[s[r]] )
                formed++;
            while( l <= r && formed == checks )
            {
                if ( min_len > r-l+ 1 )
                {
                    min_len = r-l+1;
                    min_start = l;
                }
                char out_char = s[l];
                s_m[s[l++]]--;
                if ( t_m.count(out_char) && t_m[out_char] > s_m[out_char] )
                    formed--;
            }
        }
        return min_len == INT_MAX ?  "" : s.substr(min_start,min_len);
    }
};