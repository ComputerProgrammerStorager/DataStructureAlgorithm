/*
A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

 

Example 1:


Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
Example 2:


Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
 

Constraints:

1 <= n <= 2 * 104
edges.length == n - 1
0 <= ai, bi < n
ai != bi
All the pairs (ai, bi) are distinct.
The given input is guaranteed to be a tree and there will be no repeated edges.
*/


// Find the height of each possible rooted tree and return the minimum height 
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> graph;
        vector<int> res, res2; 
        int minheight = INT_MAX;
        for (auto e : edges ) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        for ( int i = 0; i < n; i++ )
            res.push_back(getminheight(graph,i));
        minheight = *min_element(res.begin(),res.end());
        for ( int i = 0; i < n; i++  ) {
            if ( res[i] == minheight ) {
                res2.push_back(i);
            }
        }

        return res2;
    }

    //
    int getminheight(unordered_map<int,vector<int>>& graph, int start) {
        int dist = -1;
        queue<int> q; 
        unordered_set<int> visited;
        visited.insert(start);
        q.push(start);
        while(!q.empty()) {
            for ( int i = q.size(); i > 0; i-- ) {
                auto cur = q.front();
                q.pop();
                for ( auto n : graph[cur] ) {
                    if ( visited.count(n) == 0 ) {
                        visited.insert(n);
                        q.push(n);
                    }
                }
            }
            dist++;
        }

        return dist;
    }
};

// BFS in a reverse order 
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        unordered_set<int> remaining;
        unordered_map<int, unordered_set<int>> graph;
        queue<int> q;
        vector<int> res;
        for( auto e : edges ) {
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }

        for ( int i = 0; i < n; i++ )
            remaining.insert(i);

        for ( auto it : graph ) {
            if ( it.second.size() == 1 ) {
                q.push(it.first);
            }
        }

        while(remaining.size() > 2 ) {
            for ( int i = q.size(); i > 0; i-- ) {
                auto cur = q.front();
                q.pop();
                remaining.erase(cur);
                for ( auto n : graph[cur] ) {
                        graph[n].erase(cur);
                        if ( graph[n].size() == 1 )
                            q.push(n);
                    }
                }
        }
        for (auto it : remaining )
            res.push_back(it);
        return res;
    }
};