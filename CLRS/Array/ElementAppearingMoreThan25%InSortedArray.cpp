/*
Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.

 

Example 1:

Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6
Example 2:

Input: arr = [1,1]
Output: 1
 

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 105
*/

// the target must be in [A[n/4],A[n/2],A[3n/4]]. check each candidate's block length and will know which one is the target 

class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size(); 
        vector<int> candidates{arr[n/4],arr[n/2],arr[3*n/4]};
        for ( auto c : candidates ) {
            int left = lower_bound(arr.begin(),arr.end(),c) - arr.begin();
            int right = upper_bound(arr.begin(),arr.end(),c) - arr.begin() - 1;
            if ( right - left + 1 > n/4 )
                return c;
        }

        return -1;
    }
};