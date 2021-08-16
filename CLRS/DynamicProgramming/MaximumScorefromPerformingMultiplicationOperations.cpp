/*
You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.

You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:

Choose one integer x from either the start or the end of the array nums.
Add multipliers[i] * x to your score.
Remove x from the array nums.
Return the maximum score after performing m operations.

 

Example 1:

Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.
Example 2:

Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
Output: 102
Explanation: An optimal solution is as follows:
- Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
- Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
- Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
- Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
- Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
The total score is 50 + 15 - 9 + 4 + 42 = 102.
 

Constraints:

n == nums.length
m == multipliers.length
1 <= m <= 103
m <= n <= 105
-1000 <= nums[i], multipliers[i] <= 1000
*/

#include "../Common/common_api.h"

// This is a classic DP problem, where dp[i][j] denotes the results of having i numbers from the left end and j numbers from the right end.
// therefore dp[i][j] could arrive from picking the nums[i-1] from the left or picking nums[n-j] from the right side for the (i+j)th step
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size(), m = multipliers.size();
        auto dp = vector<vector<int>>(m+1,vector<int>(m+1));
        int res = INT_MIN;
        dp[0][0] = 0;
        for ( int r = 1; r <= m; r++)
        {
            dp[r][0] = dp[r-1][0] + nums[r-1]*multipliers[r-1];    
        }
        
        for ( int c = 1; c <= m; c++ )
        {
            dp[0][c] = dp[0][c-1] + nums[n-c]*multipliers[c-1];
        }
        
        for ( int len = 2; len <= m; len++ )
        {
            for ( int r = 0; r < len; r++ )
            {
                int c = len - r;
                if ( r != 0 && c != 0 )
                {
                    dp[r][c] = max(dp[r-1][c]+nums[r-1]*multipliers[r+c-1],dp[r][c-1] + nums[n-c]*multipliers[r+c-1]);
                }
                if ( r+c == m )
                {
                    res = max(res,dp[r][c]);
                }
            }
        }
        
        return res;
    }
};

int main()
{
    vector<int> nums = {1,2,3};
    vector<int> multipliers = {3,2,1};
    Solution s;
    s.maximumScore(nums,multipliers);
}