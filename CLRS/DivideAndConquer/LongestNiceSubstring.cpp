/*
A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.

Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.

 

Example 1:

Input: s = "YazaAay"
Output: "aAa"
Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
"aAa" is the longest nice substring.
Example 2:

Input: s = "Bb"
Output: "Bb"
Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.
Example 3:

Input: s = "c"
Output: ""
Explanation: There are no nice substrings.
 

Constraints:

1 <= s.length <= 100
s consists of uppercase and lowercase English letters.
*/

// Naive solution would be checking each substring if it's nice 
// Key observation is that if we find a char which doesn't satisfy the condition, then this could not be included in any substring
// which means we will only look into either its left or right results
// Therefore, divide and conquer comes into play :-) 
class Solution {
public:
    string longestNiceSubstring(string s) {
        if ( s.size() == 0 )
            return s;
        unordered_set<char> chars;
        for ( auto c : s )
            chars.insert(c);
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( chars.count(toupper(s[i])) && chars.count(tolower(s[i])) )
                continue;
            string left = longestNiceSubstring(s.substr(0,i));
            string right = longestNiceSubstring(s.substr(i+1));
            return left.size() >= right.size() ? left : right;
        }

        return s;
    }
};