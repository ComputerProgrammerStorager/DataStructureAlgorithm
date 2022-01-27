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
class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        vector<int> res;
        sort(sums.begin(),sums.end());
        if ( dfs(sums,n,res) ) 
            return res;
        return {};
    }
private: 
    void Partition(vector<int> const& sums, int pivot, vector<int> &pairSum)
    {
        int n = sums.size(), i = 0;
        multiset<int> st(sums.begin(),sums.end());
        while( i < n/2 )
        {
            int sum, pair_sum;
            if ( pivot < 0 )    // pivot < 0, then the smallest must have pivot as part of it 
            {
                sum = *st.begin();   
            }
            else    // pivot >= 0 case, the biggest sum must have pivot as part of it 
            {
                sum = *st.rbegin();
            }
            pair_sum = sum-pivot;
            if ( st.find(pair_sum) == st.end() )
                break;
            pairSum.push_back(pair_sum);
            st.erase(st.find(sum));
            st.erase(st.find(pair_sum));
            i++;
        }
    }
    
    bool dfs(vector<int>& sums, int rem_num, vector<int> &res )
    {
        if ( rem_num == 1 )
        {
            if ( sums[0] && sums[1] )
                return false;
            res.push_back(sums[0] ? sums[0] : sums[1] );
            return true;
        }
        
        //sort(sums.begin(), sums.end());
        int n = sums.size(), d = sums[n-1] - sums[n-2];
        vector<int> pairSum;        // sums that do not have d or -d 
        Partition(sums,d,pairSum);
        if ( pairSum.size() == n/2 )
        {
            res.push_back(d);
            if ( dfs(pairSum,rem_num-1,res) )
                return true;
            res.pop_back();
        }
        
        pairSum.clear();
        Partition(sums,-d,pairSum);
        if ( pairSum.size() == n/2 )
        {
            res.push_back(-d);
            if ( dfs(pairSum,rem_num-1,res) ) 
                return true;
            res.pop_back();
        }
        
        return false;
    }
};


class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        multiset<int> rem_sums(sums.begin(),sums.end());
        vector<int> res; 
        while( rem_sums.size() > 1)
        {
            int d = *rem_sums.begin() - *next(rem_sums.begin());  // we know d <= 0
            vector<int> small_sum, small_pair_sum;
            multiset<int> small_sum_set, small_pair_sum_set;
            while( rem_sums.size() > 1 )
            {
                int smallest = *rem_sums.begin();
                rem_sums.erase(rem_sums.begin());
                auto pair = rem_sums.find(smallest-d);
                small_pair_sum.push_back(*pair);
                small_sum.push_back(smallest);
                rem_sums.erase(pair);
            }
            for ( auto &x : small_sum )
                small_sum_set.insert(x);
   
            for ( auto &x : small_pair_sum )
                small_pair_sum_set.insert(x);
            if ( small_sum_set.count(0) )
            {
                res.push_back(-d);
                rem_sums.swap(small_sum_set);
            }
            else 
            {
                res.push_back(d);
                rem_sums.swap(small_pair_sum_set);
            }
        }
        
        return res;
    }
};