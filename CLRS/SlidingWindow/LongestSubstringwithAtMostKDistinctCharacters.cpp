/*
Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

 

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
 

Constraints:

1 <= s.length <= 5 * 104
0 <= k <= 50
*/

#include "../Common/common_api.h"


// we maintain the rightmost position of the chars which are currrently in the sliding window
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> rightmost_idx;
        int maxlen = 1, left = 0, right = 0;
        int n = s.size();
        if ( n * k == 0 )
            return 0;
        while ( right < n )
        {
            rightmost_idx[s[right]] = right;
            right++;
            if ( rightmost_idx.size() == k+1 )
            {
                int lowest_idx = INT_MAX;
                for ( pair<char,int> element : rightmost_idx )
                {
                    lowest_idx = min(lowest_idx,element.second);
                }
                rightmost_idx.erase(s[lowest_idx]);
                left = lowest_idx + 1;
            }
            
            maxlen = max(maxlen,right-left);
        }
        
        return maxlen;
    }
};

// once we have more than k then we need to remove the leftmost till we get to reduce the number of chars in the window 
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char,int> m;
        int maxlen = 0, l = 0;
        for ( int r = 0; r < s.size(); r++ )
        {
            m[s[r]]++;
            if ( m.size() == k + 1 )
            {
                while ( --m[s[l]] != 0 )
                    l++;
                m.erase(s[l]);
                l++;
            }
            maxlen = max(maxlen,r-l+1);
        }
        
        return maxlen;
    }
};

int main()
{
    string str = "eceba";
    int k  = 2;
    Solution s;
    s.lengthOfLongestSubstringKDistinct(str,2);
}