/*
You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.

The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.

Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.

 

Example 1:


Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation:
The above figure shows the positions and ranges of the 2 bombs.
If we detonate the left bomb, the right bomb will not be affected.
But if we detonate the right bomb, both bombs will be detonated.
So the maximum bombs that can be detonated is max(1, 2) = 2.
Example 2:


Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation:
Detonating either bomb will not detonate the other bomb, so the maximum number of bombs that can be detonated is 1.
Example 3:


Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation:
The best bomb to detonate is bomb 0 because:
- Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
- Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
- Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
Thus all 5 bombs are detonated.
 

Constraints:

1 <= bombs.length <= 100
bombs[i].length == 3
1 <= xi, yi, ri <= 105
*/

// The relationship between the distance and the range of a bomb defines a graph relationship. 
// When a bomb is detonated, that those which are within the range of that bomb will also be detonated, 
// then in a cascading manner untill no bomb can be detonated. This exactly is a graph traversal problem 
// So to find the best choice, we explore each bomb as the starting node and calculate how many bombs can be detonated. 

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int mx = 1, n = bombs.size();
        vector<vector<int>> neighbors(100,vector<int>());
        for ( int i = 0; i < n; i++ )
        {
            for ( int l = i-1; l >= 0; l-- )
                if ( distancesquared({bombs[i][0],bombs[i][1]},{bombs[l][0],bombs[l][1]}) <= pow(bombs[i][2],2) ) 
                    neighbors[i].push_back(l);
            for ( int r = i+1; r < n; r++ )
                if ( distancesquared({bombs[i][0],bombs[i][1]},{bombs[r][0],bombs[r][1]}) <= pow(bombs[i][2],2) )
                    neighbors[i].push_back(r);
        }
        
        for ( int i = 0; i < n; i++ )
        {
            int explodes = 0;
            vector<bool> visited(n,false);
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while(!q.empty())
            {
                int q_sz = q.size(); 
                explodes += q_sz;
                for ( int j = 0; j < q_sz; j++ )
                {
                    int cur = q.front();
                    q.pop();
                    for ( auto next : neighbors[cur] )
                        if ( !visited[next] )
                        {
                            q.push(next);
                            visited[next] = true;
                        }
                }
            }
            mx = max(mx,explodes);
        }
        
        return mx;
    }
    
private:
    double distancesquared(pair<int,int> const& a, pair<int,int> const& b)
    {
        return pow(a.first-b.first,2) + pow(a.second-b.second,2);
    }
};

// use DFS 
class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int res = 0, n = bombs.size();
        if ( n < 2 )
            return n;
        vector<vector<int>> graph(n);
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < n; j++ )
            {
                if ( i == j )
                    continue;
                if ( withindistance({bombs[i][0],bombs[i][1]},{bombs[j][0],bombs[j][1]},bombs[i][2]) )
                    graph[i].push_back(j);
            }
        for ( int i = 0; i < n; i++ )
        {
            set<int> visited;
            res = max(res,dfs(i,visited,graph));
        }
        
        return res;
    }
private:
    bool withindistance(const pair<int,int>& center, const pair<int,int>& point, int r )
    {
        return power(center.first-point.first,2) + power(center.second-point.second,2) <= power(r,2);
    }
    int dfs(int start, set<int>& visited, const vector<vector<int>>& graph)
    {
        int res = 1;
        visited.insert(start);
        for ( auto nei : graph[start] )
            if ( !visited.count(nei) ) 
            {
                res += dfs(nei,visited,graph);
            }

        return res;
    }
};