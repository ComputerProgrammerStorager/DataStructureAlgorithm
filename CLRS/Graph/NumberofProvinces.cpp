/*

There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]
*/


// BFS or DFS 
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int visited[200] = {0}, cities = 0, n = isConnected.size();
        vector<vector<int>> neighbors(200,vector<int>());
        
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                if ( isConnected[i][j] && i != j )
                    neighbors[i].push_back(j);
            }
        }
        
        for ( int i = 0; i < n; i++ )
        {
            if ( !visited[i] )
            {
                cities++;
                //dfs(i,neighbors,visited);
                bfs(i,neighbors,visited);
            }
        }
        
        return cities;
    }
private:
    void dfs(int s, vector<vector<int>> const& neighbors, int visited[] )
    {
        visited[s] = true;
        for ( auto next : neighbors[s] )
        {
            if ( !visited[next] )
                dfs(next,neighbors,visited);
        }
    }
    
    void bfs(int s, vector<vector<int>> const& neighbors, int visited[])
    {
        queue<int> next;
        visited[s] = true;
        next.push(s);
        while(!next.empty())
        {
            int q_sz = next.size();
            for ( int i = 0; i < q_sz; i++ )
            {
                int cur = next.front();
                next.pop();
                for ( auto n : neighbors[cur] )
                {
                    if ( !visited[n] )
                    {
                        visited[n] = true;
                        next.push(n);
                    }
                }
            }
        }
    }
};

// we could also use union find 
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), cities = n;
        UF uf(n);
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < n; j++ )
            {
                if ( isConnected[i][j] && i != j )
                    uf.union_nodes(i,j);
            }
        
        return uf.get_cnt();
    }

    class UF {
    public:
        UF(int size){
            cap = size;
            data.resize(cap);
            for ( int i = 0; i < cap; i++ )
                data[i] = -1;
        };
        int find_parent(int idx) 
        {
            if ( data[idx] == -1 )
                return idx;
            return find_parent(data[idx]);
        }
        void union_nodes(int s, int e)
        {
            int s_p = find_parent(s);
            int e_p = find_parent(e);
            if ( s_p != e_p )
                data[s_p] = e_p;
        }
        int get_cnt()
        {
            int cnt = 0;
            for ( int i = 0; i < cap; i++ )
                if ( data[i] == -1 )
                    cnt++;
            return cnt;
        }
    private:
        int cap;
        vector<int> data;
    };
};