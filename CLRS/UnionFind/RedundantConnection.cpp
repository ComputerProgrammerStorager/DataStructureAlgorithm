/*
In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.

 

Example 1:


Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
Example 2:


Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
 

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.
*/


// Use union_find 
class Solution {
    constexpr static int NUM_NODES = 10001;
    class union_find {
    public:
        int Parent[NUM_NODES];
        union_find() {
            for ( int i = 0; i < NUM_NODES; i++ )
                Parent[i] = -1;
        }
    };
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        union_find uf;
        for ( auto e : edges )
        {
            int r1 = find_root(uf,e[0]);
            int r2 = find_root(uf,e[1]);
            if ( r1 == r2 )
            {
                return e;
            }
            else 
            {    
                union_nodes(uf,r1,r2);
            }
        }
        return {};
    }
    
    int find_root( union_find &uf, int node )
    {
        while ( uf.Parent[node] > 0 )
        {
            node = uf.Parent[node];
        }
        
        return node;
    }
    
    void union_nodes( union_find &uf, int source_root, int target_root) 
    {
        if ( uf.Parent[source_root] > uf.Parent[target_root] )
        {
            uf.Parent[target_root] += uf.Parent[source_root];
            uf.Parent[source_root] = target_root;
        }
        else
        {
            uf.Parent[source_root] += uf.Parent[target_root];
            uf.Parent[target_root] = source_root;
        }
    }
};

// basically use dfs or bfs to check if an edge can already be reached. If so, it means adding it would cause a cycle 
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> graph;
        unordered_set<int> seen;
        for ( auto e : edges )
        {
            if ( dfs(e[0],e[1],graph,seen) )
                return e;
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
            seen.clear();
        }

        return {};
    }

    bool dfs(int s, int t, unordered_map<int,vector<int>> &graph, unordered_set<int> &seen)
    {
        if ( seen.count(s) == 0 )
        {
            seen.insert(s);
            if ( s == t ) 
                return true;
            for ( auto nei : graph[s] )
                if ( dfs(nei,t,graph,seen) )
                    return true;
        }

        return false;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> graph;
        for ( auto e : edges )
        {
            if ( bfs(e[0],e[1],graph) ) 
                return e;
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        return {};
    }

    bool bfs( int s, int t, unordered_map<int,vector<int>> &graph)
    {
        if ( s == t )
            return true;
        queue<int> q;
        unordered_set<int> visited;
        for ( auto nei : graph[s] )
            q.push(nei);
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            visited.insert(cur);
            if ( cur == t )
                return true;
            for ( auto nei : graph[cur] )
            {
                if ( visited.count(nei) == 0 )
                    q.push(nei);
            }
        }

        return false;
    }
};

// maintain one and only one component
class UnionFind {
public:
    UnionFind(int max_val) {
        parent.resize(max_val);
        rank.resize(max_val);
        for ( int i = 0; i < max_val; i++ )
            parent[i] = i;
        fill(rank.begin(),rank.end(),0);
    }
    int Find(int x)
    {
        if ( parent[x] != x )
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y)
    {
        int rootx = Find(x), rooty = Find(y);
        if ( rootx != rooty )
        {
            if ( rank[rootx] > rank[rooty] )
                parent[rooty] = rootx;
            else if ( rank[rootx] < rank[rooty] )
                parent[rootx] = rooty;
            else 
            {
                rank[rootx]++;
                parent[rooty] = rootx;
            }
        }
    }
private: 
    vector<int> parent;
    vector<int> rank;
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFind uf(1001);
        for ( auto e : edges )
        {
            if ( uf.Find(e[0]) == uf.Find(e[1]) )
                return e;
            uf.Union(e[0],e[1]);
        }

        return {};
    }
};