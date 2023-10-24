/*
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
 

Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
 

Constraints:

1 <= word.length <= 25
word in addWord consists of lowercase English letters.
word in search consist of '.' or lowercase English letters.
There will be at most 2 dots in word for search queries.
At most 104 calls will be made to addWord and search.
*/

// hash map mapping len to strings of the same length 
class WordDictionary {
    unordered_map<int,vector<string>> len2strings;
public:
    WordDictionary() {
        len2strings.clear();
    }
    
    void addWord(string word) {
        int len = word.size();
        if ( len == 0 )
            return;
        len2strings[len].push_back(word);
    }
    
    bool search(string word) {
        int len = word.size();
        if ( len2strings.count(len) )
        {
            for ( auto str : len2strings[len] )
            {
                int i = 0; 
                while( i < len && (word[i] == str[i] || word[i] == '.') )
                {
                    i++;
                }
                if ( i == len )
                    return true;
            }
        }

        return false;
    }
};

// use trie.. when encountered a wild char, explore all possiblities 
class TrieNode {
public:
    unordered_map<char, TrieNode*> m;
    bool isWord;
    TrieNode() {
        m.clear();
        isWord = false;
    };
};
class WordDictionary {
private:
    TrieNode *root;
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode *walk = root;
        for ( auto ch : word )
        {
            if ( walk->m.count(ch) == 0 )
                walk->m[ch] = new TrieNode();
            walk = walk->m[ch];
        }
        walk->isWord = true;
    }
    
    bool search(string word) {
        return searchInNode(root,word);
    }
private:
    bool searchInNode(TrieNode *root, string word)
    {
        for ( int i = 0; i < word.size(); i++ )
        {
            if ( root->m.count(word[i]) == 0 )
            {
                if ( word[i] == '.' )
                {
                    for ( auto it : root->m )
                    {
                        if ( searchInNode(it.second,word.substr(i+1)) )
                            return true;
                    }
                }
                return false;
            } else {
                root = root->m[word[i]];
            }
        }

        return root->isWord;
    }
};
