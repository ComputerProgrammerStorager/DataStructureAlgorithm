/*
You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.

 

Example 1:

Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
Example 2:

Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1
 

Constraints:

1 <= envelopes.length <= 105
envelopes[i].length == 2
1 <= wi, hi <= 105

*/


// We sort the envelopes based on widths, and use dfs + memorization to find the longest increase subsequence. 
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size(), res = 0;
        int mx_width = INT_MIN, mx_height = INT_MIN;
        for ( auto e : envelopes )
        {
            mx_width = max(mx_width,e[0]);
            mx_height = max(mx_height,e[1]);
        }

        vector<vector<int>> dp(mx_width+1,vector<int>(mx_height+1,0));
        sort(envelopes.begin(),envelopes.end());
        for ( int i = 0; i < n; i++ )
            res = max(res,dfs(envelopes,i,dp));
        return res;
    }

private:
    int dfs(const vector<vector<int>>& envelopes, int start, vector<vector<int>>& dp)
    {
        if ( dp[envelopes[start][0]][envelopes[start][1]] )
            return dp[envelopes[start][0]][envelopes[start][1]];
        int cnt = 1;
        for ( int next = start + 1; next < envelopes.size(); next++ )
        {
            if ( envelopes[next][0] > envelopes[start][0] && envelopes[next][1] > envelopes[start][1] )
            {
                cnt = max(cnt,dfs(envelopes,next,dp)+1);
            }
        }

        return dp[envelopes[start][0]][envelopes[start][1]] = cnt;
    }
};

// We could convert this 2D LIS problem into a 1D LIS problem
// First, we sort the nums by width, then the result would be the LIS of the heights, if there is no duplicate widths. 
// To deal with the cases where widths are the same, we sort the heights in descreasing order. In doing so, no two envelopes with the same widths 
// would ever be included in the LIS, because we are looking for increasing sequence !! 
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto cmp = [](vector<int>& a, vector<int>& b) {
            if ( a[0] < b[0] )
                return true;
            if ( a[0] > b[0] )
                return false;
            return a[1] > b[1];
        };

        sort(envelopes.begin(),envelopes.end(),cmp);
        vector<int> heights;
        for ( auto e : envelopes )
            heights.push_back(e[1]);
        return lis2(heights);
    }
private:
    int lis(const vector<int>& nums)
    {
        int n = nums.size();
        if ( n == 0 )
            return 0;
        vector<int> dp(n,1);
        for ( int i = 1; i < n; i++ )
        {
            for ( int j = 0; j < i; j++ )
            {
                if ( nums[i] > nums[j] )
                {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }
        return *max_element(dp.begin(),dp.end());
    }

    int lis2(const vector<int>& nums)
    {
        vector<int> seq;
        if ( nums.size() == 0 )
            return 0;
        seq.push_back(nums[0]);
        for ( int i = 1; i < nums.size(); i++ )
        {
            if ( nums[i] > seq.back() )
            {
                seq.push_back(nums[i]);
            }
            else 
            {
                seq[binarysearch(seq,nums[i])] = nums[i];
            }
        }

        return seq.size();
    }

    int binarysearch(const vector<int>& nums, int num )
    {
        int l = 0, r = nums.size() - 1;
        while ( l < r )
        {
            int m = (l+r)/2;
            if ( nums[m] == num )
                return m;
            if ( nums[m] > num )
                r = m;
            else 
                l = m+1;
        }
        return l;
    }
};