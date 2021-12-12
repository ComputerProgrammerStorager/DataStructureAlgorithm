/*
Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.

 

Example 1:


Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
We have two small ponds 1 and 3 units trapped.
The total volume of water trapped is 4.
Example 2:


Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
Output: 10
 

Constraints:

m == heightMap.length
n == heightMap[i].length
1 <= m, n <= 200
0 <= heightMap[i][j] <= 2 * 104
*/

// idea:
// Image the heightMap is a castle and the flood is coming. So the water will first enter to the shortest height at the very outsid and then will 
// form a new circumference around the castle with some outside edges replaced by the unvisited neighbors of the shortest position. 
// then for each of the neighbors, it can trap some water if its height is less than the current min height of the circumference whose min value is the 
// shortest of the outmost heights. 
// So the procedure should be as following:
// 1. initialize a priority queue with all outmost heights. Then top of the current priority queue should be the min height ever during the bfs process 
// 2. use bfs to check unvisisted neighbors of the shortest one and calculate the trapped water if the neighbor's heights is less than the current min height
// 3. pop the priority queue to check each and every position and update the min_h if the new shortest height is higher than min_h because some islands might be 
//    at a higher position and  could trap more water. 

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size(), res = 0, min_h = INT_MIN;
        priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        pair<int,int> dirs[4] = {{-1,0},{1,0},{0,1},{0,-1}};
        for ( int i = 0; i < m; i++ )
            for( int j = 0; j < n; j++ )
            {
                if ( i == 0 || i == m -1 || j == 0 || j == n-1 )
                {
                    visited[i][j] = true;
                    pq.push({heightMap[i][j],{i,j}});
                }
            }
        
        while( !pq.empty() )
        {
            auto cur = pq.top();
            pq.pop();
            min_h = max(min_h,cur.first);
            for ( auto d : dirs )
            {
                int x = d.first + cur.second.first;
                int y = d.second + cur.second.second;
                if ( x < 0 || x >= m || y < 0 || y >= n || visited[x][y] )
                    continue;
                if ( heightMap[x][y] < min_h )
                    res += min_h - heightMap[x][y];
                visited[x][y] = true;
                pq.push({heightMap[x][y],{x,y}});
            }
        }
        
        return res;
    }
};