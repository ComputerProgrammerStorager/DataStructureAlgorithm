/*
There are some stones in different positions on the X-axis. You are given an integer array stones, the positions of the stones.

Call a stone an endpoint stone if it has the smallest or largest position. In one move, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.

In particular, if the stones are at say, stones = [1,2,5], you cannot move the endpoint stone at position 5, since moving it to any position (such as 0, or 3) will still keep that stone as an endpoint stone.
The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).

Return an integer array answer of length 2 where:

answer[0] is the minimum number of moves you can play, and
answer[1] is the maximum number of moves you can play.
 

Example 1:

Input: stones = [7,4,9]
Output: [1,2]
Explanation: We can move 4 -> 8 for one move to finish the game.
Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
Example 2:

Input: stones = [6,5,4,3,10]
Output: [2,3]
Explanation: We can move 3 -> 8 then 10 -> 7 to finish the game.
Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
 

Constraints:

3 <= stones.length <= 104
1 <= stones[i] <= 109
All the values of stones are unique.

*/

// Maximum:
// There are only two cases, i.e., choose the leftmost or rightmost first. Once this first step has been decided, then we can move either new leftmost 
// or rightmost to it's any of the unoccupied position to consunme all avaliable spaces, leading to maximal moves. Therefore, the number of avaliable spaces 
// is the maximum of moves plus the first step. 

// Minimum:
// From the eventual result perspective, every position could be the left end of the final consecutive result. 
// We need to maintain the window size as well as how many stones falling within the current window. 
// Once the winsize becomes bigger than we need, we need to shrink the window, because we only need n consecutive spaces
// Special treatment for consecutive (n-1) subsequence. 
// In this case, if the last one is only one space apart for the bulk, then it requires only one move: 
//   abc.y   ----> bcay
// if the last one is two or more spaces apart from the bulk, then it requires two moves: ( because we could not move y per the definition)
///  abc..y  ----> bc.ay  --- > bcya... 
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size(); 
        int l = 0, r = 0, min_val = INT_MAX, max_val, win_size = 0;
        sort(stones.begin(),stones.end());
        // sliding window to find the minimal moves considering each position as the 
        // starting position of the eventually continuous result 
        while (r < n)
        {
            int win_size = stones[r]-stones[l]+1;
            int stone_cnt =  r-l+1;
            if (win_size > n )
            {
                l++;
                continue;
            }
            
            if ( win_size == n - 1 && stone_cnt == n - 1)
            {
                min_val = min(min_val, stones[n-1] - stones[r] == 1 ? 1 : 2 );
            }
            else 
            {
                min_val = min(min_val, n-stone_cnt);
            }
            r++;
        }
        
        // calculate maximum
        max_val = max(stones[n-1]-stones[1]+1-n,stones[n-2]-stones[0]+1-n)+1;
        return {min_val,max_val};
    }
};