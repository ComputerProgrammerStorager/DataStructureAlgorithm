/*
Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

 

Example 1:

Input: nums = [1,2,3]
Output: 6
Example 2:

Input: nums = [1,2,3,4]
Output: 24
Example 3:

Input: nums = [-1,-2,-3]
Output: -6
 

Constraints:

3 <= nums.length <= 104
-1000 <= nums[i] <= 1000

*/

// the result is either the product of the three largest nums or the product of the two smallest negative number and the biggest positive num
// So we can sort the numbs first
// O(nlgn), O(lgn)
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        return max(nums[0]*nums[1]*nums[n-1],nums[n-1]*nums[n-2]*nums[n-3]);
    }
};

// alternatively, based on the above idea we can find the numbers using one pass scan 
// we can image that the interested five positions are like this:
// min1,min2........max3,max2,max1
// and we update the five numbers as we check each number for possible updating 
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX, max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        for ( auto n : nums )
        {
            if ( n <= min1 )
            {
                min2 = min1;
                min1 = n;
            }
            else if  ( n <= min2 )
            {
                min2 = n;
            }

            
            if ( n > max1 )
            {
                max3 = max2;
                max2 = max1;
                max1 = n;
            }
            else if ( n >= max2 )
            {
                max3 = max2;
                max2 = n;
            }
            else if ( n >= max3 )
            {
                max3 = n;
            }
            
        }
        return max(min2*min1*max1,max1*max2*max3);
    }
};