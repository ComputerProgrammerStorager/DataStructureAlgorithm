/*
    A trie is an space and time efficient data structure for querying the existing of an element in a dictionary 
*/
#include "../Common/common_api.h"

const int ELEM_SPACE_SZ = 26;           // assume only lowercase english letters are used to construct the words 
class Trie {
public:
    class TrieNode {
        public:
        TrieNode *next[ELEM_SPACE_SZ];
        int cnt;               // how many words is the current char included into
        bool IsWord;            // is there word ending at the current char from the root
        TrieNode(){
            for ( int i = 0; i < ELEM_SPACE_SZ; i++ )
                next[i] = nullptr;
            cnt = 0;
            IsWord = false;
        }
    };
private:
    TrieNode *root;     // the root of the trie
    unordered_set<string> words;        // for vefification purpose only if ever needed
public:
    Trie();
    ~Trie();
    bool InsertWord(string const &w);
    bool CheckWordExistence(string const &w);
    void RemoveWord(string const &w);
    void VisualizeTrie();       //@TODO: implement visualizing the Trie properly
};

Trie::Trie()
{
    root = new TrieNode();
    words.clear();
}

Trie::~Trie()
{
    delete root;
}

// insert a word to the Trie
bool Trie::InsertWord( string const &w )
{
    vector<TrieNode *> AllocatedMemory;
    bool InsertSuccess = true, ret = true;
    TrieNode *node = root, *tmp = nullptr;
    for ( auto ch : w )
    {
        if ( node->next[ch-'a'] == nullptr )
        {
            tmp = new TrieNode();
            if ( tmp == nullptr )
            {
                InsertSuccess = false;
                break;
            }
            else 
            {
                tmp->cnt++;
                node->next[ch-'a'] = tmp;
                AllocatedMemory.push_back(tmp);
            }
        }
        node = tmp;
    }
    if ( InsertSuccess )
    {
        node->IsWord = true;
        words.insert(w);
    }
    else 
    {
        for ( auto n : AllocatedMemory )
            delete n;
        ret = false;
    }

    return ret;
}

bool Trie::CheckWordExistence( string const &w )
{
    bool ret = false;
    TrieNode *node = root;
    for ( auto ch : w )
    {
        if ( node->next[ch-'a'] == nullptr || node->next[ch-'a']->cnt == 0 )
        {
            break;
        }
        node = node->next[ch-'a'];
    }
    if ( node->IsWord )
    {
        ret = true;
    }

    return ret;
}

void Trie::RemoveWord( string const &w )
{
    TrieNode *node = root;
    for ( auto ch : w )
    {
        if ( node->next[ch-'a'] == nullptr )
            break;
        node->next[ch-'a']->cnt--;
        node = node->next[ch-'a'];
    }

    if ( node->IsWord && node->cnt == 0 )
        node->IsWord = false;
}

int main()
{
    Trie t;
}