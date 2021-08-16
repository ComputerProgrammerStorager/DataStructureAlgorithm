/*
You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.

For example, if nums = [6,1,7,4,1]:

Choosing to remove index 1 results in nums = [6,7,4,1].
Choosing to remove index 2 results in nums = [6,1,4,1].
Choosing to remove index 4 results in nums = [6,1,7,4].
An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.

Return the number of indices that you could choose such that after the removal, nums is fair.

 

Example 1:

Input: nums = [2,1,6,4]
Output: 1
Explanation:
Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
There is 1 index that you can remove to make nums fair.
Example 2:

Input: nums = [1,1,1]
Output: 3
Explanation: You can remove any index and the remaining array is fair.
Example 3:

Input: nums = [1,2,3]
Output: 0
Explanation: You cannot make a fair array after removing any index.
*/

#include "../Common/common_api.h"

class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size(), ways = 0;
        if ( n == 0 )
            return 0;
        vector<vector<int>> left_sum(2,vector<int>(n,0));
        vector<vector<int>> right_sum(2,vector<int>(n,0));
        left_sum[0][0] = nums[0];
        if ( n % 2 )
        {
            right_sum[0][n-1] = nums[n-1];
        }
        else 
        {
            right_sum[1][n-1] = nums[n-1];
        }
        for ( int i = 1; i < n; i++ )
        {
            if ( i % 2 )
            {
                left_sum[0][i] = left_sum[0][i-1];
                left_sum[1][i] = left_sum[1][i-1] + nums[i];
            }
            else 
            {
                left_sum[0][i] = left_sum[0][i-1] + nums[i];
                left_sum[1][i] = left_sum[1][i-1];
            }
            if ( (n-1-i) % 2 )
            {
                right_sum[1][n-1-i] = right_sum[1][n-i] + nums[n-1-i];
                right_sum[0][n-1-i] = right_sum[0][n-i];
            }
            else 
            {
                right_sum[1][n-1-i] = right_sum[1][n-i];
                right_sum[0][n-1-i] = right_sum[0][n-i] + nums[n-1-i];
            }
        }
        
        for ( int i = 0; i < n; i++ )
        {
            if ( i % 2 )
            {
                if ( left_sum[1][i] - nums[i] + right_sum[0][i] == left_sum[0][i] + right_sum[1][i] - nums[i] )
                    ways++;
            }
            else if ( left_sum[0][i] - nums[i] + right_sum[1][i] == left_sum[1][i] + right_sum[0][i] - nums[i] )
            {
                ways++;
            }
        }
        
        return ways;
    }
};

int main()
{
    vector<int> a = {1,2,3};
    Solution s;
    s.waysToMakeFair(a);
}