/*
Given a string s, return the length of the longest substring that contains at most two distinct characters.


Example 1:

Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.
Example 2:

Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.
 

Constraints:

1 <= s.length <= 104
s consists of English letters.
*/

// maintain the righmost index of numbers in the sliding window 
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char,int> rightmost;
        int maxlen = 0, l = 0;
        for ( int r = 0; r < s.size(); r++ )
        {
            rightmost[s[r]] = r;
            while(rightmost.size() > 2 )
            {
                if ( l == rightmost[s[l]] )
                    rightmost.erase(s[l]);
                l++;
            }
            maxlen = max(r-l+1,maxlen);
        }
        return maxlen;
    }
};

// maintain occurrence
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char,int> m;
        int maxlen = 0, l = 0;
        for ( int r = 0; r < s.size(); r++ )
        {
            m[s[r]]++;
            if (m.size() > 2 )
            {
                while( --m[s[l]] != 0 )
                    l++;
                m.erase(s[l]);
                l++;
            }
            maxlen = max(r-l+1,maxlen);
        }
        return maxlen;
    }
};
