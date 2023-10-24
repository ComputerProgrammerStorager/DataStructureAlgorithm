/*
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 104
arr is sorted in ascending order.
-104 <= arr[i], x <= 104
*/

// use a customized sorting comparator 
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        auto cmp = [&](int a, int b) {
            if ( abs(a-x) == (b-x) ) 
            {
                return a < b;
            }
            else 
                return abs(a-x) < abs(b-x);
        };

        sort(arr.begin(),arr.end(),cmp);
        for ( int i = 0; i < k; i++ )
            res.push_back(arr[i]);
        sort(res.begin(),res.end());
        return res;
    }
};


// find the closest number and then expand the sliding window 
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        int n = arr.size();
        if ( n == k )
        {
            for ( int i = 0; i < k; i++ )
                res.push_back(arr[i]);
            return res;
        }

        int l = 0, r = n;
        while( l < r )
        {
            int m = (r+l)/2;
            if ( arr[m] >= x )
                r = m;
            else 
                l = m+1;
        }

        l -= 1;
        r = l+1;
        while( r - l - 1 < k )
        {
            if ( l == -1 )
            {
                r++;
                continue;
            }
            if ( r == n || abs(arr[l]-x) <= abs(arr[r]-x) )
                l--;
            else 
                r++;
        }

        for ( int i = l+1; i < r; i++ )
        {
            res.push_back(arr[i]);
        }

        return res;
    }
};

// Binary search based on comparison between nums[m] and nums[m+k]
// Because either nums[m] or nums[m+k] will be included in the res, but not both, it would cause its length to be greater than k
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size(), l = 0, r = n-k;
        while( l < r )
        {
            int  m = (r+l)/2;
            if ( x-arr[m] <= arr[m+k] - x ) 
            {
                r = m;
            }
            else {
                l = m+1;
            }
        }
        return vector<int>(arr.begin()+l,arr.begin()+l+k);
    }
};