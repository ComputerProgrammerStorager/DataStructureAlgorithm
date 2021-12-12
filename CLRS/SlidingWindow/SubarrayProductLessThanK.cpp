/*
Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

 

Example 1:

Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Example 2:

Input: nums = [1,2,3], k = 0
Output: 0
 

Constraints:

1 <= nums.length <= 3 * 104
1 <= nums[i] <= 1000
0 <= k <= 106
*/

// We maintain a sliding window whose product is less than K.
// Then for each expanding element from the right, a. the product could be still less than K or b. become 
// big or equal than K. 
// For case a., this new added element would introduce the number of existing element plus one (i.e., only the new element) qualifying subarrays. 
//              It's equal to the number of elements in the sliding window including the new expanded element, i.e., r-l+1;
// For case b., we need first to shift the left boudary to make the sliding window product become less than K. 

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size(), l = 0, r = 0, res = 0, prod = 1;
        if ( k < 2 )
            return 0;
        while ( r < n )
        {
            prod *= nums[r];
            while( prod >= k )
            {
                prod /= nums[l++];
            }
            res += r-l+1;
            r++;
        }
        
        return res;
    }
};