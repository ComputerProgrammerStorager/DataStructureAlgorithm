/*
You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].

Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.

 

Example 1:

Input: nums = [1,2,0,3,0], k = 1
Output: 3
Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
Example 2:

Input: nums = [3,4,5,2,1,7,3,4,7], k = 3
Output: 3
Explanation: Modify the array from [3,4,5,2,1,7,3,4,7] to [3,4,7,3,4,7,3,4,7].
Example 3:

Input: nums = [1,2,4,1,2,5,1,2,6], k = 3
Output: 3
Explanation: Modify the array from [1,2,4,1,2,5,1,2,6] to [1,2,3,1,2,3,1,2,3].
 

Constraints:

1 <= k <= nums.length <= 2000
​​​​​​0 <= nums[i] < 210
*/

#include "../Common/common_api.h"

class Solution {
    //vector<unordered_map<int,int>> group(2001);       // what are the numbers in each group
    //vector<unordered_set<int>> group_num(2001);   // the unique number of each group
    //vector<int> total_group_count(2001);
    int group[2001][1024];
    unordered_set<int> group_num[2001];
    int total_group_count[2001];
    //vector<vector<int>> dp(k,vector<int>(1024,0));      // the minimum changes when the xor sum up till the kth number equals to d 
    int dp[2001][1024];
public:
    int minChanges(vector<int>& nums, int k) {
        
        for ( int g = 0; g < k; g++ )
        {
            for ( int p = g; p < nums.size(); p += k )
            {
                group[g][nums[p]]++;
                group_num[g].insert(nums[p]);
                total_group_count[g]++;
            }
        }
        
        for ( int d = 0; d < 1024; d++ )
        {
            dp[0][d] = findgroupchange(0,d);
        }
        
        // fill up the dp array 
        for ( int g = 1; g < k; g++ )
        {
            for ( int d = 0; d < 1024; d++ )
            {
                int min_changes = INT_MAX;
                for ( int prev_d = 0; prev_d < 1024; prev_d++ )
                {
                    // start from prev_d for the k-1 group and arrive at d for the k group,some the current number of k group should be prev_d xor d
                    int cur_changes = findgroupchange(g,d^prev_d);
                    min_changes = min(min_changes,dp[k-1][prev_d]+cur_changes);
                }
                dp[g][d] = min_changes;
            }
        }
        
        return dp[k-1][0];
    }
    
    // the changeds need to make group @g to be all value d
    int findgroupchange(int g, int d)
    {
        // populate dp[g][***]: group g
        if (group_num[g].count(d)) 
        {
            dp[g][d] = total_group_count[g] - group[g][d];
        }
        else 
        {
            dp[g][d] = total_group_count[g];
        }
        return dp[g][d];
    }
    Solution(){
        memset(group,0,sizeof(group));
        memset(dp,0,sizeof(dp));
        memset(total_group_count,0,sizeof(total_group_count));
    }
};

#if 0
int main()
{
    Solution s;
    vector<int> data = {26,19,19,28,13,14,6,25,28,19,0,15,25,11};
    int k = 3;
    s.minChanges(data,k);
}
#endif 


int group[2001][1024];
unordered_set<int> group_num[2001];
int total_group_count[2001];
int dp[2001][1024];
// the changes need to make group @g to be all value d
int findgroupchange(int g, int d)
{
    // populate dp[g][***]: group g
    if (group_num[g].count(d)) 
    {
        dp[g][d] = total_group_count[g] - group[g][d];
    }
    else 
    {
        dp[g][d] = total_group_count[g];
    }
    return dp[g][d];
}

int main()
{
    vector<int> nums = {26,19,19,28,13,14,6,25,28,19,0,15,25,11};
    int k = 3;
    for ( int g = 0; g < k; g++ )
    {
        for ( int p = g; p < nums.size(); p += k )
        {
            group[g][nums[p]]++;
            group_num[g].insert(nums[p]);
            total_group_count[g]++;
        }
    }
    
    for ( int d = 0; d < 1024; d++ )
    {
        dp[0][d] = findgroupchange(0,d);
    }
    
    // fill up the dp array 
    for ( int g = 1; g < k; g++ )
    {
        for ( int d = 0; d < 1024; d++ )
        {
            int min_changes = INT_MAX;
            for ( int prev_d = 0; prev_d < 1024; prev_d++ )
            {
                // start from prev_d for the k-1 group and arrive at d for the k group,some the current number of k group should be prev_d xor d
                int cur_changes = findgroupchange(g,d^prev_d);
                min_changes = min(min_changes,dp[k-1][prev_d]+cur_changes);
            }
            dp[g][d] = min_changes;
        }
    }
    
    return dp[k-1][0];

};