/*
Given a string s, return true if s is a good string, or false otherwise.

A string s is good if all the characters that appear in s have the same number of occurrences (i.e., the same frequency).

 

Example 1:

Input: s = "abacbc"
Output: true
Explanation: The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2 times in s.
Example 2:

Input: s = "aaabb"
Output: false
Explanation: The characters that appear in s are 'a' and 'b'.
'a' occurs 3 times while 'b' occurs 2 times, which is not the same number of times.
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.
*/

class Solution {
public:
    bool areOccurrencesEqual(string s) {
        unordered_map<char,int> m;
        int cnt = -1;
        for ( auto c : s )
            m[c]++;
        if ( m.size() == 1 ) 
            return true;
        for ( auto it : m )
        {
            if ( cnt == -1 )
                cnt = it.second;
            else
            {
                if ( it.second != cnt )
                    return false;
            }
        }

        return true;
    }
};

class Solution {
public:
    bool areOccurrencesEqual(string s) {
        int cnt[26] = {0};
        if ( s.size() == 0 )
            return false;
        for ( auto c : s )
            cnt[c-'a']++;
        int chars = 0, occurrence = 0;
        for ( int i = 0; i < 26; i++ )
            if ( cnt[i] )
            {
                chars++;
                occurrence = cnt[i];
            }
        if ( chars == 1 )
            return true;
        for ( int i = 0; i < 26; i++ )
        {
            if ( cnt[i] != 0 && cnt[i] != occurrence )
                return false;
        }

        return true;
    }
};