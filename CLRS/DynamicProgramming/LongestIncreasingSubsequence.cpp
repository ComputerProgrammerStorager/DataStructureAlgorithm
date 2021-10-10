#include "../Common/common_api.h"

// 1. Is suboptimal structured? Yes, because when we consider the next number, it depends on all previously examined subproblems 
// 2. Is subproblems overlapping ? Yes, subproblems are for reused for larger subproblems 
// 3. Recurrence:
//      a. use dp[i] to denote the LIS of data[1...i]
//                          |  max(dp[j]) + 1 for 0<=j < i if data[i] > data[j] 
//      b. then dp[i+1] =   |  1                           for all other cases
//                          | 
int LongestIncreasingSubsequence( const vector<int> &data )
{
    int n = data.size(), maxres = 1;
    if ( n == 0 )
    return 0;
    vector<int> dp(n,1);
    for (int i = 0; i < n; i++)
    {
        int prev_max = INT_MIN;
        for (int j = 0; j < i; j++ )
        {
            if (data[i] > data[j] && dp[j] > prev_max )
                prev_max = dp[j];
        }
        if ( prev_max != INT_MIN )
        {
            dp[i] = prev_max + 1;
            if (dp[i] > maxres )
                maxres = dp[i];
        }
    }
    return maxres;
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int res = 1, n = nums.size();
        vector<int> dp(n,1);
        for ( int i = 1; i < n; i++ )
        {
            for ( int j = 0; j < i; j++ )
            {
                if ( nums[j] < nums[i] )
                    dp[i] = max(dp[i],dp[j]+1);
            }
            
            res = max(res,dp[i]);
        }
        
        return res;
    }
};

// This is the recursive solution, for each position we could include it in the current subsequence (if the current element is larger)
// than the previously examined value, or we could exclude it from the subsequence. 
// O(2^n)
// O(n^2)
int lengthOfLIS(const vector<int> &nums, int prev_val, int curpos )
{
    if ( curpos == nums.size() )
    {
        return 0;
    }
    int taken_cur_len = 0;
    if ( nums[curpos] > prev_val )
    {
        taken_cur_len = lengthOfLIS(nums,nums[curpos],curpos+1) + 1;
    }
    int not_taken_cur_len = lengthOfLIS(nums,prev_val,curpos+1);
    return max(taken_cur_len,not_taken_cur_len);
}

int lengthOfLIS(vector<int>& nums) 
{
    return lengthOfLIS(nums,INT_MIN,0);
}

// recursion with memo optimization   
int lengthOfLISMemo(const vector<int> &nums, int prev_idx, int curpos, unordered_map<string,int> &m )
{
    string key = to_string(prev_idx+1) +','+ to_string(curpos);
    if ( m.count(key) )
        return m[key];
    int taken_cur_len = 0;
    if ( prev_idx == -1 || nums[curpos] > nums[prev_idx] )
    {
        taken_cur_len = lengthOfLISMemo(nums,nums[curpos],curpos+1,m) + 1;
    }
    int not_taken_cur_len = lengthOfLISMemo(nums,prev_idx,curpos+1,m);
    m[key] =  max(taken_cur_len,not_taken_cur_len);
    return m[key];
}

int lengthOfLISMemo(vector<int>& nums) 
{
    unordered_map<string,int> m;
    return lengthOfLISMemo(nums,-1,0,m);
}

int main()
{
#if 0
    vector<int> data{1,3,6,7,9,4,10,5,6};
    cout << " The LIS of vector: ";
    PrintVector(data);
    cout <<" is " << LongestIncreasingSubsequence(data) << "." << endl;
    vector<int> v{10,9,2,5,3,7,101,18};
   // cout << " with Memo " << lengthOfLISMemo(v) << endl;
#endif 
    int x = 0, y = 1;
    if ( x++ && y++ )
    {
        // do something
    }
    cout << "x = " << x << " y = " << y << endl;

    int m = 1, n = 1;
    if ( m++ || n-- )
    {
        // do something
    }
    cout << "m = " << m << " n = " << n << endl;
}