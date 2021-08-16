/*
Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]
Constraint: It's guaranteed that the product of the elements of any prefix or suffix of the array (including the whole array) fits in a 32 bit integer.

Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)
*/

// Using the concept of prefix product and suffix product 

#if 0
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> output(nums.size(),1);
        for ( int i = nums.size()-2; i >= 0; i-- )
        {
            output[i] = output[i+1] * nums[i+1];
        }
        int mul = 1;
        for ( int i = 1; i < nums.size(); i++ )
        {
            mul *= nums[i-1];
            output[i] = output[i] * mul;
        }
        
        return output;
    }
};
#endif 

#include "../Common/common_api.h"

int main()
{
    int8_t x1 = 5, x2 = -5;
    printf("x1 = %d(%x), x2 = %d(%x)\n",x1,x1,x2,x2);
}
