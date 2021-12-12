/*
Given an array of integers arr, return true if and only if it is a valid mountain array.

Recall that arr is a mountain array if and only if:

arr.length >= 3
There exists some i with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

 

Example 1:

Input: arr = [2,1]
Output: false
Example 2:

Input: arr = [3,5,5]
Output: false
Example 3:

Input: arr = [0,3,2,1]
Output: true
 

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 104
*/

// find the reflection point and check both left and right 
class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int reflection_idx = -1, n = arr.size(); 
        if ( n < 3 )
            return false;
        for ( int i = 1; i < n; i++ )
        {
            if ( arr[i] < arr[i-1] )
            {
                reflection_idx = i-1;
                break;
            }
        }
       if ( reflection_idx != -1 && reflection_idx != 0 )
       {
            for ( int i = 1; i <= reflection_idx; i++ )
            {
                if ( arr[i] <= arr[i-1] )
                    return false;
            }
            for ( int i = reflection_idx; i < n-1; i++ )
            {
                if ( arr[i+1] >= arr[i] )
                    return false;
            }
           
           return true;
       }
        return false;
        
    }
};

// can also use one-pass, walk-up to the reflection point and then walk-down to the end 
class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int n = arr.size(), i = 0;
        while( i+1 < n && arr[i] < arr[i+1] )
            i++;
        if ( i == 0 || i == n-1 )
            return false;
        while( i+1 < n && arr[i+1] < arr[i] )
            i++;
        return i == n-1;
        
    }
};