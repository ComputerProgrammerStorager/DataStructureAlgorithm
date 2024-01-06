/*
There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the m x n maze, the ball's start position and the destination, where start = [startrow, startcol] and destination = [destinationrow, destinationcol], return true if the ball can stop at the destination, otherwise return false.

You may assume that the borders of the maze are all walls (see examples).

 

Example 1:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
Example 2:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
Output: false
Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.
Example 3:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
Output: false
 

Constraints:

m == maze.length
n == maze[i].length
1 <= m, n <= 100
maze[i][j] is 0 or 1.
start.length == 2
destination.length == 2
0 <= startrow, destinationrow <= m
0 <= startcol, destinationcol <= n
Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
The maze contains at least 2 empty spaces.
*/

// DFS 
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        return dfs(maze,start,destination,visited);
    }
    bool dfs(vector<vector<int>>& maze, vector<int> start, vector<int> dest, vector<vector<bool>>& visited) {
        int m = maze.size(), n = maze[0].size();
        int dirs[] = {0,1,0,-1,0};
        if ( visited[start[0]][start[1]] )
            return false;
        if ( start == dest )
            return true;
        visited[start[0]][start[1]] = true;
        for ( int d = 0; d < 4; d++ ) {
            int r = start[0], c = start[1]; 
            while( r >= 0 && r < m && c >= 0 && c < n && maze[r][c] == 0 ) {
                r += dirs[d];
                c += dirs[d+1];
            }
            r -= dirs[d];
            c -= dirs[d+1]; 
            if ( dfs(maze,{r,c},dest,visited) )
                return true;
        }
        return false;
    }
};


// BFS
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        queue<pair<int,int>> q;
        int dirs[] = {0,1,0,-1,0};
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        q.push({start[0],start[1]});
        visited[start[0]][start[1]] = true;
        while(!q.empty()) {
            auto [x,y] = q.front();
            q.pop();
            if ( x == destination[0] && y == destination[1] )
                return true;
            for ( int d = 0; d < 4; d++ ) {
                int r = x, c = y;
                while( r >= 0 && r < m && c >= 0 && c < n && maze[r][c] == 0 ) {
                    r += dirs[d];
                    c += dirs[d+1];
                }
                r -= dirs[d];
                c -= dirs[d+1];
                if ( !visited[r][c] ) {
                    visited[r][c] = true;
                    q.push({r,c});
                }
            }
        }

        return false;
    }
};
