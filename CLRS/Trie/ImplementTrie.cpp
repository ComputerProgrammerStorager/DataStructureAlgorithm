/*
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
 

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
 

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, search, and startsWith.
*/

class Node {
public:
    Node* children[26];
    bool is_word;
    Node() {
        is_word = false;
        for ( int i = 0; i < 26; i++ )
            children[i] = nullptr;
    }
};

class Trie {
private:
    Node *root;
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node *tmp = root;
        for ( int i = 0; i < word.size(); i++ )
        {
            if ( tmp->children[word[i]-'a'] == nullptr )
                tmp->children[word[i]-'a'] = new Node();
            tmp = tmp->children[word[i]-'a'];
        }

        tmp->is_word = true;
    }
    
    bool search(string word) {
        Node *tmp = root;
        for ( int i = 0; i < word.size(); i++ )
        {
            if ( tmp->children[word[i]-'a'] == nullptr)
                return false;
            tmp = tmp->children[word[i]-'a'];
        }

        return tmp->is_word;
    }
    
    bool startsWith(string prefix) {
        Node *tmp = root;
        for ( int i = 0; i < prefix.size(); i++ )
        {
            if ( tmp->children[prefix[i]-'a'] == nullptr )
                return false;
            tmp = tmp->children[prefix[i]-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */