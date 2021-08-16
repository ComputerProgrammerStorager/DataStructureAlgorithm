/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/

class Solution {
    
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st(wordDict.begin(),wordDict.end());
        int len = s.size();
        vector<bool> dp(len+1,false);     // dp[i]: represent s[0,i-1) is valid.. return dp[len]
        dp[0] = true;
        
        for ( int i = 0; i <= len; i++ )
        {
            if ( dp[i] )
            {
                for ( auto w : st )
                {
                    if ( s.substr(i,w.size()) == w && i+w.size() <= len )
                        dp[i+w.size()] = true;
                }
            }
        }
        
        return dp[len];
    }
};


// DFS + Trie
class Solution {

    class TrieNode {
        public:
        TrieNode *children[26];
        bool IsEnd;
        TrieNode() {
            for (int i = 0; i < 26; i++ )
                children[i] = nullptr;
            IsEnd = false;
        }
    };
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        TrieNode root;
        int n = s.size();
        vector<bool> memo(n,false);
        for ( auto w : wordDict )
        {
            InsertTrieNode(&root,w);
        }
        
        return dfs(s,0,&root,memo);
    }
    
    bool dfs(string s, int cur, TrieNode *root, vector<bool> &memo)
    {
        TrieNode *node = root;
        if ( cur == s.size() )
            return true;
        if ( memo[cur] )
            return false;
        
        for ( int next = cur; next < s.size(); next++ )
        {
            if ( node->children[s[next]-'a'] == nullptr )
                break;
            node = node->children[s[next]-'a'];
            if ( node->IsEnd && dfs(s,next+1,root,memo) )
            {
                return true;
            }
        }
        memo[cur] = true;
        return false;
    }
    
    void InsertTrieNode( TrieNode *root, string const &s)
    {
        TrieNode *node = root;
        for ( int i = 0; i < s.size(); i++ )
        {
            int pathidx = s[i]-'a';
            
            if ( node->children[pathidx] == nullptr )
                node->children[pathidx] = new TrieNode();
            node = node->children[pathidx];
        }
        node->IsEnd = true;
    }
};