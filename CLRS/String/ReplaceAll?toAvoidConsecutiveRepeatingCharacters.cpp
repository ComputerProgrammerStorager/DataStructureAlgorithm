/*
Given a string s containing only lower case English letters and the '?' character, convert all the '?' characters into lower case letters such that the final string does not contain any consecutive repeating characters. You cannot modify the non '?' characters.

It is guaranteed that there are no consecutive repeating characters in the given string except for '?'.

Return the final string after all the conversions (possibly zero) have been made. If there is more than one solution, return any of them. It can be shown that an answer is always possible with the given constraints.

 

Example 1:

Input: s = "?zs"
Output: "azs"
Explanation: There are 25 solutions for this problem. From "azs" to "yzs", all are valid. Only "z" is an invalid modification as the string will consist of consecutive repeating characters in "zzs".
Example 2:

Input: s = "ubv?w"
Output: "ubvaw"
Explanation: There are 24 solutions for this problem. Only "v" and "w" are invalid modifications as the strings will consist of consecutive repeating characters in "ubvvw" and "ubvww".
Example 3:

Input: s = "j?qg??b"
Output: "jaqgacb"
Example 4:

Input: s = "??yw?ipkj?"
Output: "acywaipkja"
 

Constraints:

1 <= s.length <= 100
s contains only lower case English letters and '?'.

*/

// for each ?, we replace it with a character that is neither the previous nor the following one. 
class Solution {
public:
    string modifyString(string s) {
        string res;
        char prev = ' ';
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( s[i] != '?' )
            {
                res.push_back(s[i]);
                prev = s[i];
            }
            else
            {
                char can = pickcandidate(prev, i == s.size() - 1 ? ' ' : s[i+1]);
                res.push_back(can);
                prev = can;
            }
        }
        
        return res;
    }
    
    char pickcandidate( char prev, char next)
    {
        for ( char can = 'a'; can <= 'z'; can++ )
        {
            if ( can != prev && can != next )
                return can;
        }
        return ' ';
    }
};