/*
The diameter of a tree is the number of edges in the longest path in that tree.

There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the tree.

Return the diameter of the tree.

 

Example 1:


Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: The longest path of the tree is the path 1 - 0 - 2.
Example 2:


Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: The longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 

Constraints:

n == edges.length + 1
1 <= n <= 104
0 <= ai, bi < n
ai != bi
*/

// randomly select one and get the furthest and start from the furthest 
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> graph;
        for ( auto e : edges ) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        auto start = bfs(graph,0);
        auto result = bfs(graph,start.first);
        return result.second;
    }

    pair<int,int> bfs(unordered_map<int,vector<int>> graph, int start) {
        queue<int> q; 
        int dist = -1, furthest = -1;
        q.push(start);
        unordered_set<int> visited;
        visited.insert(start);
        while(!q.empty()) {
            for ( int i = q.size(); i > 0; i-- ) {
                auto cur = q.front();
                q.pop();
                furthest = cur;
                for ( auto n : graph[cur] ) {
                    if ( visited.count(n) == 0 ) {
                        visited.insert(n);
                        q.push(n);
                    }
                }
            }
            dist++;
        }
        return {furthest, dist};
    }
};