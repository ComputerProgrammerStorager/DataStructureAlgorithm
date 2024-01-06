/*
There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are 
sorted lexicographically
 by the rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are multiple solutions, return any of them.

 

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.

*/

// construct the graph and topologic sort it 
class Solution {
public:
    string alienOrder(vector<string>& words) {
        queue<char> q;
        unordered_map<char,unordered_set<char>> adjlist;
        unordered_map<char,int> indegree;
        string res;
        for (auto w : words )
            for ( auto c : w )
                indegree[c] = 0;
        
        for ( int i = 1; i < words.size(); i++ ) {
            string w1 = words[i-1], w2 = words[i];
            int len1 = w1.size(), len2 = w2.size();
            if ( len1 > len2 && w1.substr(0,len2) == w2 ) 
                return "";
            for ( int i = 0; i < min(len1,len2); i++ ) {
                if ( w1[i] != w2[i] ) {
                    if ( adjlist[w1[i]].count(w2[i]) == 0 ) {
                        adjlist[w1[i]].insert(w2[i]);
                        indegree[w2[i]]++;
                    }
                    break;
                }
            }
        }

        for (auto ch : indegree ) {
            if ( ch.second  == 0 ) {
                q.push(ch.first);
            }
        }

        while(!q.empty()) { 
            auto cur = q.front();
            q.pop();
            res += cur;
            for ( auto n : adjlist[cur] ) {
                if ( --indegree[n] == 0 ) {
                    q.push(n);
                }
            }
        }

        return res.size() == indegree.size() ? res : "";
    }
};