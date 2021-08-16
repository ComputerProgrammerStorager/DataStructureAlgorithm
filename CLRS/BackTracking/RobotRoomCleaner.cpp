/*
You are controlling a robot that is located somewhere in a room. The room is modeled as an m x n binary grid where 0 represents a wall and 1 represents an empty slot.

The robot starts at an unknown location in the root that is guaranteed to be empty, and you do not have access to the grid, but you can move the robot using the given API Robot.

You are tasked to use the robot to clean the entire room (i.e., clean every empty cell in the room). The robot with the four given APIs can move forward, turn left, or turn right. Each turn is 90 degrees.

When the robot tries to move into a wall cell, its bumper sensor detects the obstacle, and it stays on the current cell.

Design an algorithm to clean the entire room using the following APIs:

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
Note that the initial direction of the robot will be facing up. You can assume all four edges of the grid are all surrounded by a wall.

 

Custom testing:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the four mentioned APIs without knowing the room layout and the initial robot's position.

 

Example 1:


Input: room = [[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,0,0,0,0],[1,1,1,1,1,1,1,1]], row = 1, col = 3
Output: Robot cleaned all rooms.
Explanation: All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
Example 2:

Input: room = [[1]], row = 0, col = 0
Output: Robot cleaned all rooms.
 

Constraints:

m == room.length
n == room[i].length
1 <= m <= 100
1 <= n <= 200
room[i][j] is either 0 or 1.
0 <= row < m
room[row][col] == 1
All the empty cells can be visited from the starting position.

*/

// Idea: this is essentially a dfs + backtracking problem
// The key point is to define a sweeping order which is consistent and comprehensive, meaning it can cover all paths.
// we can envision that the robot at any cell position moves clockwise and it tries to move into every four direction 
// in a clockwise manner. Suppose the robot is at position X {x_i,x_j} and explores position Y {y_i,y_j}. 
// Upon entering a new neighbour, we need to answer two questions: 
// 1. From which direction to continue sweeping ? 
//    We can start at any direction to sweep as long as all four directions will be covered. But choosing to start from the 
//    same direction which it enters upon from previous position would simplify the backtracking, i.e., it doesn't change the 
//    direction after entering a neighbour. 
//    
// 2. If we have checked all the four directions of the new poistion, how we can backtrack to previous position to continue 
//    checking other directions which had not been checked before it entered the currect new position ? 
//    One thing to observe is that given any position, after the robot finishes checking all four directions, it will return 
//    to the same orientation. So in order to ga back to its previous position, we should change the direction 180 degrees
//    i.e., two turnRight, and make a move to the previous position. However, after the move back operation, it has the opposite 
//    orientation, so need to change 180 degree again to make it back to the same position and the same orientation so as to continue
//    exploring the remaining directions which were left. 

class Solution {
    vector<pair<int,int>> dirs;
    set<pair<int,int>> visited;
private:
    void go_back(Robot& robot)
    {
        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnRight();
        robot.turnRight();
    }
public:
    void cleanRoom(Robot& robot) {
        // 0 "up", 1 "right", 2 "down", 3 "left"
        dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        dfs(robot,0,0,0);
    }

    void dfs(Robot& robot, int cur_x, int cur_y, int dir)
    {
        robot.clean();
        visited.insert({cur_x,cur_y});
        for ( int i = 0; i < 4; i++ )
        {
            int next_x = cur_x + dirs[dir].first;
            int next_y = cur_y + dirs[dir].second;
            if (!visited.count({next_x,next_y}) && robot.move() )
            {
                dfs(robot,next_x,next_y,dir);
                go_back(robot);
            }
            dir = (dir+1) % 4;
            robot.turnRight();
        }
    }
};