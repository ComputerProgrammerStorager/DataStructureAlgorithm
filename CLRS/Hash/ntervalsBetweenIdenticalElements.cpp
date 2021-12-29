/*
You are given a 0-indexed array of n integers arr.

The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.

Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].

Note: |x| is the absolute value of x.

 

Example 1:

Input: arr = [2,1,3,1,2,3,3]
Output: [4,2,7,2,4,4,5]
Explanation:
- Index 0: Another 2 is found at index 4. |0 - 4| = 4
- Index 1: Another 1 is found at index 3. |1 - 3| = 2
- Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
- Index 3: Another 1 is found at index 1. |3 - 1| = 2
- Index 4: Another 2 is found at index 0. |4 - 0| = 4
- Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
- Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
Example 2:

Input: arr = [10,5,10,10]
Output: [5,0,3,4]
Explanation:
- Index 0: Two more 10s are found at indices 2 and 3. |0 - 2| + |0 - 3| = 5
- Index 1: There is only one 5 in the array, so its sum of intervals to identical elements is 0.
- Index 2: Two more 10s are found at indices 0 and 3. |2 - 0| + |2 - 3| = 3
- Index 3: Two more 10s are found at indices 0 and 2. |3 - 0| + |3 - 2| = 4
 

Constraints:

n == arr.length
1 <= n <= 105
1 <= arr[i] <= 105

*/

// use a hash map to group all indexes having the same value.. then process the set of index for each value 
class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        unordered_map<int,vector<int>> val2idxes;
        vector<long long> res;
        for ( int i = 0; i < arr.size(); i++ )
            val2idxes[arr[i]].push_back(i);
        for ( int i = 0; i < arr.size(); i++ )
        {
            if ( val2idxes[arr[i]].size() == 1 )
                res.push_back(0);
            else
            {
                long long cnt = 0;
                for ( auto idx : val2idxes[arr[i]] )
                    if ( idx != i )
                    {
                        cnt += abs(idx-i);
                    }
                res.push_back(cnt);
            }
        }
        
        return res;
    }
};

// we can use prefix sum to calculate the set of indexes for each same value 
class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        unordered_map<int,vector<int>> val2idxes;
        vector<long long> res(arr.size(),0);
        for ( int i = 0; i < arr.size(); i++ )
            val2idxes[arr[i]].push_back(i);
        for ( auto e : val2idxes )
        {
            vector<int> tmp(e.second);
            int n = tmp.size();
            vector<long long> pre_sum(n,0);
            if ( n == 1 )
            {
                res[tmp[0]] = 0;
            }
            else 
            {
                for ( int i = 0; i < n; i++ )
                {
                    pre_sum[i] = i == 0 ? tmp[i] : pre_sum[i-1] + tmp[i];
                }

                for ( int i = 0; i < n; i++ )
                {
                    long long cnt = (long long)tmp[i] * i - (i==0 ? 0 : pre_sum[i-1]) + (pre_sum[n-1] - pre_sum[i]) - (long long)tmp[i] * (n-i-1);
                    res[tmp[i]] = cnt;
                }
            }
        }
        
        return res;
    }
};