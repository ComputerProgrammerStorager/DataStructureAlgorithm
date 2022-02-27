/*
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Find the kth positive integer that is missing from this array.

 

Example 1:

Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
Example 2:

Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.
 

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
arr[i] < arr[j] for 1 <= i < j <= arr.length
*/

// naive solution makes it an easy problem 
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int missing = 0, val = 1;
        unordered_set<int> v(arr.begin(),arr.end());
        while( missing < k )
        {
            if ( v.count(val) == 0 )
                missing++;
            if ( missing == k )
                break;    
            val++;
        }
        
        return val;
    }
};

// we can check how many holes are there between each continuous interval 
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        if ( k < arr[0] )
            return k;
        k -= arr[0] - 1;
        for ( int i = 1; i < arr.size(); i++ )
        {
            int curmissing = arr[i] - arr[i-1] - 1;
            if ( curmissing >= k )
                return arr[i-1] + k;
            k -= curmissing;
        }
        
        return arr.back()+k;
    }
};

// we can also use binary search to find it
// the key observation is that the amount of missing number for arr[pos] is arr[pos] - pos - 1, given the numbers 
// are all positive numbers.. 
// when the loop ends, we have left == right + 1, and the value should be between arr[right] and arr[left]. 
// then we get the kth missing number as arr[right] + (k-(arr[right]-right-1)) == k+right+1, or alternatively, k + left

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int left = 0, right = arr.size() - 1;
        while( left <= right )
        {
            int mid = left + (right-left) / 2;
            int curmissing = arr[mid] - mid - 1;
            if ( curmissing < k )
                left = mid+1;
            else
                right = mid-1;
        }
        
        return k+right+1;       // k + left;
    }
};
