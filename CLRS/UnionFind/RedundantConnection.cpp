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