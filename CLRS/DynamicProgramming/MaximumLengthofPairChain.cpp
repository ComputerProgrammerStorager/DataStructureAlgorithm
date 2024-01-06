/*
You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.

You do not need to use up all the given intervals. You can select pairs in any order.

 

Example 1:

Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].
Example 2:

Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
 

Constraints:

n == pairs.length
1 <= n <= 1000
-1000 <= lefti < righti <= 1000
*/

// A variant of LIS with a bit tweak on the condition 

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if ( pairs.size() == 0 )
            return 0;
        sort(pairs.begin(),pairs.end());
        int n = pairs.size();
        vector<int> dp(n,1);
        for ( int i = 1; i < n; i++ )
        {
            for (int j = i-1; j >= 0; j-- )
                if ( pairs[j][1] < pairs[i][0] )
                    dp[i] = max(dp[i],dp[j]+1);
        }

        return *max_element(dp.begin(),dp.end());
    }
};

// sort the pairs based on end time and greedily pick up the pair which minimizes the cur end time; 
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto cmp =[](vector<int>& a, vector<int>&b) {
            return a[1] < b[1];
        };
        sort(pairs.begin(),pairs.end(),cmp);
        int ans = 0, cur = INT_MIN;
        for ( int i = 0; i < pairs.size(); i++ ) {
            if ( pairs[i][0] > cur ) {
                ans++;
                cur = pairs[i][1];
            }
        }

        return ans;
    }
};
