/*
Given a string s, return the last substring of s in lexicographical order.

 

Example 1:

Input: s = "abab"
Output: "bab"
Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
Example 2:

Input: s = "leetcode"
Output: "tcode"
 

Constraints:

1 <= s.length <= 4 * 105
s contains only lowercase English letters.
*/

// Key observations: the last substring must start with the largest chars in the string, and there could be multipe of them 
// When all later substrings are prefixes of the first substring, the first string wins 
// If not, then we can alway maintain the first as the current last, and check the next, without skipping any later substrings 
// So we consider two substrings starting at i and j, which are initialized to 0 and 1, with a len to grow. 
// Note: at any time, s[i,i+k-1] == s[j,j+k-1],
// during the check, there could be 