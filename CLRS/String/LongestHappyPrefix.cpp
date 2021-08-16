/*
A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s. Return the longest happy prefix of s .

Return an empty string if no such prefix exists.

 

Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
Example 3:

Input: s = "leetcodeleet"
Output: "leet"
Example 4:

Input: s = "a"
Output: ""
 

Constraints:

1 <= s.length <= 10^5
s contains only lowercase English letters.
*/

// brute force: we check each prefix
class Solution {
public:
    string longestPrefix(string s) {
        int n = s.length();
        int res = 0, len;
        for ( len = n - 1; len > 0; len-- )
        {
            if ( s.substr(0,len) == s.substr(n-len,len))
                break;
        }
        return s.substr(0,len);
    }
};

// suffix[i]: the longest happpy prefix of the substring ending at the i_th position, s[0..i]
// and if k = suffix[i].. then s[0..i] has this pattern: s[0..K-1] = s[i-k+1,i]
// X X X X -------- X X X X 
//      k-1               i
// then suffix[i] depends on the some previous suffix value, walking back as in the way like KMP 
// let j = suffix[i-1], then we check whether s[j] == [i] ? If not, we walk the way back until we find 
// the equavilency or reach the begining 
//  X X X X X X -------- X X X X X X 
//            j                    i
// 
class Solution {
public:
    string longestPrefix(string s) {
        int n = s.length();
        int res = 0, len;
        vector<int> suffix(n,0);
        if ( n == 0 )
            return 0;
        suffix[0] = 0;
        for ( int i = 1; i < n; i++ )
        {
            int j = suffix[i-1];
            while ( j > 0 && s[j] != s[i] )
                j = suffix[j];
            suffix[i] = s[i] != s[j] ? 0 : j + 1;
        }
        return s.substr(0,suffix[n-1]);
    }
};