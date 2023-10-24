/*
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

 

Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achive this answer too.
 

Constraints:

1 <= s.length <= 105
s consists of only uppercase English letters.
0 <= k <= s.length
*/

// consider each and every unique char as the potential max counted char 
class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_set<char> uniques; 
        int max_len = 0;
        for ( auto c : s )
            uniques.insert(c);
        for ( auto c : uniques )
        {
            int l = 0, r = 0, cnt = 0;
            while( r < s.size() )
            {
                if ( s[r] == c )
                    cnt++;
                while(!isvalidwin(l,r,cnt,k))
                {
                    if ( s[l++] == c )
                        cnt--;
                }
                max_len = max(max_len,r-l+1);
                r++;
            }
        }
        return max_len;
    }
private:
    bool isvalidwin(int s, int e, int cnt, int k)
    {
        return e-s+1-cnt <= k;
    }
};

// We can only track the max_freq 
// we don't need to reduce max_freq as our goal is to move out a non-max char and update the max freq doesn't increase the longest length.
class Solution {
public:
    int characterReplacement(string s, int k) {
        int max_len = 0, max_cnt = 0;
        unordered_map<char,int> m;
        int l = 0;
        for ( int r = 0; r < s.size(); r++ )
        {
            m[s[r]]++;
            max_cnt = max(max_cnt,m[s[r]]);
            while(r-l+1-max_cnt > k )
            {
                m[s[l++]]--;
            }
            max_len = max(max_len,r-l+1);
        }

        return max_len;
    }
};