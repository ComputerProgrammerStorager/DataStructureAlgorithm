/*
Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.

Follow up: Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

 

Example 1:

Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.
Example 2:

Input: nums = [-1,0]
Output: [-1,0]
Example 3:

Input: nums = [0,1]
Output: [1,0]
 

Constraints:

2 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each integer in nums will appear twice, only two integers will appear once.
*/

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int,int> m;
        vector<int> res;
        for ( auto num : nums )
            m[num]++;
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            if ( it->second == 1 )
                res.push_back(it->first);
        }
        
        return res;
    }
};

// xor_sum is the xor of the two difference numbers in which each one bit represents a different position
// for convenience, we select the right most set bit of the xor sum by using the quick equation x & -x 
// then we use this one-bit-set mask to divide the duplicate nums into two groups, as the duplicates which have or have not the bit 
// set would go the two groups respectively.
// Note: use long to avoid -INT_MIN overflowing
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        long xor_sum = accumulate(nums.begin(),nums.end(),0,bit_xor<int>());
        long least_diff_bit = (xor_sum & -xor_sum);
        vector<int> res(2,0);
        for ( auto num : nums )
        {
            if ( num & least_diff_bit )
                res[0] ^= num;
            else
                res[1] ^= num;
        }
        
        return res;
    }
};


// same idea, but we use xor to calculate the other number
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int bitmask = 0;
        for ( auto num : nums )
            bitmask ^= num;
        int rightmost_bit = bitmask & (-bitmask);
        int x = 0;
        for ( auto num : nums )
            if ( num & rightmost_bit )
                x ^= num;
        return {x,bitmask^x};
    }
};