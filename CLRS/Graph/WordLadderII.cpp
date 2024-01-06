/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 5
endWord.length == beginWord.length
1 <= wordList.length <= 500
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.
The sum of all shortest transformation sequences does not exceed 105.
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordset(wordList.begin(),wordList.end());
        vector<vector<string>> res;
        unordered_map<string,vector<string>> graph;
        if ( wordset.count(endWord) == 0 ) 
          return {};
        
        if ( !bfs(graph,beginWord, endWord, wordset) ) 
          return {};
        
        dfs(graph, beginWord, endWord, {beginWord}, res);
        return res;
    }

    bool bfs(unordered_map<string,vector<string>>& graph, string beginWord, string endWord, unordered_set<string>& wordset) {
      unordered_set<string> curlevel{beginWord};
      while( !curlevel.empty() ) {
        for ( auto w : curlevel )
          wordset.erase(w);
          bool reachend = false;
          unordered_set<string> nextlevel;
          for ( auto w : curlevel ) {
            vector<string> children = getchildren(w,wordset);
            for (auto child : children ) {
              graph[w].push_back(child);
              nextlevel.insert(child);
              if ( child == endWord )
                reachend = true;
            }
          }
          if ( reachend ) 
            return true;
          curlevel = nextlevel;
      }

      return false;
    }

    vector<string> getchildren(string parent, unordered_set<string>& wordset) {
      vector<string> res;
      for ( int i = 0; i < parent.size(); i++ ) {
        char cur_ch = parent[i];
        for ( char c = 'a'; c <= 'z'; c++ ) {
          if ( c == cur_ch )
            continue;
          parent[i] = c;
          if ( wordset.count(parent) ) 
            res.push_back(parent);
        }
        parent[i] = cur_ch;
      }

      return res;
    }

    void dfs(unordered_map<string,vector<string>>& graph, string lastWord, string endWord, vector<string>&& path, vector<vector<string>>& res) {
      if ( lastWord == endWord ) {
        res.push_back(path);
        return; 
      }

      for ( auto child : graph[lastWord] ) {
        path.push_back(child);
        dfs(graph,child,endWord,move(path),res);
        path.pop_back();
      }
    }
};


// pure BFS 

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordset(wordList.begin(),wordList.end());
        vector<vector<string>> res;
        queue<vector<string>> paths{{{beginWord}}};
        while(!paths.empty()){
            unordered_set<string> curlevelvisited;
            for ( int i = paths.size(); i > 0; i-- ) {
              auto path = paths.front();
              paths.pop();
              string lastWord = path.back();
              for ( int i = 0; i < lastWord.size(); i++ ) {
                char cur_ch = lastWord[i];
                for ( char ch = 'a'; ch <= 'z'; ch++ ) {
                  lastWord[i] = ch;
                  if ( wordset.count(lastWord) ) {
                    curlevelvisited.insert(lastWord);
                    auto nextPath(path);
                    nextPath.push_back(lastWord);
                    if ( lastWord == endWord ) {
                      res.push_back(nextPath);
                    } else {
                      paths.push(nextPath);
                    }
                  }
                }
                lastWord[i] = cur_ch;
              }
            }

            for (auto it : curlevelvisited ) 
              wordset.erase(it);
        }

        return res;
    }
};

// traversing top down might encounter paths unnecessarily. However, traversing bottom up would only traverse the necessary paths. 
// Therefore, we need to remember a way to the way up. One way is to remember the children-parent relationship. Another easier way is to 
// remember the levels from beginWord to endWord. In this way, we only traverse a one upper level while traversing up. 
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string,int> m;
        vector<vector<string>> res;
        vector<string> path;
        unordered_set<string> wordset(wordList.begin(),wordList.end());
        if ( wordset.count(endWord) == 0 )
            return {};
        if ( wordset.count(beginWord) ) 
            wordset.erase(beginWord);
        queue<pair<string,int>> q;
        q.push({beginWord,1});
        while(!q.empty()) { 
            auto [word, step] = q.front();
            q.pop();
            m[word] = step;
            if ( word == endWord )
                break;
            for ( int i = 0; i < word.size(); i++ ) {
                char cur_ch = word[i];
                for ( char ch = 'a'; ch <= 'z'; ch++ ) {
                    word[i] = ch;
                    if ( wordset.count(word) ) {
                        wordset.erase(word);
                        q.push({word,step+1});
                    }
                }
                word[i] = cur_ch;
            }
        }

        // dfs starting from the endWord 
        path.push_back(endWord);
        dfs(res,path,m,endWord,beginWord);
        return res;
    }

    void dfs(vector<vector<string>>& res, vector<string>& path, unordered_map<string,int>& m, string lastWord, string beginWord) { 
        if ( lastWord == beginWord ) {
            reverse(path.begin(),path.end());
            res.push_back(path);
            reverse(path.begin(),path.end());
            return;
        }
        int step = m[lastWord];
        for ( int i = 0; i < lastWord.size(); i++ ) {
            char cur_ch = lastWord[i];
            for ( char ch = 'a'; ch <= 'z'; ch++ ) {
                lastWord[i] = ch;
                if ( m[lastWord] == step - 1 ) {
                    path.push_back(lastWord);
                    dfs(res,path,m,lastWord,beginWord);
                    path.pop_back();
                }
            }
            lastWord[i] = cur_ch;
        }
    }
};