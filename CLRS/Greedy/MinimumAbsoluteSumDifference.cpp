/*
You are given two positive integer arrays nums1 and nums2, both of length n.

The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).

You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.

Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.

|x| is defined as:

x if x >= 0, or
-x if x < 0.
 

Example 1:

Input: nums1 = [1,7,5], nums2 = [2,3,5]
Output: 3
Explanation: There are two possible optimal solutions:
- Replace the second element with the first: [1,7,5] => [1,1,5], or
- Replace the second element with the third: [1,7,5] => [1,5,5].
Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
Example 2:

Input: nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
Output: 0
Explanation: nums1 is equal to nums2 so no replacement is needed. This will result in an 
absolute sum difference of 0.
Example 3:

Input: nums1 = [1,10,4,4,2,7], nums2 = [9,3,5,1,7,4]
Output: 20
Explanation: Replace the first element with the second: [1,10,4,4,2,7] => [10,10,4,4,2,7].
This yields an absolute sum difference of |10-9| + |10-3| + |4-5| + |4-1| + |2-7| + |7-4| = 20
 

Constraints:

n == nums1.length
n == nums2.length
1 <= n <= 105
1 <= nums1[i], nums2[i] <= 105
*/

#if 0
Note:
lower_bound finds the first element that is not less than the given value 
upper_bound finds the first element that is greater than the give value 
// lower_bound and upper_bound in vector
#include <algorithm> // for lower_bound, upper_bound and sort
#include <iostream>
#include <vector> // for vector
 
using namespace std;
 
int main()
{
    int gfg[] = { 5, 6, 7, 7, 6, 5, 5, 6 };
 
    vector<int> v(gfg, gfg + 8); // 5 6 7 7 6 5 5 6
 
    sort(v.begin(), v.end()); // 5 5 5 6 6 6 7 7
 
    vector<int>::iterator lower, upper;
    lower = lower_bound(v.begin(), v.end(), 7);
    upper = upper_bound(v.begin(), v.end(), 7);
 
    cout << "lower_bound for 6 at position "
         << (lower - v.begin() + 1) << '\n';
    cout << "upper_bound for 6 at position "
         << (upper - v.begin() + 1) << '\n';
 
    return 0;
}
#endif

// Idea: use greedy algorithm to find the possible closest replacement in nums1, which would result in a possible 
// biggest absolute decrease. 
// Then the result will be simply the original abs sum minus the maximum descrease
class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> tmp(nums1);
        sort(tmp.begin(),tmp.end());
        int maxDecrease = 0;
        for ( int i = 0; i < n; i++ )
        {
            int originDiff = abs(nums1[i]-nums2[i]);
            int prev_num = INT_MAX/2, cur_num = INT_MAX/2;
            auto rep = lower_bound(tmp.begin(),tmp.end(),nums2[i]);
            if ( rep != tmp.begin() )
                prev_num = *prev(rep);
            if ( rep != tmp.end() )
                cur_num = *rep;
            int newDiff = min(abs(prev_num-nums2[i]),abs(cur_num-nums2[i]));
            maxDecrease = max(maxDecrease,originDiff - newDiff);
        }
        
        long ret = 0;
        constexpr long M = 1e9 + 7;
        for ( int i = 0; i < n; i++ )
        {
            ret += abs((long)nums1[i]-(long)nums2[i]) % M;
            ret %= M;
        }
        
        ret -= maxDecrease;
        ret %= M;
        return ret;
    }
};