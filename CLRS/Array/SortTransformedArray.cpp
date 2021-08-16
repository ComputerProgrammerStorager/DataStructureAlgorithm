/*
Given a sorted integer array nums and three integers a, b and c, apply a quadratic function of the form f(x) = ax2 + bx + c to each element nums[i] in the array, and return the array in a sorted order.

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]
Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]
 

Constraints:

1 <= nums.length <= 200
-100 <= nums[i], a, b, c <= 100
nums is sorted in ascending order.
 

Follow up: Could you solve it in O(n) time?
*/

// Find the center line of the parabola and expand using two pointers
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> res;
        if ( a == 0 )
        {
            if ( b > 0 )
            {
                for ( auto n : nums )
                    res.push_back(b*n + c);
            }
            else 
            {
                for ( auto n : nums )
                    res.insert(res.begin(),b*n+c);
            }
            return res;
        }
        
        double center = (double)(-b) / (2*a);
        int left = -1, right = 0, n = nums.size();
        
        while ( right < n && nums[right] < center )
            right++;
        if ( right > 0 )
            left = right - 1;
        while ( left >= 0 && right < n )
        {
            if ( abs(nums[left] - center)  < abs(nums[right] - center) ) 
            {
                int val = a*pow(nums[left],2) + b * nums[left] + c;
                if ( a > 0 )
                    res.push_back( val );
                else
                    res.insert(res.begin(),val);
                left--;
            }
            else
            {
                int val = a * pow(nums[right],2) + b * nums[right] + c;
                if ( a > 0 )
                    res.push_back(val);
                else
                    res.insert(res.begin(),val);
                right++;
            }
        }
        while ( left >= 0 )
        {
            int val = a*pow(nums[left],2) + b * nums[left] + c;
            if ( a > 0 )
                res.push_back( val );
            else
                res.insert(res.begin(),val);
            left--;
        }
        while ( right < n )
        {
            int val = a * pow(nums[right],2) + b * nums[right] + c;
            if ( a > 0 )
                res.push_back(val);
            else
                res.insert(res.begin(),val);
            right++;
        }
        
        return res;
    }
};