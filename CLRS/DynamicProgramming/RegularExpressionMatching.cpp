/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*' where: 

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input: s = "mississippi", p = "mis*is*p*."
Output: false
 

Constraints:

0 <= s.length <= 20
0 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
*/

#include "../Common/common_api.h"

constexpr int TESTS_NUM = 5;

// Recursion method:
// if both empty, true;
// if the pattern has it's second as "*", then 
//    a. if we perceive the preceding char and "*" as 0, then we continue to check s vs p with the first two chars removed 
//    b. if we perceive it has at least one, then we check the first chars are equal and remove the first char from s 
// if the pattern has it's second not "*", then the first chars must be the same and move forward one char to continue comparision 

class SolutionRecurs {
public:
   static bool isMatch(string s, string p) {
        if ( p.empty() ) 
            return s.empty();
        if ( p.length() >= 2 && p[1] == '*' )
        {
            return isMatch(s,p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1),p));
        }
        else 
        {
            return (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1),p.substr(1)));
        }
    }
};

// dp[r][c] represents the matching result of s[0...r-1] and p[0...c-1]
// First we intialize the entire dp table to false, and set dp[0][0] to true which denotes that an empty pattern matches an empty string 
// Then we intialize the values of dp[0][c] to deal with the bases case of s = "" and p = "x*x*....."
// Then walk through the table and for dp[r][c]:
// a. if the last char matches, i.e., p[c-1] == s[r-1] || p[c-1] == '.', then the matching result would be the matching of the string minus the last char, i.e., dp[r-1][c-1];
// b. if the last char DOESN'T match, then the only case that could lead to a match is when the current char in pattern is "*", i.e., p[c-1] == '*', and in this case we could have two different cases:
//      1. The repeated char preceding "*" doesn't match the last char in the target string, then "x*" must be eliminated, i.e., the dp[r][c] = dp[r][c-2], which is the matching result of s and p with "x*" removed. 
//      2. The repeated cahr preceding "*" matches the last char in the target string, then we have three cases:
//          2.1: "x*" represents zero effective char in the matching, then the result is dp[r][c-2]
//          2.2: "x*" represents one or more effective chars in the matching and it's equal to s[r-1], then the result equals to dp[r-1][c] given that s[r-1] could be generated by "x*". This case is illustrated as follows:
//                s =  |...|matched char|....|
//                         |
//                          ----------->  s[0..r-2] vs p[0...c-1] ===> dp[r-1][c]
//                                      |
//                p =  |...|    x *     |....|

class Solution_dp {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m+1,vector(n+1,false));
        dp[0][0] = true;
        for ( int c = 1; c <= n; c++ )
        {
            if ( p[c-1] == '*' && dp[0][c-2] )
                dp[0][c] = true;
        }
        
        for ( int r = 1; r <= m; r++ )
            for ( int c = 1; c <= n; c++ )
            {
                if ( p[c-1] == s[r-1] || p[c-1] == '.' )
                    dp[r][c] = dp[r-1][c-1];
                else if ( p[c-1] == '*' )
                {
                    if ( s[r-1] != p[c-2] && p[c-2] != '.' )
                        dp[r][c] = dp[r][c-2];
                    else 
                        dp[r][c] = dp[r][c-2] || dp[r-1][c];
                }
            }
        return dp[m][n];
    }
};

typedef struct {
    string s;
    string p;
    bool res;
} test_case_entry;

int main()
{
    test_case_entry TestSuite[TESTS_NUM] = {
        {"aa","a",false},
        {"aa","a*",true},
        {"ab",".*",true},
        {"aab","c*a*b",true},
        {"mississippi","mis*is*p*.",false},
    };
    SolutionRecurs s_recur;
    bool OverallResFail = false;
    int i = 0;
    for ( ; i < TESTS_NUM; i++ )
    {
        if ( TestSuite[i].res != s_recur.isMatch(TestSuite[i].s,TestSuite[i].p) )
        {
            OverallResFail = true;
            break;
        }
    }

    if ( OverallResFail )
    {
        cout <<"TestSuite failed at test case %d using recursiong method" << i << endl;
    }
    else 
    {
        cout << "All test cases passed using recursion method!" << endl;
    }
    OverallResFail = false;
    for ( i = 0 ; i < TESTS_NUM; i++ )
    {
        if ( TestSuite[i].res != s_recur.isMatch(TestSuite[i].s,TestSuite[i].p) )
        {
            OverallResFail = true;
            break;
        }
    }

    if ( OverallResFail )
    {
        cout <<"TestSuite failed at test case %d using DP method" << i << endl;
    }
    else 
    {
        cout << "All test cases passed using DP method!" << endl;
    }
}

