/*
Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
*/

// Assume the array has n numbers, then the first missing positive must be the smallest in [1,n+1] that doesn't exist in the array 
// then we can check the possible numbers from the smallest 
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        set<int> st(nums.begin(),nums.end());
        for ( int i = 1; i <= n+1; i++ )
            if ( st.count(i) == 0 )
                return i;
        return -1;
    }
};

// the biggest missing number is n+1, which happens when the array contains [1,n].
// duplicates doesn't impact the results, therefore, we can assign all value less than zero or bigger than n to a duplicate value. 
// we choose 1, as it's easier. but we need to first check if 1 exists in the array or not. If not, then 1 is the result. 
// After this processing, then we have all the numbers in the array are positive, thus we can use sign (negativity) to check the existence of a number
// while using the value as index to array. then is a cell has positive value then, it's is the answer 
// Note we use nums[0] to denote the existence of n 
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int has_one = false, n = nums.size();
        for ( auto num : nums )
            if ( num == 1 )
            {
                has_one = true;
                break;
            }
        if ( !has_one )
            return 1;
        for ( auto &num : nums )
        {
            if ( num <= 0 || num > n )
                num = 1;
        }

        for ( int i = 0; i < n; i++ )
        {
            int val = abs(nums[i]);
            if ( val == n )
                nums[0] = -abs(nums[0]);
            else 
                nums[val] = -abs(nums[val]);
        }

        for ( int i = 1; i < n; i++ )
            if ( nums[i] > 0 )
                return i;
        if ( nums[0] > 0 )
            return n;
        return n+1;
    }
}; 
