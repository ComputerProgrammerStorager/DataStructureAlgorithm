/*
Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.

We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).

 

Example 1:

Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:

Input: nums = [4,2,1]
Output: false
Explanation: You cannot get a non-decreasing array by modifying at most one element.
 

Constraints:

n == nums.length
1 <= n <= 104
-105 <= nums[i] <= 105
*/

// we want to find the violations. When we encounter the first violation, we want to fix it in a greedy manner 
// in the hope to minimize the future violation, i.e., set it to the minimaml possible value 
// The violation happens at i when nums[i] < nums[i-1]: 
// To fix it, we need to look at nums[i-2] as well. We know nums[i-2] <= nums[i-1] > nums[i] 
// If i == 1, then there is no nums[i-2], then set nums[0] to nums[1] (or any number that is less than nums[1] ) to fix it
//     nums[i-1] = nums[i]
// If i > 1, then there is such a nums[i-2], then we compare nums[i-2] and nums[i] 
//   if nums[i-2] <= nums[i], given nums[i-1] > nums[i], we want to greedily modify nums[i-1] to  nums[i] (any number between [nums[i-2],nums[i]] 
//          we call this a greedy manner, because we could have changed nums[i] to any number larger than or equal to nums[i-1] (remeber nums[i-1] > nums[i]) 
//          but doing this way would increase the likelyhood of future violations 
//  if nums[i-2] > nums[i], then we need to fix nums[i] and set the minimum possible value which is nums[i-1] to reduce the likelyhood of future violations 
//          nums[i] = nums[i-1] 
//  Since we are only allowed one violation and nums[i-1] doesn't matter in determining the second violation (as we are moving forward), we should be able only to code the 
//  case when nums[i] changes. 

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        bool used = false;
        for ( int i = 0; i < nums.size(); i++ ) {
            if ( i > 0 && nums[i] < nums[i-1] ) {
                if ( used )
                    return false;
                used = true;
                if ( i == 1 ) 
                    nums[i-1] = nums[i]; 
                else if ( nums[i-2] > nums[i]) {
                    nums[i] = nums[i-1];
                }
            }
        }
        return true;
    }
};

// only care about nums[i] changes 
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        bool used = false;
        for ( int i = 0; i < nums.size(); i++ ) {
            if ( i > 0 && nums[i] < nums[i-1] ) {
                if ( used )
                    return false;
                used = true;
                if ( i > 1 && nums[i-2] > nums[i]) {
                    nums[i] = nums[i-1];
                }
            }
        }
        return true;
    }
};