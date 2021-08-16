/*
Given a binary array nums, return the maximum number of consecutive 1's in the array if you can flip at most one 0.

 

Example 1:

Input: nums = [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the maximum number of consecutive 1s. After flipping, the maximum number of consecutive 1s is 4.
Example 2:

Input: nums = [1,0,1,1,0,1]
Output: 4
 

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.
 

Follow up: What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

*/

// we maintain a sliding window and whenever we encount more than one zeros we need to move out the first zero 
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size(), s = 0, e = 0;
        bool zero_in_win = false;
        int max_val = 0;
        while ( e < n )
        {
            if ( nums[e] == 0 )
            {
                if ( zero_in_win )
                {
                    while(nums[s++]);
                }
                else 
                {
                   zero_in_win = true;
                }
            }
            max_val = max(max_val, e-s+1);
            e++;
        }
        
        return max(max_val,e-s);
    }
};