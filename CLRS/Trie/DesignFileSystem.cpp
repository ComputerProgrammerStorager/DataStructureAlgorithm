/*
You are asked to design a file system that allows you to create new paths and associate them with different values.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string "" and "/" are not.

Implement the FileSystem class:

bool createPath(string path, int value) Creates a new path and associates a value to it if possible and returns true. Returns false if the path already exists or its parent path doesn't exist.
int get(string path) Returns the value associated with path or returns -1 if the path doesn't exist.
 

Example 1:

Input: 
["FileSystem","createPath","get"]
[[],["/a",1],["/a"]]
Output: 
[null,true,1]
Explanation: 
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input: 
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output: 
[null,true,true,2,false,-1]
Explanation: 
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/leet", 1); // return true
fileSystem.createPath("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.
 

Constraints:

2 <= path.length <= 100
1 <= value <= 109
Each path is valid and consists of lowercase English letters and '/'.
At most 104 calls in total will be made to createPath and get.
*/

// use hashmap to store every string and value pairs 
class FileSystem {
    unordered_map<string,int> m;
public:
    FileSystem() {
        m.clear();
        m["/"] = 0;
    }
    
    bool createPath(string path, int value) {
        if ( path.empty() || (path.size() == 1 && path == "/") || m.count(path) )
            return false;
        int last_idx = path.find_last_of('/');
        string parent = path.substr(0,last_idx);
        if ( m.count(parent) == 0 && parent.size() > 1)
            return false;
        m[path] = value;
        return true;
    }
    
    int get(string path) {
        if ( m.count(path) == 0 )
            return -1;
        return m[path];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */

// we could use trie to save space 

class TrieNode {
public:
    string name;
    int value;
    unordered_map<string,TrieNode*> children;
    TrieNode(string name) : name(name), value(-1){

    }

};
class FileSystem {
    TrieNode *root;
public:
    FileSystem() {
        root = new TrieNode("");
    }
    
    bool createPath(string path, int value) {
        vector<string> components = getcomponents(path);
        TrieNode *cur = root;
        for (int i = 0; i < components.size(); i++ )
        {
            if ( cur->children.count(components[i]) == 0 )
            {
                if ( i == components.size() - 1 )
                {
                    TrieNode *next = new TrieNode(components[i]);
                    cur->children[components[i]] = next;
                }
                else 
                {
                    return false;
                }
            }

            cur = cur->children[components[i]];
        }
        if ( cur->value != -1 )
        {
            return false;
        }
        cur->value = value;
        return true;
    }
    
    int get(string path) {
        vector<string> components = getcomponents(path);
        TrieNode *cur = root;
        for ( int i = 0; i < components.size(); i++ )
        {
            if ( cur->children.count(components[i]) == 0 )
                return -1;
            cur = cur->children[components[i]];
        }
        return cur->value;
    }
private:
    vector<string> getcomponents(string s) {
        vector<string> res;
        stringstream ss(s);
        string word;
        while(getline(ss,word,'/'))
            if ( word.size() != 0 )
                res.push_back(word);
        return res;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */

