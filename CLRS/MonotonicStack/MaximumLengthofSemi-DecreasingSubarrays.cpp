/*
You are given an integer array nums.

Return the length of the longest semi-decreasing subarray of nums, and 0 if there are no such subarrays.

A subarray is a contiguous non-empty sequence of elements within an array.
A non-empty array is semi-decreasing if its first element is strictly greater than its last element.
 

Example 1:

Input: nums = [7,6,5,4,3,2,1,6,10,11]
Output: 8
Explanation: Take the subarray [7,6,5,4,3,2,1,6].
The first element is 7 and the last one is 6 so the condition is met.
Hence, the answer would be the length of the subarray or 8.
It can be shown that there aren't any subarrays with the given condition with a length greater than 8.
Example 2:

Input: nums = [57,55,50,60,61,58,63,59,64,60,63]
Output: 6
Explanation: Take the subarray [61,58,63,59,64,60].
The first element is 61 and the last one is 60 so the condition is met.
Hence, the answer would be the length of the subarray or 6.
It can be shown that there aren't any subarrays with the given condition with a length greater than 6.
Example 3:

Input: nums = [1,2,3,4]
Output: 0
Explanation: Since there are no semi-decreasing subarrays in the given array, the answer is 0.
 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

// consider a subarray ending at i, then the longest semi-decreasing subarray, would be the one whose starting element is the earliest 
// in order to fast find the left boundary, we can use a monotonic stack. 
//  idea is: if we have a larger number in the left, then it will be a better candidate than others which follow it and are smaller than it. 
//  to find the largest then, we can start from the end[j,i], which will be longer than [j',i], when j' < j. therefore we can safely pop the left boundary, i.e., i. 
class Solution {
public:
    int maxSubarrayLength(vector<int>& nums) {
        stack<int> st;
        int res = 0, n = nums.size();
        for ( int i = 0; i < n; i++ ) {
            if ( st.empty() || nums[st.top()] < nums[i] )
                st.push(i);
        }

        for ( int j = n-1; j > 0; j-- ) {
            while(!st.empty() && nums[st.top()] > nums[j] ) {
                res = max(res,j-st.top()+1);
                st.pop();
            }
        }

        return res;
    }
};