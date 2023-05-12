/*
Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.

 

Example 1:

Input: arr = [5,5,4], k = 1
Output: 1
Explanation: Remove the single 4, only 5 is left.
Example 2:
Input: arr = [4,3,1,1,3,3,2], k = 3
Output: 2
Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
0 <= k <= arr.length

*/

// sort the numbers based on their frequencies and start with removing the least frequent numbers until can not lead any further unique number to be removed. 
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int,int> m;
        vector<pair<int,int>> uniquenums;
        int removals = 0;
        for (auto num : arr )
            m[num]++;
        for ( auto& it : m )
        {
            uniquenums.push_back({it.second,it.first});
        }
        sort(uniquenums.begin(),uniquenums.end());
        for ( auto& p : uniquenums)
        {
            if ( p.first <= k )
            {
                removals++;
                k -= p.first;
            }
            else 
            {
                break;
            }
        }
        return uniquenums.size() - removals;
    }
};