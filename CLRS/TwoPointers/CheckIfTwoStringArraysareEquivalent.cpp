/*
Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.

A string is represented by an array if the array elements concatenated in order forms the string.

 

Example 1:

Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
Output: true
Explanation:
word1 represents string "ab" + "c" -> "abc"
word2 represents string "a" + "bc" -> "abc"
The strings are the same, so return true.
Example 2:

Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
Output: false
Example 3:

Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
Output: true
 

Constraints:

1 <= word1.length, word2.length <= 103
1 <= word1[i].length, word2[i].length <= 103
1 <= sum(word1[i].length), sum(word2[i].length) <= 103
word1[i] and word2[i] consist of lowercase letters.
*/


class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int w1 = 0, w2 = 0, str1 = 0, str2 = 0, w1_cnt = word1.size(), w2_cnt = word2.size();
        while( w1 < w1_cnt && w2 < w2_cnt ) {
            if ( word1[w1][str1++] != word2[w2][str2++] ) 
                return false;
            if ( str1 == word1[w1].size() ) {
                str1 = 0;
                w1++;
            }
            if ( str2 == word2[w2].size() ) {
                str2 = 0;
                w2++;
            }
        }
        return w1 == w1_cnt && w2 == w2_cnt;
    }
};