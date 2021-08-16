/*
A message containing letters from A-Z can be encoded into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode an encoded message, all the digits must be mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "111" can have each of its "1"s be mapped into 'A's to make "AAA", or it could be mapped to "11" and "1" ('K' and 'A' respectively) to make "KA". Note that "06" cannot be mapped into 'F' since "6" is different from "06".

Given a non-empty string num containing only digits, return the number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

 

Example 1:

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
Example 3:

Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with 0. The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20".
Since there is no character, there are no valid ways to decode this since all digits need to be mapped.
Example 4:

Input: s = "1"
Output: 1
 

Constraints:

1 <= s.length <= 100
s contains only digits and may contain leading zero(s).
*/

#include "../Common/common_api.h"
// Recursion with memoization
class Solution {
public:
    int numDecodings(string s) {
        unordered_map<string,int> m;
        return helper(s,m);
    }
    
    int helper(string s, unordered_map<string,int> &m)
    {
        int res = 0;
        if ( s.empty() )
            return 1;
        if ( s.size() == 1 )
        {
            if (s[0] >= '1' && s[0] <= '9' )
                return 1;
            else 
                return 0;
        }
        
        if (s[0] == '0')
            return 0;
        if ( m.count(s) )
            return m[s];
        res += helper(s.substr(1),m);
        int val = stoi(s.substr(0,2));
        if ( val <= 26 )
            res += helper(s.substr(2),m);
        m[s] = res;
        return res;
        
    }
};


// DP method: dp[i] means the decoding ways for string s[0...i-1]; 
class Solution_DP{
public:
    int numDecodings(string s) {
        int n = s.size();
        if ( n == 0 || ( n== 1 && (s[0] >= '0' && s[0] <= '9')) ) 
            return 1;
        else if ( n == 1 && s[0] == '0' )
            return 0;
        vector<int> dp(n+1,0);
        dp[0] = 1;
        dp[1] = s[0] == '0'? 0 : 1;
        for ( int i = 2; i <= n; i++ )
        {
            if ( s[i-1] <= '1' && s[i-1] >= '9' )
                dp[i] += dp[i-1];
            int val = stoi(s.substr(i-2,2));
            if ( s[i-2] != '0' && val <= 26 )
                dp[i] += dp[i-2];
        }
            
        return dp[n];
    }
};

// same as the above but use constant space considering it's only dependent on the previous two values, similar to fibonacci number series. 
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if ( n == 0 || ( n== 1 && (s[0] >= '1' && s[0] <= '9')) ) 
            return 1;
        else if ( n == 1 && s[0] == '0' )
            return 0;
        int a = 1;
        int b = s[0] == '0' ? 0 : 1;
        for ( int i = 2; i <= n; i++ )
        {
            int current = 0;
            if (s[i-1] != '0' )
                current += b;
            int val = stoi(s.substr(i-2,2));
            if ( val >= 10 && val <= 26 )
                current += a;
            a = b;
            b = current;
        }
        
        return b;
    }
};

int main()
{
    string str = "12";
    Solution_DP s_dp;
    int res = s_dp.numDecodings(str);
    cout << "res = " << res << endl;
}