/*
Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.

 

Example 1:

Input: arr = [1,0,2,3,0,4,5,0]
Output: [1,0,0,2,3,0,0,4]
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
Example 2:

Input: arr = [1,2,3]
Output: [1,2,3]
Explanation: After calling your function, the input array is modified to: [1,2,3]
 

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 9
*/

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size(), i = 0, j = 0;
        vector<int> tmp(arr.begin(),arr.end());
        while( j < n )
        {
            arr[j++] = tmp[i];
            if ( !tmp[i] && j < n )
                arr[j++] = tmp[i];
            i++;
        }
    }
};

// we can go without using extra space, the critical observation is that we need to find the last_index up to which it will 
// use up the whole array by expanding zeros. One case needing special care is when the last_index is zero, where we need to distinguish 
// if the whole array is used up after itself or after duplicate this last zero. 
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size(), last_index = 0, cnt = 0;
        bool last_zero_duplicate = false;
        if ( n == 0 )
            return;
        while( cnt < n )
        {
            cnt++;
            if ( cnt == n )
            {
                if ( arr[last_index] == 0 )
                {
                    last_zero_duplicate = false;
                }
            }
            else if ( arr[last_index] == 0 )
            {
                cnt++;
                if ( cnt == n )
                {
                    last_zero_duplicate = true;
                }
            }
            last_index++;
        }
        last_index--;
        if ( arr[last_index] == 0 )
        {
            arr[--cnt] = 0;
            if ( last_zero_duplicate && cnt > 0 ) 
            {
                arr[--cnt] = 0;
            }
            last_index--;
        }
        while( last_index >= 0 )
        {
            arr[--cnt] = arr[last_index];
            if ( arr[last_index] == 0 )
                arr[--cnt] = 0;
            last_index--;
        }
    }
};