/*
Given an array of strings words representing an English Dictionary, return the longest word in words that can be built one character at a time by other words in words.

If there is more than one possible answer, return the longest word with the smallest lexicographical order. If there is no answer, return the empty string.


Example 1:

Input: words = ["w","wo","wor","worl","world"]
Output: "world"
Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:

Input: words = ["a","banana","app","appl","ap","apply","apple"]
Output: "apple"
Explanation: Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
 

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 30
words[i] consists of lowercase English letters.
*/

// sort the strings per the criteria and stop once one if found to meet the condition which is checking each of prefix substrings exsits 
// in the dictionary 

class Solution {
public:
    string longestWord(vector<string>& words) {
        string res = "";
        auto cmp = [](string const &s1, string const &s2) {
            return (s1.size() > s2.size()) || (s1.size() == s2.size() && s1 < s2);
        };
        
        sort(words.begin(),words.end(),cmp);
        
        unordered_set<string> word_set(words.begin(),words.end());
        
        for ( auto w : words )
        {
            int len = 1;
            for ( ; len < w.size(); len++ )
            {
                if (word_set.count(w.substr(0,len)) == 0 ) 
                {
                    break;
                }
            }
            if ( len == w.size() )
            {
                res = w;
                break;
            }
        }
        
        return res;
    }
};


// Same idea but use a trie to find the words 
class Solution {
    struct TrieNode {
        int str_idx;
        TrieNode *nodes[26];
        TrieNode() {
            str_idx  = -1;
            for (int i = 0; i < 26; i++ )
                nodes[i] = nullptr;
        };
    };
public:
    string longestWord(vector<string>& words) {
        TrieNode *root = new TrieNode;
        for (int i = 0; i < words.size(); i++ )
            InsertWord(root,words[i],i);
        string res = "";
        trie_dfs(root,res,words);
        return res;
    }
    
    void trie_dfs(TrieNode *root, string &res,vector<string> const &words)
    {
        stack<TrieNode *> s;
        s.push(root);
        while ( !s.empty() )
        {
            TrieNode *node = s.top();
            s.pop();
            if ( node->str_idx >= 0 || node == root )
            {
                if (node != root)
                {
                    string w = words[node->str_idx];
                    if ( w.length() > res.length() || (w.length() == res.length() && w < res) )
                        res = w;
                }
                
                for ( int i = 0; i < 26; i++ )
                    if ( node->nodes[i])
                        s.push(node->nodes[i]);
            }
        }
    }
    
    void InsertWord(TrieNode *root, string const &w, int idx )
    {
        TrieNode * walk = root;
        for ( auto c : w )
        {
            if (walk->nodes[c-'a'] == nullptr)
            {
                walk->nodes[c-'a'] = new TrieNode();
            }
            
            walk = walk->nodes[c-'a'];
        }
        walk->str_idx = idx;
    }
};