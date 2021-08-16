/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.
*/

// idea: Trie + DFS 
// we first construct a Trie containing all the words and then use dfs to start with each and every position to see if we could find any word in the trie
// note to avoid revisiting nodes and backtrack 

class Solution {
    
    class TrieNode {
        public:
        TrieNode *children[26];
        bool IsWord;
        TrieNode() {
            for ( int i = 0; i < 26; i++ )
                children[i] = nullptr;
            IsWord = false;
        }
    };
    unordered_set<string> res;
    bool visited[12][12];
    vector<pair<int,int>> dir{{1,0},{-1,0},{0,1},{0,-1}};
    TrieNode *root;
    int m, n;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new TrieNode();
        m = board.size();
        n = board[0].size();
        
        
        for ( auto w : words )
        {
            TrieNode *node = root;
            for ( auto ch : w )
            {
                if ( node->children[ch-'a'] == nullptr )
                {
                    node->children[ch-'a'] = new TrieNode;
                }
                node = node->children[ch-'a'];
            }
            
            node->IsWord = true;
        }
        
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                visited[i][j] = true;
                string cur_word;
                dfs(board,i,j,cur_word,root);
                visited[i][j] = false;
            }
        vector<string> ans(res.begin(),res.end());
        
        return ans;
    }
    
    void dfs( vector<vector<char>> &board, int i, int j, string &cur_word, TrieNode* node)
    {
        if ( node->children[board[i][j]-'a'] == nullptr )
            return ;
        node = node->children[board[i][j]-'a'];
        cur_word.push_back(board[i][j]);
        
        if ( node->IsWord )
            res.insert(cur_word);
           
        for ( int d = 0; d < 4; d++ )
        {
            int x = i + dir[d].first;
            int y = j + dir[d].second;
            if ( x < 0 || x >= m || y < 0 || y >= n || visited[x][y] )
                continue;
            visited[x][y] = true;
            dfs(board,x,y,cur_word,node);
            visited[x][y] = false;
        }
        
        cur_word.pop_back();
    }
};

// The above solution will search the same word as many times as it may exist on board.. 
// one optimization is to remove the word once it has been found by augmenting a count member to the TrieNode struct 
class Solution {
    
    class TrieNode {
        public:
        TrieNode *children[26];
        bool IsWord;
        int cnt;
        TrieNode() {
            for ( int i = 0; i < 26; i++ )
                children[i] = nullptr;
            IsWord = false;
            cnt = 0;
        }
    };
    unordered_set<string> res;
    bool visited[12][12];
    vector<pair<int,int>> dir{{1,0},{-1,0},{0,1},{0,-1}};
    TrieNode *root;
    int m, n;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new TrieNode();
        m = board.size();
        n = board[0].size();
        
        
        for ( auto w : words )
        {
            TrieNode *node = root;
            for ( auto ch : w )
            {
                if ( node->children[ch-'a'] == nullptr )
                {
                    node->children[ch-'a'] = new TrieNode;
                }
                node = node->children[ch-'a'];
                node->cnt++;
            }
            
            node->IsWord = true;
        }
        
        for ( int i = 0; i < m; i++ )
            for ( int j = 0; j < n; j++ )
            {
                visited[i][j] = true;
                string cur_word;
                dfs(board,i,j,cur_word,root);
                visited[i][j] = false;
            }
        vector<string> ans(res.begin(),res.end());
        
        return ans;
    }
    
    void dfs( vector<vector<char>> &board, int i, int j, string &cur_word, TrieNode* node)
    {
        if ( node->children[board[i][j]-'a'] == nullptr || node->children[board[i][j]-'a']->cnt == 0 )
            return ;
        node = node->children[board[i][j]-'a'];
        cur_word.push_back(board[i][j]);
        
        if ( node->IsWord )
        {
            res.insert(cur_word);
            removeWord(cur_word);
        }
           
        for ( int d = 0; d < 4; d++ )
        {
            int x = i + dir[d].first;
            int y = j + dir[d].second;
            if ( x < 0 || x >= m || y < 0 || y >= n || visited[x][y] )
                continue;
            visited[x][y] = true;
            dfs(board,x,y,cur_word,node);
            visited[x][y] = false;
        }
        
        cur_word.pop_back();
    }
    
    void removeWord( string &w )
    {
        TrieNode *node = root;
        for ( auto ch : w )
        {
            node = node->children[ch-'a'];
            node->cnt--;
        }
        
        if ( node->cnt == 0 && node->IsWord == true )
            node->IsWord = false;
    }
};