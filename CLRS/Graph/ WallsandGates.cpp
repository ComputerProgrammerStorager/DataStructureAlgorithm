/*
You are given an m x n grid rooms initialized with these three possible values.

-1 A wall or an obstacle.
0 A gate.
INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

 

Example 1:


Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
Example 2:

Input: rooms = [[-1]]
Output: [[-1]]
Example 3:

Input: rooms = [[2147483647]]
Output: [[2147483647]]
Example 4:

Input: rooms = [[0]]
Output: [[0]]
 

Constraints:

m == rooms.length
n == rooms[i].length
1 <= m, n <= 250
rooms[i][j] is -1, 0, or 231 - 1.

*/

//Idea: BFS searching starting from all empty gates 
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        pair<int,int> dirs[4] = {{-1,0},{1,0},{0,-1},{0,1}};
        queue<pair<int,int>> gates;
        int dist = 0;
        int m = rooms.size(), n = rooms[0].size();
        
        for (int i = 0; i < m; i++ )
            for (int j = 0; j < n; j++ )
            {
                if (rooms[i][j] == 0)
                    gates.push({i,j});
            }
        
        while (!gates.empty())
        {
            int cur_sz = gates.size();
            dist++;
            for (int i = 0; i < cur_sz; i++)
            {
                auto cur = gates.front();
                gates.pop();
                for (int i = 0; i < 4; i++)
                {
                    int next_r = cur.first + dirs[i].first;
                    int next_c = cur.second + dirs[i].second;
                    if (next_r < 0 || next_r >= m ||next_c < 0 ||next_c >= n || rooms[next_r][next_c] != INT_MAX )
                        continue;
                    rooms[next_r][next_c] = dist;
                    gates.push({next_r,next_c});
                }
            }
        }
    }
};