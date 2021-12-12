/*
Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
 

Note:

1 <= A.length <= 5000
*/

#include "../Common/common_api.h"

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int n = A.size(); 
        if ( n < 2 )
            return A;
        int l = 0, r = n - 1;
        while ( l < r )
        {
            while ( A[l] % 2 == 0 && l < r) 
                l++;
            while ( A[r] % 2 == 1 && r > l )
                r--;
            swap(A[l],A[r]);
            l++;
            r--;
        }
        
        return A;
    }
};

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int even_idx = 0, n = nums.size(), walk;
        while( even_idx < n && nums[even_idx] % 2 == 0 )
            even_idx++;
        walk = even_idx+1;
        while( walk < n )
        {
            while( walk < n && nums[walk] % 2 )
                walk++;
            if ( walk < n )
                swap(nums[even_idx++],nums[walk++]);
        }
        return nums;
    }
};

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        auto cmp = [](int a, int b){ 
            if ( a&1 )
                return false;
            return true;
        };
        sort(nums.begin(),nums.end(),cmp);
        return nums;
    }
};

int main()
{
    int arr[] = {0,2};
    vector<int> data(arr,arr+2);
    Solution s;
    s.sortArrayByParity(data);
}