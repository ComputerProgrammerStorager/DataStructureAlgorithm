/*
Given a non-decreasing array of positive integers nums and an integer k, find out if this array can be divided into one or more disjoint increasing subsequences of length at least k.

 

Example 1:

Input: nums = [1,2,2,3,3,4,4], k = 3
Output: true
Explanation: 
The array can be divided into the two subsequences [1,2,3,4] and [2,3,4] with lengths at least 3 each.
Example 2:

Input: nums = [5,6,6,7,8], k = 3
Output: false
Explanation: 
There is no way to divide the array using the conditions required.
 

Note:

1 <= nums.length <= 105
1 <= k <= nums.length
1 <= nums[i] <= 105

*/

// the minimum number of sequence is determined by the maximum frequence of the same number 
// once we know the max_freq, then if the total numbers is larger or equal to the k*max_freq 
// then this could be divided to max_freq groups with each being at least k size
class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        int len = nums.size(), max_freq = 0;
        for (int s = 0; s < len; )
        {
            int cur_freq = 1;
            int e = s + 1;
            while ( e < len && nums[e] == nums[s] )
            {
                cur_freq++;
                e++;
            }
            max_freq = max(max_freq,cur_freq);
            s += cur_freq;
        }
        
        return len >= max_freq * k;
    }
};