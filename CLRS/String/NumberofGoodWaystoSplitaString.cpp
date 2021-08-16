/*
You are given a string s, a split is called good if you can split s into 2 non-empty strings p and q where its concatenation is equal to s and the number of distinct letters in p and q are the same.

Return the number of good splits you can make in s.

 

Example 1:

Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
Example 2:

Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
Example 3:

Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.
Example 4:

Input: s = "acbadbaada"
Output: 2
 

Constraints:

s contains only lowercase English letters.
1 <= s.length <= 10^5
*/

#include "../Common/common_api.h"

class Solution {
public:
    int numSplits(string s) {
        int n = s.size(), ways = 0;
        unordered_set<char> left, right_s;
        unordered_map<char,int> right_m;
        if ( n > 1 )
        {
            for ( int i = 0; i < n; i++ )
            {
                right_s.insert(s[i]);
                right_m[s[i]]++;
            }
            for (int i = 0; i < n -1; i++)
            {
                left.insert(s[i]);
                if ( --right_m[s[i]] == 0 )
                    right_s.erase(s[i]);
                if ( left.size() == right_s.size() )
                {
                    ways++;
                }
            }
        }
        
        return ways;
    }
};


class Solution {
public:
    int numSplits(string s) {
        int n = s.size(), res = 0;
        if ( n < 2 )
            return 0;
        vector<int> left(n,0), right(n,0);
        int seen[26] = {0};
        seen[s[0]-'a'] = 1;
        for ( int i = 1; i < n; i++ )
        {
            seen[s[i]-'a']++;
            left[i] = left[i-1] + (seen[s[i]-'a'] == 1);
        }
        memset(seen,0,sizeof(seen));
        seen[s[n-1]-'a'] = 1;
        for ( int i = n-2; i >= 0; i-- )
        {
            seen[s[i]-'a']++;
            right[i] = right[i+1] + (seen[s[i]-'a'] == 1);
        }
        
        for ( int i = 0; i < n-1; i++ )
        {
            if ( left[i] == right[i+1] )
                res++;
        }
        
        return res;
    }
};

int main()
{
    string str = "aacaba";
    Solution s;
    s.numSplits(str);
}