/*
Design a data structure that simulates an in-memory file system.

Implement the FileSystem class:

FileSystem() Initializes the object of the system.
List<String> ls(String path)
If path is a file path, returns a list that only contains this file's name.
If path is a directory path, returns the list of file and directory names in this directory.
The answer should in lexicographic order.
void mkdir(String path) Makes a new directory according to the given path. The given directory path does not exist. If the middle directories in the path do not exist, you should create them as well.
void addContentToFile(String filePath, String content)
If filePath does not exist, creates that file containing given content.
If filePath already exists, appends the given content to original content.
String readContentFromFile(String filePath) Returns the content in the file at filePath.
*/

// path can be encoded in a Trie, and each TrieNode represents a component(file or dir) of the path. 
class FileSystem {
public:
    FileSystem() {
        root_ = new TrieNode();
    }
    
    vector<string> ls(string path) {
        auto cur = getTrieNode(path);
        if ( cur->isFile )
            return {getpath(path).back()};
        vector<string> res;
        for ( const auto it : cur->children )
        {
            res.emplace_back(it.first);
        }

        sort(res.begin(),res.end());
        return res;
    }
    
    void mkdir(string path) {
        auto cur = getTrieNode(path);
        cur->isFile = false;
    }
    
    void addContentToFile(string filePath, string content) {
        auto node = getTrieNode(filePath);
        node->content += content;
        node->isFile = true;
    }
    
    string readContentFromFile(string filePath) {
        return getTrieNode(filePath)->content;
    }
private:
    class TrieNode {
    public:
        bool isFile;
        string content;
        unordered_map<string, TrieNode*> children;      // both dir and files 
    };
    TrieNode *root_;

    TrieNode *getTrieNode(const string& path)
    {
        vector<string> paths = getpath(path);
        auto cur = root_;
        for ( const auto& next : paths )
            cur = cur->children[next];
        return cur;
    }

    TrieNode *insertTrieNode(const string& path)
    {
        vector<string> paths = getpath(path);
        auto cur = root_;
        for ( const auto& next : paths)
        {
            if ( !cur->children[next] )
                cur->children[next] = new TrieNode();
            cur = cur->children[next];
        }

        return cur;
    }
    
    vector<string> getpath(const string& path)
    {
        vector<string> res;
        stringstream ss(path);
        string word; 
        while(getline(ss,word,'/'))
        {
            if ( !word.empty() )
                res.emplace_back(word);
        }

        return res;
    }
};