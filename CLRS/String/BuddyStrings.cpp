/*
Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].

For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
 

Example 1:

Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
Example 2:

Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.
Example 3:

Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.
Example 4:

Input: s = "aaaaaaabc", goal = "aaaaaaacb"
Output: true
 

Constraints:

1 <= s.length, goal.length <= 2 * 104
s and goal consist of lowercase letters.


*/

// we just need to track the number of differing chars 
// Pay special attention to when the two strings are the same, in this case, it is only true when there are 
// at least one char appearching at least twice. 
class Solution {
public:
    bool buddyStrings(string s, string goal) {
        int s_sz = s.size(), goal_sz = goal.size();
        if ( s_sz != goal_sz || s_sz <= 1 )
            return false;
        vector<int> diff_pos;
        for ( int i = 0; i < s_sz; i++ )
        {
            if ( s[i] != goal[i] )
                diff_pos.push_back(i);
        }
        
        if ( diff_pos.size() == 2 )
        {
            return s[diff_pos[0]] == goal[diff_pos[1]] && s[diff_pos[1]] == goal[diff_pos[0]];
        } else if ( diff_pos.size() == 0 )
        {
            int cnt[26] = {0};
            for ( auto c : s )
                cnt[c-'a']++;
            for ( int i = 0; i < 26; i++ )
                if ( cnt[i] > 1 )
                    return true;
        } 
        return false;
    }
};