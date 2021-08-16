/*
You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.

In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.

Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.

 

Example 1:

Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
- Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
- Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
- Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
Example 2:

Input: nums1 = [1,1,1,1,1,1,1], nums2 = [6]
Output: -1
Explanation: There is no way to decrease the sum of nums1 or to increase the sum of nums2 to make them equal.
Example 3:

Input: nums1 = [6,6], nums2 = [1]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed. 
- Change nums1[0] to 2. nums1 = [2,6], nums2 = [1].
- Change nums1[1] to 2. nums1 = [2,2], nums2 = [1].
- Change nums2[0] to 4. nums1 = [2,2], nums2 = [4].
*/

// The idea is for each step we could either increase or decrease with the maximum possible amount in order to approach the target 
// Therefore, we sort the two arrays and select one if there is still a diff

class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(),nums1.end(),0);
        int sum2 = accumulate(nums2.begin(),nums2.end(),0);
        if ( sum1 < sum2 )
            return minOperations(nums2,nums1);
        int steps = 0;
        int dec_idx = nums1.size()-1, inc_idx = 0;
        int diff = sum1 - sum2;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        while ( diff > 0 )
        {
            if ( dec_idx < 0 && inc_idx == nums2.size() )
                return -1;
            if ( dec_idx < 0 )
            {
                diff -= (6-nums2[inc_idx]);
                inc_idx++;
            }
            else if ( inc_idx == nums2.size() )
            {
                diff -= (nums1[dec_idx] - 1);
                dec_idx--;
            }
            else 
            {
                diff -= max(nums1[dec_idx]-1, 6-nums2[inc_idx]);
                if ( nums1[dec_idx] - 1 > 6 - nums2[inc_idx] )
                {
                    dec_idx--;
                }
                else 
                {
                    inc_idx++;
                }
            }
            steps++;
        }
        
        return steps;
    }
};