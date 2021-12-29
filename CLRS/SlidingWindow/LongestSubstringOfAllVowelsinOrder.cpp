/*
A string is considered beautiful if it satisfies the following conditions:

Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.

Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.

A substring is a contiguous sequence of characters in a string.

 

Example 1:

Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
Output: 13
Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
Example 2:

Input: word = "aeeeiiiioooauuuaeiou"
Output: 5
Explanation: The longest beautiful substring in word is "aeiou" of length 5.
Example 3:

Input: word = "a"
Output: 0
Explanation: There is no beautiful substring, so return 0.
 

Constraints:

1 <= word.length <= 5 * 105
word consists of characters 'a', 'e', 'i', 'o', and 'u'.
*/

// The resetting sliding window is when the new char is smaller than the last char and the qualified condition is when the window has all five vowels
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int n = word.size(), l = 0, ans = 0;
        char last_char;
        unordered_set<char> s;
        if ( n == 0 )
            return ans;
        last_char = word[0];
        for ( int r = 0; r < n; r++ )
        {
            if ( word[r] < last_char )
            {
                l = r;
                s.clear();
            }
            s.insert(word[r]);
            if ( s.size() == 5 )
                ans = max(ans,r-l+1);
            last_char = word[r];
        }
        
        return ans;
    }
};