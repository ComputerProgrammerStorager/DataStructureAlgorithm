/*
Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

 

Example 1:

Input: s = "abccccdd"
Output: 7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
Example 2:

Input: s = "a"
Output: 1
Example 3:

Input: s = "bb"
Output: 2
 

Constraints:

1 <= s.length <= 2000
s consists of lowercase and/or uppercase English letters only.

*/

// all even chars can be used to construct the string, but only one odd char can be added at last 
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char,int> ch2freq;
        int res = 0;
        bool remainder = false;
        for ( auto c : s )
            ch2freq[c]++;
        for ( auto it : ch2freq )
        {
            if ( it.second % 2 )
            {
                remainder = true;
            }
            res += (it.second / 2) * 2;
        }
        
        if ( remainder )
            res++;
        return res;
    }
};