/*
Given a string s, the power of the string is the maximum length of a non-empty substring that contains only one unique character.

Return the power of the string.

 

Example 1:

Input: s = "leetcode"
Output: 2
Explanation: The substring "ee" is of length 2 with the character 'e' only.
Example 2:

Input: s = "abbcccddddeeeeedcba"
Output: 5
Explanation: The substring "eeeee" is of length 5 with the character 'e' only.
Example 3:

Input: s = "triplepillooooow"
Output: 5
Example 4:

Input: s = "hooraaaaaaaaaaay"
Output: 11
Example 5:

Input: s = "tourist"
Output: 1
 

Constraints:

1 <= s.length <= 500
s contains only lowercase English letters.

*/

// maintain a local and global and update the max whenever it's a consecutive same char 
class Solution {
public:
    int maxPower(string s) {
        int power = 1, max_power = 1;
        char cur_ch = s[0];
        for ( int i = 1; i < s.size(); i++ )
        {
            if ( s[i] == cur_ch )
            {
                power++;
                max_power = max(max_power,power);
            }
            else 
            {
                cur_ch = s[i];
                power = 1;
            }
        }
        
        return max(max_power,power);
    }
};