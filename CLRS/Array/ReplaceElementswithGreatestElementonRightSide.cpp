/*
Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.

After doing so, return the array.

 

Example 1:

Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]
Explanation: 
- index 0 --> the greatest element to the right of index 0 is index 1 (18).
- index 1 --> the greatest element to the right of index 1 is index 4 (6).
- index 2 --> the greatest element to the right of index 2 is index 4 (6).
- index 3 --> the greatest element to the right of index 3 is index 4 (6).
- index 4 --> the greatest element to the right of index 4 is index 5 (1).
- index 5 --> there are no elements to the right of index 5, so we put -1.
Example 2:

Input: arr = [400]
Output: [-1]
Explanation: There are no elements to the right of index 0.
 

Constraints:

1 <= arr.length <= 104
*/


// fill the results starting from the right side
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        if ( n == 0 )
            return res;
        res[n-1] = -1;
        for ( int j = n-2; j >= 0; j-- )
        {
            res[j] = max(res[j+1],arr[j+1]);
        }
        
        return res;
    }
};


// can also go without additional memory space
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        if ( n == 0 )
            return arr;
        int cur_val = arr[n-1];
        arr[n-1] = -1;
        for ( int j = n-2; j >= 0; j-- )
        {
           int tmp = arr[j];
            arr[j] = max(cur_val,arr[j+1]);
            cur_val = tmp;
        }
        
        return arr;
    }
};

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size(), max_sofar = -1;
        for ( int i = n-1; i >= 0; i-- )
        {
            int tmp = arr[i];
            arr[i] = max_sofar;
            max_sofar = max(max_sofar,tmp);
        }
        
        return arr;
    }
};