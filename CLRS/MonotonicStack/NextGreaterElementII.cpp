/*
Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.

The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

 

Example 1:

Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number. 
The second 1's next greater number needs to search circularly, which is also 2.
Example 2:

Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
 

Constraints:

1 <= nums.length <= 104
-109 <= nums[i] <= 109
*/

/* First solution brute force, adding a copy to the end */
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,-1);
        vector<int> tmp2(2*n);
        for ( int i = 0; i < n; i++ )
        {
            tmp2[i] = nums[i];
            tmp2[i+n] = nums[i];
        }

        for ( int i = 0; i < n; i++ )
        {
            for ( int j = i+1; j < tmp2.size(); j++ )
            {
                if ( tmp2[j] > nums[i] )
                {
                    res[i] = tmp2[j];
                    break;
                }
            }
        }

        return res;
    }
};

/* Using circular */
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,-1);
        for ( int i = 0; i < n; i++ )
        {
            for ( int len = 1; len < n; len++ )
            {
                if ( nums[(len+i)%n] > nums[i] )
                {
                    res[i] = nums[(len+i)%n];
                    break;
                }
            }
        }
        return res;
    }
};

// We can use monotonic stack to keep track of the next greate element to the right of an element 
// Note that however, we need two passes 
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> nextidx;
        vector<int> res(n,-1);
        for ( int i = 2*n - 1; i >= 0; i-- )
        {
            while(!nextidx.empty() && nums[nextidx.top()] <= nums[i%n] )
            {
                nextidx.pop();
            }
            if ( !nextidx.empty() )
            {
                res[i%n] = nums[nextidx.top()];
            }
            nextidx.push(i%n);
        }

        return res;
    }
};