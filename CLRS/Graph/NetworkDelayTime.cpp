/*
You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

 

Example 1:


Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
 

Constraints:

1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
*/

#include "../Common/common_api.h"

// BFS + priority_queue, O(ElgE)
class Solution {
    typedef pair<int,int> wt_node;
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
 
        vector<vector<wt_node>> AdjList(n+1);
        vector<bool> visited(n+1,false);
        int res = 0;
        priority_queue<wt_node,vector<wt_node>, greater<>> pq;
        for ( auto e : times )
        {
            AdjList[e[0]].push_back({e[1],e[2]});
        }
        
        pq.push({0,k});
        while ( !pq.empty() )
        {
            auto [d,node] = pq.top();
             pq.pop();
            if ( visited[node] )
                continue;
            visited[node] = true;
            res = max(res,d);
            for ( auto next : AdjList[node] )
            {
                //if ( !visited[next.first] )
                {
                    pq.push({d+next.second,next.first});
                }    
            }
        }
        
        for ( int i = 1; i <= n; i++ )
            if ( !visited[i] )
                return -1;
        return res;
    }
};

// Tabulation-like traversal 
class Solution {
    typedef pair<int,int> wt_node;
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
 
        vector<vector<wt_node>> AdjList(n+1);
        vector<bool> visited(n+1,false);
        vector<int> dist(n+1,INT_MAX);
        int res = 0;

        for ( auto e : times )
        {
            AdjList[e[0]].push_back({e[1],e[2]});
        }
        
        dist[k] = 0;
        
        for ( int i = 1; i <= n; i++ )
        {
            int minDist = INT_MAX, min_idx = -1;
            for ( int j = 1; j <= n; j++ )
            {
                if ( !visited[j] && dist[j] < minDist )
                {
                    minDist = dist[j];
                    min_idx = j;
                }
            }
            if ( min_idx == -1 )
                break;
            visited[min_idx] = 1;
            for ( auto next : AdjList[min_idx] )
            {
                //if ( !visited[next.first] )
                    dist[next.first] = min(dist[next.first],dist[min_idx] + next.second);
            }
        }
        
        for ( int i = 1; i <= n; i++ )
            res = max(res,dist[i]);
        return res == INT_MAX ? -1 : res;
    }
};

// Floyd algorithm 
class Solution {
    typedef pair<int,int> wt_node;
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        auto dp = vector<vector<int>>(n+1,vector<int>(n+1,INT_MAX/2));
        // dp[i][j]: shortest path between i and j 
        for ( auto e : times )
            dp[e[0]][e[1]] = e[2];
        for ( int i = 1; i <= n; i++ )
            dp[i][i] = 0;
        
        for ( int k = 1; k <= n; k++ )
        {
            for ( int i = 1; i <= n; i++ )
                for ( int j = 1; j <= n; j++ )
                    dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j]);
        }
        
        int res = 0;
        for ( int i = 1; i <= n; i++ )
            res = max(dp[k][i],res);
        return res == INT_MAX/2 ? -1 : res;
    }
};

int main()
{
    vector<vector<int>> times = {{1,2,1},{2,1,3}};
    Solution s;
    s.networkDelayTime(times,2,2);
}