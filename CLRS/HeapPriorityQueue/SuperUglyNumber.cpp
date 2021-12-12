/*
A super ugly number is a positive integer whose prime factors are in the array primes.

Given an integer n and an array of integers primes, return the nth super ugly number.

The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

 

Example 1:

Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly numbers given primes = [2,7,13,19].
Example 2:

Input: n = 1, primes = [2,3,5]
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are in the array primes = [2,3,5].
 

Constraints:

1 <= n <= 106
1 <= primes.length <= 100
2 <= primes[i] <= 1000
primes[i] is guaranteed to be a prime number.
All the values of primes are unique and sorted in ascending order.
*/

// priority queue
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<long,vector<long>,greater<long>> pq;
        long res;
        for ( auto n : primes )
            pq.push(n);
        pq.push(1);
        if ( n == 1 )
            return 1;
        for ( int i = 0; i < n; i++ )
        {
            res = pq.top();
            pq.pop();
            while(!pq.empty() && pq.top() == res)
                pq.pop();
            for ( auto n : primes )
                pq.push(res*n);
        }
        return res;
    }
};

// we can associate the samllest number with where the idx of the sorted list that it comes from 
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<pair<long,long>,vector<pair<long,long>>,greater<pair<long,long>>> pq;
        vector<long> res(n,1);
        for ( int i = 0; i < primes.size(); i++ )
            pq.push({primes[i],0});
        int cnt = 1;
        while (cnt < n )
        {
            long num = pq.top().first, idx = pq.top().second;
            pq.pop();
            if ( num != res[cnt-1] )
            {
                res[cnt++] = num;
            }
            
            for ( auto p : primes )
                pq.push({num*p,idx+1});
        }
        return res[n-1];
    }
};

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<pair<long,long>,vector<pair<long,long>>,greater<pair<long,long>>> pq;
        vector<long> res(n,1);
        for ( int i = 0; i < primes.size(); i++ )
            pq.push({primes[i],0});
        int cnt = 1;
        while (cnt < n )
        {
            long num = pq.top().first, idx = pq.top().second;
            pq.pop();
            if ( num != res[cnt-1] )
            {
                res[cnt++] = num;
            }
            
            for ( auto p : primes )
                pq.push({num*p,idx+1});
        }
        return res[n-1];
    }
};

// maintain separate indexes for all the primes, and advance them if a value is selected, which is the same as the smallest from the list
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> dp(n,1), idx(primes.size(),0);
        for ( int i = 1; i < n; i++ )
        {
            dp[i] = INT_MAX;
            for ( int j = 0; j < primes.size(); j++ )
            {
                dp[i] = min(dp[i],primes[j] * dp[idx[j]]);
            }
                
            for ( int j = 0; j < primes.size(); j++ )
                if ( dp[i] == primes[j]*dp[idx[j]] )
                {
                    idx[j]++;
                }
        }
        
        return dp.back();
    }
};

// Tweak a bit to avoid time limit exceeded on leetcode 
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int p_sz = primes.size(); 
        vector<int> res(n,1), p_idx(p_sz,0);
        for ( int i = 1; i < n; i++ )
        {
            int val = INT_MAX;
            vector<int> min_idx;
            for ( int j = 0; j < p_sz; j++ )
            {
                int cur_num = res[p_idx[j]] * primes[j];
                if ( cur_num < val )
                {
                    min_idx.clear();
                    min_idx.push_back(j);
                    val = cur_num;
                }
                else if ( cur_num == val )
                {
                    min_idx.push_back(j);
                }
            }
            
            res[i] = val;
            for ( auto d : min_idx )
                p_idx[d]++;
        }
        
        return res.back();
    }
};