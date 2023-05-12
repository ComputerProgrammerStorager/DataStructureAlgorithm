/*
You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given pairs any number of times.

Return the lexicographically smallest string that s can be changed to after using the swaps.

 

Example 1:

Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"
Example 2:

Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"
Example 3:

Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination: 
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"
 

Constraints:

1 <= s.length <= 10^5
0 <= pairs.length <= 10^5
0 <= pairs[i][0], pairs[i][1] < s.length
s only contains lower case English letters.
*/

// the key insight is that all indexes that can swap formulate a graph components. 
// Therefore, we need to find all components, and for each component having a set of chars and indices, put the smallest char to its smallest indice and so on. 
// After completing this for all components, we can get the smallest lexicographically string

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vector<int>> graph(n);
        vector<vector<int>> components(n);
        set<int> visited;

        for ( auto e : pairs )
        {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        for ( int i = 0; i < n; i++ )
        {
            if ( !visited.count(i) )
            {
                vector<int> new_component;
                dfs(graph,i,visited,new_component);
                components.push_back(new_component);
            }
        }

        for ( auto c : components )
        {
            vector<char> chars; 
            for ( auto idx : c )
                chars.push_back(s[idx]);
            sort(chars.begin(),chars.end());
            sort(c.begin(),c.end());
            for ( int i = 0; i < c.size(); i++ )
                s[c[i]] = chars[i];
        }

        return s;
    }

private:
    void dfs(const vector<vector<int>> &graph, int s, set<int>& visited, vector<int>& res)
    {
        res.push_back(s);
        visited.insert(s);
        for ( auto n : graph[s] )
        {
            if ( !visited.count(n) )
                dfs(graph,n,visited,res);
        }
    }
};



class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for ( int i = 0; i < n; i++ )
            parent[i] = i;
    }

    void Union(int x, int y)
    {
        int p_x = Find(x), p_y = Find(y);
        if ( p_x != p_y )
        {
            if ( rank[p_x] > rank[p_y] )
            {
                parent[p_y] = p_x;
            }
            else if ( rank[p_x] < rank[p_y] )
            {
                parent[p_y] = p_x;
            }
            else {
                rank[p_x]++;
                parent[p_y] = p_x;
            }
        }
    }

    int Find(int x)
    {
        if ( parent[x] != x )
        {
            parent[x] = Find(parent[x]);
        }

        return parent[x];
    }
};

// of course we could use Union find to find the components instead of BFS/DFS
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size(); 
        if ( n == 0 )
            return s;
        unordered_map<int,vector<int>> components;
        UnionFind uf(n);
        for (auto& e : pairs)
        {
            uf.Union(e[0],e[1]);
        }

        for ( int i = 0; i < n; i++ )
        {
            components[uf.Find(i)].push_back(i);
        }

        for ( auto& c : components )
        {
            vector<char> chars;
            for ( auto idx : c.second )
                chars.push_back(s[idx]);
            sort(chars.begin(),chars.end());
            for ( int i = 0; i < chars.size(); i++ )
            {
                s[c.second[i]] = chars[i];
            }
        }

        return s;
    }
};