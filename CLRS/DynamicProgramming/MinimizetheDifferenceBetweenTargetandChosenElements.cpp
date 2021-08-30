/*
You are given an m x n integer matrix mat and an integer target.

Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized.

Return the minimum absolute difference.

The absolute difference between two numbers a and b is the absolute value of a - b.

 

Example 1:


Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
Output: 0
Explanation: One possible choice is to:
- Choose 1 from the first row.
- Choose 5 from the second row.
- Choose 7 from the third row.
The sum of the chosen elements is 13, which equals the target, so the absolute difference is 0.
Example 2:


Input: mat = [[1],[2],[3]], target = 100
Output: 94
Explanation: The best possible choice is to:
- Choose 1 from the first row.
- Choose 2 from the second row.
- Choose 3 from the third row.
The sum of the chosen elements is 6, and the absolute difference is 94.
Example 3:


Input: mat = [[1,2,9,8,7]], target = 6
Output: 1
Explanation: The best choice is to choose 7 from the first row.
The absolute difference is 1.
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 70
1 <= mat[i][j] <= 70
1 <= target <= 800

*/

// Basically, we need to enumerate all possibilities and find the minimum absolute difference.
// So we use a set to maintain what are the current sums and add each number of the next row to 
// each of the numbers in the sum set to generate the next sum set
// This could result in a complexity of O(70 * 70 * 4900), as at any step the sum set could have at most 4900 numbers, per the given conditions. 
// We could optimize it by only remembering the smallest of the numbers that are larger than @target, because we seek to find the minimum absolute difference
// This could bring down the complexity to O(70*70*target). 
// Note that at each step we could not just keep the closest but smaller sum to the target, because the next step might bring a smaller sum to be closer to the target. 
// For instance, assume the current sum set is { 14, 18 },  target is 20, and the next row is {6}.. In actuality, 14+6 would result in the minimum absolute difference
// being zero. So we could not exclude 14 in the previous step. 

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size(), n = mat[0].size();
        unordered_set<int> sum{0};
        for ( int i = 0; i < m; i++ )
        {
            int large_min = INT_MAX;
            unordered_set<int> next_sum;
            for ( auto s : sum )
            {
                for ( int j = 0; j < n; j++ )
                {
                    int val = s + mat[i][j];
                    if ( val <= target )
                    {
                        next_sum.insert(val);
                    }
                    else
                    {
                        large_min = min(large_min,val);
                    }
                }
            }
            
            if ( large_min != INT_MAX )
                next_sum.insert(large_min);
            sum = std::move(next_sum);
        }
        
        int diff = INT_MAX;
        for ( auto n : sum )
            diff = min(diff,abs(n-target));
        return diff;
    }
};