/*
You are given an integer array nums. In one operation, you can replace any element in nums with any integer.

nums is considered continuous if both of the following conditions are fulfilled:

All elements in nums are unique.
The difference between the maximum element and the minimum element in nums equals nums.length - 1.
For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.

Return the minimum number of operations to make nums continuous.

 

Example 1:

Input: nums = [4,2,5,3]
Output: 0
Explanation: nums is already continuous.
Example 2:

Input: nums = [1,2,3,5,6]
Output: 1
Explanation: One possible solution is to change the last element to 4.
The resulting array is [1,2,3,5,4], which is continuous.
Example 3:

Input: nums = [1,10,100,1000]
Output: 3
Explanation: One possible solution is to:
- Change the second element to 2.
- Change the third element to 3.
- Change the fourth element to 4.
The resulting array is [1,2,3,4], which is continuous.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109

*/

// Each number could be the smallest number of the end continuous array. So we check each case. 
// In order to facilitate checking, we could sort the array and keep only unique numbers. Then for each 
// start smallest value denoted as x,  we search the largest value (which is x+n-1) and calculate how many unique numbers 
// already existing (j-i+1), then we expect a total of n numbers, so the n-(j-i+1) is the operations needed for this case 
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = max(n-1,0);
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        for ( int i = 0; i < nums.size(); i++ )
        {
            int j = upper_bound(nums.begin()+i,nums.end(),nums[i]+n-1) - nums.begin() - 1;
            ans = min(ans,n-(j-i+1));
        }
        
        return ans;
    }
};

// We can also use sliding window to confine the valid subsequence of sorted array. The left end of the sliding window 
// is the smallested value, while the right end is the largest value of the window with the said left end. 
// The window becomes invalid when the next value is larger than then end value. 
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = n-1;
        if ( n == 0 )
            return 0;
        unordered_set<int> win;
        sort(nums.begin(),nums.end());
        int l = 0, r = 0, end_val = nums[l]+n-1;
        while ( r < n )
        {
            if ( nums[r] > end_val ) 
            {
                win.erase(nums[l++]);
                end_val = nums[l] + n - 1;
            }
            else
            {
                win.insert(nums[r++]);
                ans = min(ans,n-(int)win.size());
            }
        }
        
        return ans;
    }
};