/*
Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
 

Example 1:

Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
Example 2:

Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
 

Constraints:

1 <= s.length <= 5 * 104
1 <= words.length <= 5000
1 <= words[i].length <= 50
s and words[i] consist of only lowercase English letters.

*/

// we calculate the next array once and use it for checking every string 
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int s_len = s.size(); 
        s = "*" + s;
        vector<vector<int>> next(s_len+1,vector<int>(26,-1));   //next[i][ch]: the first position of ch after position i 
        
        for ( int i = s_len; i >= 1; i-- )
        {
            for ( int ch = 0; ch < 26; ch++ )
                next[i-1][ch] = next[i][ch];
            next[i-1][s[i]-'a'] = i;
        }
        
        int cnt = 0;
        for ( auto w : words )
        {
            int pos = 0;
            for ( auto c : w )
            {
                pos = next[pos][c-'a'];
                if ( pos == -1 )
                    break;
            }
            if ( pos != -1 )
                cnt++;
        }
        
        return cnt;
    }
};

// we don't remember anything already got from s
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int s_len = s.size();
        int cnt = 0;
        for ( auto w : words )
        {
            int i = 0, j = 0;
            while ( i < w.size() && j < s_len)
            {
                if ( w[i] == s[j] )
                    i++;
                j++;
            }
            cnt += (i == w.size());
        }
        
        return cnt;
    }
};