/*
You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).

Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.

An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.

Note: Test cases are generated such that there will always be at least one correct answer.

 

Example 1:

Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
Output: [1,2,-3]
Explanation: [1,2,-3] is able to achieve the given subset sums:
- []: sum is 0
- [1]: sum is 1
- [2]: sum is 2
- [1,2]: sum is 3
- [-3]: sum is -3
- [1,-3]: sum is -2
- [2,-3]: sum is -1
- [1,2,-3]: sum is 0
Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
Example 2:

Input: n = 2, sums = [0,0,0,0]
Output: [0,0]
Explanation: The only correct answer is [0,0].
Example 3:

Input: n = 4, sums = [0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8]
Output: [0,-1,4,5]
Explanation: [0,-1,4,5] is able to achieve the given subset sums.
 

Constraints:

1 <= n <= 15
sums.length == 2n
-104 <= sums[i] <= 104

*/

// we know that if the numbers are all non-negative, then it's easy, beause after sorting, the second number should be a numbe in the original 
// array. Then we can use the number to partition the array into two sum subsets, which contains and does not contain the number. So we could proceed
// with the following step: 
// 1. If there is any negative number, transfer it to non-negative counterpart. 
// 2. If there is any negative number, find a subset of the non-negative result, whose sum is -mn and change all of them to negative using backtracking dfs. 
// Note: I don't understand why step2 is sufficient and necessary to find the final result, but it seems to work. 
class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        int mn = *min_element(begin(sums),end(sums));
        vector<int> ans;
        if ( mn < 0 )
        {
            for ( auto &val : sums )
                val += -mn;
        }
        multiset<int> s(begin(sums),end(sums)), next_s;
        for ( int i = 0; i < n; i++ )
        {
            int cur_num = *next(begin(s));
            ans.push_back(cur_num);
            while(s.size() > 0)
            {
                int first = *begin(s);
                s.erase(begin(s));
                next_s.insert(first);
                s.erase(s.find(first+cur_num));
            }
            swap(s,next_s);
        }
        
        if ( mn < 0 )
            dfs(ans,-mn,0);
        return ans;
    }
    
private:
    bool dfs(vector<int> &ans, int target_sum, int pos)
    {
        if ( pos == ans.size() ) 
            return target_sum == 0;
        int cur_val = ans[pos];
        if ( dfs(ans,target_sum,pos+1) )
            return true;
        ans[pos] = -cur_val;
        if ( dfs(ans,target_sum-cur_val,pos+1) )
            return true;
        ans[pos] = cur_val;
        return false;
    }
};

// assume the original array is N0...Ni-1, Z0..Zj-1, P0....Pk-1, i.e., it has i negative integers, j zeros and k positive integers 
// then after sorting, the difference between the minimum (all negative sum) and the second minimum is the absolute value of one of the elements 
// i.e., assume the difference is d > 0, then either -d or d is one of the numbers. 
// Then we can partition the sums into two parts, one having the found number and the other having no the number
// Regardless, if the sums fall into pairs whose difference is d.  Then the one having zero in is the one that doesn't have d in it, which should be processed next. 
// It could be possible that both parts may have zeros, which indicates that there exist a pair of x and -x in the original array. We could choose either partition in this case to proceed. 
class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        vector<int> ans;
        multiset<int> cursums(begin(sums),end(sums));
        while( ans.size() < n ) 
        {
            int d = *next(begin(cursums)) - *begin(cursums);
            multiset<int> small, large;
            while( cursums.size() > 0 )
            {
                int num = *cursums.begin();
                cursums.erase(cursums.begin());
                cursums.erase(cursums.find(num+d));
                small.insert(num);
                large.insert(num+d);
            }
            
            if ( small.count(0) ) 
            {
                ans.push_back(d);
                swap(cursums,small);
            }
            else
            {
                ans.push_back(-d);
                swap(cursums,large);
            }
        }
        
        return ans;
    }
};