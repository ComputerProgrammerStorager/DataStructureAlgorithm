/*
You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.

Return the number of connected components in the graph.

 

Example 1:


Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2
Example 2:


Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1
 

Constraints:

1 <= n <= 2000
1 <= edges.length <= 5000
edges[i].length == 2
0 <= ai <= bi < n
ai != bi
There are no repeated edges.
*/


// use dfs and bfs to find the number of conneted components 
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adjList;
        vector<bool> visited(n,false);
        int cnt = 0;
        for ( auto& e : edges )
        {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }
        
        for ( int i = 0; i < n; i++ )
        {
            if ( !visited[i] )
            {
                cnt++;
                bfs(visited,adjList,i);
            }
        }
        return cnt;
    }
    
    void dfs(vector<bool>& visited, unordered_map<int,vector<int>>& adjList, int start)
    {
        visited[start] = true;
        for ( int next : adjList[start] )
            if ( !visited[next] )
                dfs(visited,adjList,next);
    }
    
    void bfs(vector<bool>& visited, unordered_map<int,vector<int>> &adjList, int start)
    {
        visited[start] = true;
        queue<int> q;
        q.push(start);
        while( !q.empty() )
        {
            int cur = q.front();
            q.pop();
            for ( auto next : adjList[cur] )
                if ( !visited[next] )
                {
                    visited[next] = true;
                    q.push(next);
                }
        }
    }
};


// use union find 
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n);        // maintain every node's parent
        vector<int> size(n);         // maintain the size of the subtree rooted at index
        for ( int i = 0; i < n; i++ )
        {
            parent[i] = i;
            size[i] = 1;
        }
        
        int components = n;
        for ( auto e : edges )
        {
            components -= union_nodes(parent, size, e[0],e[1]);
        }
        
        return components;
    }
    
    int find_parent(vector<int>& parent, int n)
    {
        if ( parent[n] == n )
            return n;
        return parent[n] = find_parent(parent,parent[n]);       // amazing path compression :-) !! 
    }
    int union_nodes(vector<int>& parent, vector<int>& size, int s, int e)
    {
        int s_parent = find_parent(parent,s);
        int e_parent = find_parent(parent,e);
        if ( s_parent == e_parent )
            return 0;
        if ( size[s_parent] > size[e_parent] )
        {
            size[e_parent] += size[s_parent];
            parent[s_parent] = e_parent;
        }
        else 
        {
            size[s_parent] += size[e_parent];
            parent[e_parent] = s_parent;
        }
        
        return 1;
    }
};