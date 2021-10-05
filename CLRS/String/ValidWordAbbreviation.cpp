/*
A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with their lengths. The lengths should not have leading zeros.

For example, a string such as "substitution" could be abbreviated as (but not limited to):

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (no substrings replaced)
The following are not valid abbreviations:

"s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
"s010n" (has leading zeros)
"s0ubstitution" (replaces an empty substring)
Given a string word and an abbreviation abbr, return whether the string matches the given abbreviation.

A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: word = "internationalization", abbr = "i12iz4n"
Output: true
Explanation: The word "internationalization" can be abbreviated as "i12iz4n" ("i nternational iz atio n").
Example 2:

Input: word = "apple", abbr = "a2e"
Output: false
Explanation: The word "apple" cannot be abbreviated as "a2e".
 

Constraints:

1 <= word.length <= 20
word consists of only lowercase English letters.
1 <= abbr.length <= 10
abbr consists of lowercase English letters and digits.
All the integers in abbr will fit in a 32-bit integer.


*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int w_len = word.size(), a_len = abbr.size();
        int s1 = 0, s2 = 0;
        while( s1 < w_len && s2 < a_len )
        {
            if (abbr[s2] >= 'a' && abbr[s2] <= 'z' )
            {
                if ( word[s1++] != abbr[s2++] )
                    return false;
            }
            else if ( abbr[s2] == '0' )
            {
                return false;
            }
            else {
                int len = 0;
                while( s2 < a_len && (abbr[s2] >= '0' && abbr[s2] <= '9') )
                {
                    len = len * 10 + (abbr[s2] - '0');
                    s2++;
                }
                s1 += len;
            }
        }
        
        return s1 == w_len && s2 == a_len;
        
    }
};

// Two pointers 
class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0;
        while(i < word.size() && j < abbr.size())
        {
            if ( isdigit(abbr[j]) )
            {
                if ( abbr[j] == '0' )
                    return false;
                int len = 0;
                while( j < abbr.size() && isdigit(abbr[j]) )
                {
                    len = len * 10 + (abbr[j]-'0');
                    j++;
                }
                i += len;
            }
            else if ( word[i++] != abbr[j++] )
            {
                return false;
            }

        }
        
        return i == word.size() && j == abbr.size();
    }
};

int main()
{
    Solution s;
    string word = "internationalization", abbr = "i12iz4n";
    s.validWordAbbreviation(word,abbr);
}
