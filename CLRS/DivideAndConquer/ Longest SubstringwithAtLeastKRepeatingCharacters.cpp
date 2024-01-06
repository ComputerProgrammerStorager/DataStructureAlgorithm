/*
Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.

if no such substring exists, return 0.

 

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 

Constraints:

1 <= s.length <= 104
s consists of only lowercase English letters.
1 <= k <= 105
*/

// divide and conquer: 
// we know that any character that appears less than k times must not be included in the substring. Therefore, we could divide the string into two strings and take the max of them 
class Solution {
public:
    int longestSubstring(string s, int k) {
        return helper(s,0,s.size(),k);
    }

    int helper(const string& s, int start, int end, int k) {
        unordered_map<char,int> m;
        if ( start == end )
            return 0;
        for ( int i = start; i < end; i++ )
            m[s[i]]++;

        for ( int i = start; i < end; i++ ) {
            if ( m[s[i]] >= k ) 
                continue;
            int right = i+1;
            while(right < end && m[s[right]] < k ) 
                right++;
            return max(helper(s,start,i,k),helper(s,right,end,k));
        }

        return end-start;
    }
};

// we can use sliding window to find the max substring len when the window contains a given amount of unique characters 
// Then we iterate all possible amount of unique characters and take the maximum 
class Solution {
public:
    int longestSubstring(string s, int k) {
        int res = 0, max_cnt = getMaxUnique(s);
        for (int i = 1; i <= max_cnt; i++ )
            res = max(res,helper(s,i,k));
        return res;
    }

    int getMaxUnique(const string& s ) {
        int res = 0, set = 0;
        for ( auto c : s ) {
            if ( (set & 1<<(c-'a')) == 0) {
                res++;
                set |= (1<<(c-'a'));
            }
        }

        return res;
    }

    // get the max substring len when it has unique distinct chars, each of which has at least k appearance 
    int helper(const string& s, int unique, int k) {
        int n = s.size(), l = 0, r = 0, cnt = 0, atleastK = 0;
        int m[26] = {0};
        int res = 0;
        while ( r < n ) {
            if ( cnt <= unique ) {
                if ( m[s[r]-'a']== 0 ) 
                    cnt++;
                if ( ++m[s[r]-'a'] == k )
                    atleastK++;
                r++;
            } else {
                if ( m[s[l]-'a'] == k )
                    atleastK--;
                if ( --m[s[l]-'a'] == 0 ) {
                    cnt--;
                }
                l++;
            }

            if ( cnt == unique && atleastK == cnt ) 
                res = max(res, r-l);
        }

        return res;
    }
};