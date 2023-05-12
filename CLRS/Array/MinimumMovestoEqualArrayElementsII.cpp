/*
Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by 1.

Test cases are designed so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
Example 2:

Input: nums = [1,10,2,9]
Output: 16
 

Constraints:

n == nums.length
1 <= nums.length <= 105
-109 <= nums[i] <= 109

*/

// Naive solution: the final number must be one of the existing numbers in order to obtain minimum of moves 
// Check all the possibilities and record the one that uses minimum moves 
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        long ans = LONG_MAX;
        for ( auto final_num : nums )
        {
            long moves = 0;
            for ( auto n : nums )
                moves += abs(final_num-n);
            ans = min(ans,moves);
        }
        
        return ans;
    }
};