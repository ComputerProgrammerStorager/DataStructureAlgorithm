/*
Given a string s, return the number of distinct substrings of s.

A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string and any number (possibly zero) from the back of the string.

 

Example 1:

Input: s = "aabbaba"
Output: 21
Explanation: The set of distinct strings is ["a","b","aa","bb","ab","ba","aab","abb","bab","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba","aabbaba"]
Example 2:

Input: s = "abcdefg"
Output: 28
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
 

Follow up: Can you solve this problem in O(n) time complexity?

*/

// use a trie to check distinct substrings.. essentially it checks all possible substrings 
class Solution {
    class TrieNode {
        public: 
            TrieNode *next[26];
    };
public:
    int countDistinct(string s) {
        TrieNode *root = new TrieNode();
        int count = 0, n = s.size();
        for ( int i = 0; i < n; i++ )
        {
            TrieNode *walk = root;
            for ( int j = i; j < n; j++ )
            {
                if ( walk->next[s[j]-'a'] == NULL )
                {
                    walk->next[s[j]-'a'] = new TrieNode();
                    count++;
                }
                walk = walk->next[s[j]-'a'];
            }
        }
        
        return count;
    }

// we maintain a rolling hash for each of the possible len 
class Solution {
    typedef uint64_t ULL;
public:
    int countDistinct(string s) {
        int n = s.size(), base = 26, count = 0;
        
        for ( int len = 1; len <= n; len++ )
        {
            ULL rolling_hash = 0, power = 1;
            unordered_set<ULL> hashes;
            for ( int i = 0; i < len - 1; i++ )
                power *= base;
            
            for ( int i = 0; i < n; i++ )
            {
                if ( i >= len )
                    rolling_hash -= (s[i-len]-'a')*power;
                rolling_hash = rolling_hash * base + (s[i] - 'a');
                if ( i >= len - 1 )
                    hashes.insert(rolling_hash);
            }
            
            count += hashes.size();
        }
        return count;
    }
};