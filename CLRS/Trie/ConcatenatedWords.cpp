/*
Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

 

Example 1:

Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
"dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Example 2:

Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
 

Constraints:

1 <= words.length <= 104
0 <= words[i].length <= 1000
words[i] consists of only lowercase English letters.
0 <= sum(words[i].length) <= 6 * 105
*/

#include "../Common/common_api.h"


// since longer words can only constructed from shorter words, so we first sort the string based on their length 
// and gradually build up the trie 
class Solution {
private:
    vector<string> res;
    class TrieNode { 
        public:
        TrieNode *next[26];
        bool IsWord;
        TrieNode() {
            for ( int i = 0; i < 26; i++ )
                next[i] = nullptr;
            IsWord = false;
        }
    };
    TrieNode *root;
    
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        
        #if 1
        struct cmp {
            bool operator()(string const& left, string const &right) {
                return left.size() < right.size();
            }
        };
        
        sort(words.begin(),words.end(),cmp());
        #endif 
        root = new TrieNode();
        //sort(words.begin(),words.end(),[](string const &left, string const &right){return left.size() < right.size();});
        
        for ( auto w : words )
        {
            if ( w != "" && checkWord(w) )
                res.push_back(w);
            insertWord(w);
        }
        
        return res;
    }
    
    void insertWord( string const &w )
    {
        TrieNode *node = root;
        for ( auto ch : w )
        {
            if ( node->next[ch-'a'] == nullptr )
                node->next[ch-'a'] = new TrieNode();
            node = node->next[ch-'a'];
        }
        node->IsWord = true;
    }
    
    // check if the word is in trie
    bool checkWord(string const &w)
    {
        vector<bool> visited(w.size(),false);
        return dfs(w,0,visited);
    }
    
    bool dfs(string const &w, int cur, vector<bool> &visited)
    {
        if ( cur == w.size() )
            return true;
        if ( visited[cur] )
            return false;
        
        TrieNode *node = root;
        for ( int i = cur; i < w.size(); i++ )
        {
            if ( node->next[w[i]-'a'] )
            {
                node = node->next[w[i]-'a'];
                if ( node->IsWord && dfs(w,i+1,visited) )
                    return true;
            }
            else
            {
                break;
            }
        }
        
        visited[cur] = true;        // is not valid starting from cur position
        return false;
    }
};

// similary idea but using dynamical programming to check each and every word..
// this leads to time limit exceeded as dp takes O(n) time 
class Solution {
    unordered_set<string> S;
    
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> res;
        sort(words.begin(),words.end(),[](string const &left, string const &right){return left.size() < right.size();});
        
        for ( auto w : words )
        {
            if ( w != "" && checkWord(w) )
                res.push_back(w);
            S.insert(w);
        }
        
        return res;
    }
    
    bool checkWord(string const& w)
    {
        vector<bool> dp(w.size()+1,false);
        dp[0] = true;
        for ( int i = 0; i <= w.size(); i++ )
        {
            if ( dp[i] )
            {
                for ( auto s : S )
                {
                    if ( i + s.size() <= w.size() && s == w.substr(i,s.size()) ) 
                        dp[i+s.size()] = true;
                }
            }
        }
        
        return dp[w.size()];
    }
};

int main()
{
    vector<string> strs = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    Solution s;
    s.findAllConcatenatedWordsInADict(strs);
}