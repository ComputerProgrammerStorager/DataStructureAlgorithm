/*
You are given an integer array nums and an integer goal.

You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).

Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.

 

Example 1:

Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
Example 2:

Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
Example 3:

Input: nums = [1,2,3], goal = -7
Output: 7
 

Constraints:

1 <= nums.length <= 40
-107 <= nums[i] <= 107
-109 <= goal <= 109
*/

#include "../Common/common_api.h"

// We divide the array into two parts and find their respective sums and sort 
// Then search in a similar way to two sum approach 

// void GenerateAllSum( vector<int> const& nums, vector<int> &AllSum)
// {
//     int n = nums.size();
//     for ( int i = 0; i < (1 << n); i++ ) // n is less than 32 
//     {
//         int sum = 0;
//         for ( int pos = 0; pos < n; pos++ )
//         {
//             if ( i & ( 1 << pos ) )
//             {
//                 sum += nums[pos];
//             }
//         }
//         AllSum.push_back(sum);
//     }
// }

// void GenerateAllSum2( vector<int> const& nums, vector<int> &AllSum )
// {
//     AllSum.push_back(0);
//     for ( int i = 0; i < nums.size(); i++ )
//     {
//         int cur_sz = AllSum.size();
//         auto it = AllSum.begin();
//         for ( int j = 0; j < cur_sz; j++ )
//         {
//             AllSum.push_back(*(it+j)+ nums[i]);
//         }
//     }
// }

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        vector<int> first_half_sum{0}, second_half_sum{0};
        int n = nums.size();
        int res = abs(goal);
        if ( n == 0 )
            return abs(goal);
        GenerateSum(0,n/2,nums,first_half_sum);
        GenerateSum(n/2,n,nums,second_half_sum);
        for ( int i = 0, j = second_half_sum.size() - 1; i < first_half_sum.size() && j >= 0; )
        {
            int sum = first_half_sum[i]+second_half_sum[j];
            res = min(abs(sum-goal),res);
            if ( sum > goal )
                j--;
            else if ( sum < goal )
                i++;
            else 
                break;    
        }
        return res;
    }
    
    void GenerateSum( int s, int e, vector<int> const& nums, vector<int> &sum )
    {
        while ( s < e )
        {
            int cur_sz = sum.size();
            for ( int j = 0; j < cur_sz; j++ )
            {
                sum.push_back(sum[j]+nums[s]);
            }
            s++;
        }
        sort(sum.begin(),sum.end());
        sum.erase(unique(sum.begin(),sum.end()),sum.end());
    }
};

int main()
{
    vector<int> b = { -1, 2, 4, 3 };
    vector<int> sum1, sum2;
    GenerateAllSum(b,sum1);
    GenerateAllSum2(b,sum2);
    PrintVector(sum1);
    PrintVector(sum2);
}