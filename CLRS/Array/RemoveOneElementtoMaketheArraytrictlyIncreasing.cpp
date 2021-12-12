/*
Given a 0-indexed integer array nums, return true if it can be made strictly increasing after removing exactly one element, or false otherwise. If the array is already strictly increasing, return true.

The array nums is strictly increasing if nums[i - 1] < nums[i] for each index (1 <= i < nums.length).

 

Example 1:

Input: nums = [1,2,10,5,7]
Output: true
Explanation: By removing 10 at index 2 from nums, it becomes [1,2,5,7].
[1,2,5,7] is strictly increasing, so return true.
Example 2:

Input: nums = [2,3,1,2]
Output: false
Explanation:
[3,1,2] is the result of removing the element at index 0.
[2,1,2] is the result of removing the element at index 1.
[2,3,2] is the result of removing the element at index 2.
[2,3,1] is the result of removing the element at index 3.
No resulting array is strictly increasing, so return false.
Example 3:

Input: nums = [1,1,1]
Output: false
Explanation: The result of removing any element is [1,1].
[1,1] is not strictly increasing, so return false.
Example 4:

Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is already strictly increasing, so return true.
 

Constraints:

2 <= nums.length <= 1000
1 <= nums[i] <= 1000
*/

// Naive solution: check each possible removal 
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        for ( int i = 0; i < nums.size(); i++ )
            if ( IsStricklyIncreasing(RemoveElement(nums,i)))
                return true;
        return false;
    }
    
    vector<int> RemoveElement(vector<int> const& nums, int idx)
    {
        vector<int> res;
        for ( int i = 0; i < nums.size(); i++ )
        {
            if ( idx != i )
                res.push_back(nums[i]);
        }
        
        return res;
    }
    
    bool IsStricklyIncreasing(vector<int> const& nums)
    {
        int n = nums.size();
        for ( int i = 0; i < n-1; i++ )
        {
            if ( nums[i] >= nums[i+1] )
                return false;
        }
        
        return true;
    }
};

// Try to remove each element and test if it is strictly increasing 
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int n = nums.size(); 
        for ( int i = 0; i < n; i++ )
        {
            vector<int> tmp;
            for ( int j = 0; j < n; j++ )
                if ( j != i )
                    tmp.push_back(nums[j]);
            if ( isStrictlyIncreasing(tmp) )
                return true;
        }
        
        return false;
    }
private:
    bool isStrictlyIncreasing(vector<int> const& nums) 
    {
        int n = nums.size(), i = 1;
        if ( n < 2 )
            return true;
        #if 0 
        for ( int i = 1; i < n; i++ )
            if ( nums[i] <= nums[i-1] )
                return false;
        return true;
        #endif 
        while ( i < n && nums[i] > nums[i-1] )
            i++;
        return i == n;
    }
    
};

// we find the number of drops. if it's larger than one, then it's obviously could not make to be strictly increasing by removing only one element 
// When we find a drop, then we need to make an adjustment in order for the check to continue correctly 
// There are two cases  
// a.  nums[i+1] > nums[i-1], then we could remove nums[i] and continue checking all elements following i+1 are larger than nums[i+1]
//             i
//        /         \
//       /          i+1
//      i-1         
// b.  nums[i+1] <= nums[i-1], then we could remove nums[i+1], but to ensure all following elements are larger than nums[i], 
//     we need to update nums[i+1] = nums[i], because the following checks start from nums[i+1] in the next iteration
//             i
//        /         \
//       i-1          \
//                   i+1        
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int drop = 0, n = nums.size(); 
        if ( n < 3 )
            return true;
        for ( int i = 0; i < n-1; i++ )
        {
            if ( nums[i+1] <= nums[i] )
            {
                drop++;
                if ( drop == 2 )
                    return false;
                if ( i > 0 && nums[i+1] <= nums[i-1] )
                    nums[i+1] = nums[i];
            }
        }
        
        return true;
    }
};