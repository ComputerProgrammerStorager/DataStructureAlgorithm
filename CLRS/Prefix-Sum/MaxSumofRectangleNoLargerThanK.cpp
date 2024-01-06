/*
Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.

It is guaranteed that there will be a rectangle with a sum no larger than k.

 

Example 1:


Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
Example 2:

Input: matrix = [[2,2,-1]], k = 3
Output: 3
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-100 <= matrix[i][j] <= 100
-105 <= k <= 105
 

Follow up: What if the number of rows is much larger than the number of columns?
*/

// high level idea: 
// 1. store prefix sum in a set to find (S-k) 2. Consider any two rows and convert to 1D 3. Transpost if needed 
// thought processess: 
// if we need to find the maxsum subarray equal to k, this is easy and use Kandane's algorithm solves it 
// However, we need to find the maxsum subarray with a constraint, i.e., being less than k...
// go back a bit, how to find the subarray sum ? run and accumulate.. or prefix sum ? run and accumulate, this is O(n^2).. 
// use prefixsum, we are at nlg(n), by binary searching on prefixsums
// Our aim is to find two prefixsums S and X, which meet the condition S-X <= K, i.e., X >= S-K there could be multiple such X, but we want to find the smallest one, 
// such that S-X is maximized while.  This tells us we need to use the lower_bound on the sorted prefixsums. 
// Once we have the smallest X, then we (S-X) is one of the subarray sum that satisfies the constraint, and we use it to update the result if needed. 
// Then we convert 2D to 1D to use the above approach. When converting 2D to 1D, we just add all columns, as we are expanding rectangles column by column 
// If needed, we want transpose the array such that the column is bigger than row. 

// O(min(m,n)^2max(m,n)lg(max(m,n)))
// O(max(m,n))

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int K) {
        int m = matrix.size(), n = matrix[0].size(), res = INT_MIN;
        if ( m > n ) {
            vector<vector<int>> cpy(n,vector<int>(m));
            for (int i = 0; i < m; i++ ) 
                for ( int j = 0; j < n; j++ ) {
                    cpy[j][i] = matrix[i][j];
                }
            return maxSumSubmatrix(cpy,K);
        }
        for (int i = 0; i < m; i++ ) {
            vector<int> h(n,0);
            for ( int j = i; j < m; j++ ) {
                for ( int k = 0; k < n; k++ ) {
                    h[k] += matrix[j][k];
                }
                res = max(res,maxSum1DArray(h,K));
            }
        }

        return res;
    }

    int maxSum1DArray(const vector<int>& nums, int k) {
        int maxSum = INT_MIN, sum = 0, n = nums.size();
        set<int> prefixsums{0};
        for ( auto n : nums ) {
            sum += n;
            auto it = prefixsums.lower_bound(sum - k);
            if ( it != prefixsums.end() ) {
                maxSum = max(maxSum, sum - *it);
            }
            prefixsums.insert(sum);
        }

        return maxSum;
    }
};