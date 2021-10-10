/*
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 105

*/

// Straight forward solution using bit XOR operation 
// However, it's O(n) and O(1)
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int res = 0;
        for ( auto n : nums )
            res ^= n;
        return res;
    }
};

// we can take advantage of the array being sorted and use binary search, bringing down the complexity to O(lgn)
// From what's given, we know there are an odd amount of numbers in total. We then check how mid compares with it's 
// two neighboring numbers and the amount of numbers to the right of the mid, i.e., odd or even.. 
// If there are even amount to the right of mid:
//    if nums[mid] == nums[mid+1], then the single number must be on the right side, i.e., lo = mid+2... as illustrated:   x x x x  A,  A,      y y y y y 
//                                                                                                                                 mid mid+1  mid+2
//    if nums[mid] == nums[mid-1], then the single number must be on the left side,   i.e., hi = mid-2...as illustrated:   x x x  x    A,   A,      y y y y y
//                                                                                                                              mid-2  mid-1 mid  
//    else nums[mid] is the single number 
// If there are odd amount to the right of mid:
//    if nums[mid] == nums[mid+1], then the single number must be on the left side, i.e., lo = mid+2... as illustrated:   x x x x x      A,  A,      y y y y 
//                                                                                                                               mid-1  mid mid+1 
//    if nums[mid] == nums[mid-1], then the single number must be on the right side,   i.e., hi = mid-2...as illustrated:   x x x  x    A,   A,      y y y y y
//                                                                                                                                    mid-1 mid   mid+1
//    else nums[mid] is the single number 
// else we are with only the single number 
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while( lo < hi )
        {
            int mid = lo + (hi-lo) / 2;
            int half_is_even = (hi-mid) % 2 == 0;
            if ( half_is_even )
            {
                if ( nums[mid] == nums[mid+1] )
                {
                    lo = mid+2;
                }
                else if ( nums[mid] == nums[mid-1] )
                {
                    hi = mid-2;
                }
                else 
                    return nums[mid];
            }
            else 
            {
                if ( nums[mid] == nums[mid+1] )
                {
                    hi = mid - 1;
                }
                else if ( nums[mid] == nums[mid-1] )
                {
                    lo = mid + 1;
                }
                else 
                {
                    return nums[mid];
                }
            }
        }
        
        return nums[lo];
    }
};


// Another solution will be based on checking only even-indexed nums, because there are odd amount of numbers, 
// then size()-1 is even. Then the pairs on the left side of the single element have [even, odd] indexes and the 
// pairs on the right side of the single element have [odd,even] indexes. Based on this, we can move to the appropriate 
// side to which the single element belongs 
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while( lo < hi )
        {
            int mid = lo + (hi-lo) / 2;
            mid = mid - mid % 2;
            if ( nums[mid] != nums[mid+1] )
                hi = mid;
            else 
                lo = mid + 2;
        }
        
        return nums[lo];
    }
};