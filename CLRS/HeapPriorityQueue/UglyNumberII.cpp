/*
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.

 

Example 1:

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
Example 2:

Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
 

Constraints:

1 <= n <= 1690

*/

// Ugly numbers are genereated in this manner: 
// the next ugly number will be the min(x*2,x*3,x*5) for any of the existing ugly numbers, therefore we can maintain respective min_idx for values 
// that is used to generate the next ugly number. if the next ugly number happend to be generated from *i, then we just increment the idx i.
// the reason is because we can consider a factor(2,3,5) for the next ugly number only if the correspondingly factored ugly number is selected. 
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> res(1,1);
        int idx2 = 0, idx3 = 0, idx5 = 0;
        for ( int i = 1; i < n; i++ )
        {
            int d2 = res[idx2]*2, d3 = res[idx3]*3, d5 = res[idx5]*5;
            int mn = min(d2,min(d3,d5));
            if ( mn == d2 )
                idx2++;
            if ( mn == d3 )
                idx3++;
            if ( mn == d5 )
                idx5++;
            res.push_back(mn);
        }
        
        return res.back();
    }
};

// we can use priority queue to faciliate finding the next ugly number 
class Solution {
public:
    int nthUglyNumber(int n) {
        long res, it = 0;
        priority_queue<long,vector<long>,greater<long>> pq;
        pq.push(1);
        while( it < n )
        {
            res = pq.top();
            pq.pop();
            while( !pq.empty() && pq.top() == res )
                pq.pop();
            it++;
            pq.push(res*2);
            pq.push(res*3);
            pq.push(res*5);
        }
        
        return res;
    }
};