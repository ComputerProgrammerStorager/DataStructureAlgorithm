/*
Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.

Return the maximum possible product of the lengths of the two palindromic subsequences.

A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.

 

Example 1:

example-1
Input: s = "leetcodecom"
Output: 9
Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
The product of their lengths is: 3 * 3 = 9.
Example 2:

Input: s = "bb"
Output: 1
Explanation: An optimal solution is to choose "b" (the first character) for the 1st subsequence and "b" (the second character) for the 2nd subsequence.
The product of their lengths is: 1 * 1 = 1.
Example 3:

Input: s = "accbcaxxcxx"
Output: 25
Explanation: An optimal solution is to choose "accca" for the 1st subsequence and "xxcxx" for the 2nd subsequence.
The product of their lengths is: 5 * 5 = 25.
 

Constraints:

2 <= s.length <= 12
s consists of lowercase English letters only.
*/

// use bit mask to enumerate all disjoint subsequences ( n1 & n2 == 0 )
class Solution {
public:
    int maxProduct(string s) {
        int max_product = 0, n = s.size();
        for ( int n1 = 1; n1 < ( 1<<n); n1++ ) 
            for ( int n2 = 1; n2 < (1 << n); n2++ ) {
                if ( (n1 & n2) == 0 ) {
                    auto [b1,len1] = isPalindrome(s,n1);
                    auto [b2,len2] = isPalindrome(s,n2);
                    if ( b1 && b2 ) 
                        max_product = max(max_product,len1 * len2);
                }
            }

        return max_product;
    }

    pair<bool,int> isPalindrome(const string& s, int bitmask) {
        string tmp;
        int n = s.size();
        for (int i = 0; i < n; i++ ) {
            if ( bitmask & (1<<i) ) 
                tmp += s[i];
        }
        for ( int i = 0, j = tmp.size() -1; i < j; i++, j-- ) {
            if ( tmp[i] != tmp[j] )
                return {false,0};
        }
        return {true,tmp.size()};
    }
};

/// use dfs to generate all disjoint subsequences 
class Solution {
public:
    int maxProduct(string s) {
        int ans = 0;
        string s1,s2;
        helper(0,s,s1,s2,ans);
        return ans;
    }

    void helper(int idx, const string& s, string& s1, string& s2, int& ans) {
        if ( idx == s.size() ) {
            if ( isPalindrome(s1) && isPalindrome(s2) ) {
                ans = max(ans,(int)s1.length() * (int)s2.length());
            }
            return;
        } 
        s1 += s[idx];
        helper(idx+1,s,s1,s2,ans);
        s1.pop_back();

        s2 += s[idx];
        helper(idx+1,s,s1,s2,ans);
        s2.pop_back();

        helper(idx+1,s,s1,s2,ans);
    }

    bool isPalindrome(const string& s ){
        for (int i = 0, j = s.size() -1; i < j; i++,j-- ) {
            if (s[i] != s[j])
                return false;
        }
        return true;
    }
};