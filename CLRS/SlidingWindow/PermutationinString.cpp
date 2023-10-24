/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

 

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
 

Constraints:

1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters.
*/

// maintain two windows and check if they are equal as the window expands and shrinks
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m1[26] = {0}, m2[26] = {0};
        int n1 = s1.size(), n2 = s2.size();
        if ( n1 > n2 )
            return false;
        for ( int i = 0; i < n1; i++ )
        {
            m1[s1[i]-'a']++;
            m2[s2[i]-'a']++;
        }
        if ( match(m1,m2) )
            return true;
        for ( int l = 0, r = n1; r < n2; r++ )
        {
            m2[s2[r]-'a']++;
            m2[s2[l++]-'a']--;
            if ( match(m1,m2) )
                return true;
        }

        return match(m1,m2);
    }
private:
    bool match(int m1[], int m2[])
    {
        for ( int i = 0; i < 26; i++ )
        {
            if ( m1[i] != m2[i] )
                return false;
        }
        return true;
    }
};