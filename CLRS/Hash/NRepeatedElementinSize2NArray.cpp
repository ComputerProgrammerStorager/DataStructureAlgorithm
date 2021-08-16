/*
In a array A of size 2N, there are N+1 unique elements, and exactly one of these elements is repeated N times.

Return the element repeated N times.

 

Example 1:

Input: [1,2,3,3]
Output: 3
Example 2:

Input: [2,1,2,5,3,2]
Output: 2
Example 3:

Input: [5,1,5,2,5,3,5,4]
Output: 5
 

Note:

4 <= A.length <= 10000
0 <= A[i] < 10000
A.length is even
*/

// hash table 
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_map<int,int> m;
        int n = A.size();
        int res;
        for ( int i = 0; i < n; i++ )
        {
            m[A[i]]++;
        }
        
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            if ( it->second != 1 )
            {
                res = it->first;
                break;
            }
        }
        
        return res;
    }
};


// use set 
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_set<int> m;
        int n = A.size();
        int res;
        for ( int i = 0; i < n; i++ )
        {
            if ( m.count(A[i]) )
            {
                res = A[i];
                break;
            }
            m.insert(A[i]);
        }
        
        return res;
    }
};


// distribute N numbers into N+1 hole. either there are consecutive or one apart the any other one
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int n = A.size();
        for ( int i = 0; i < n-1; i++ )
        {
            if ( A[i] == A[i+1] )
            {
                return A[i];
            }
        }
        int res;
        for ( int i = 0; i < 2; i++ )
        {
            if ( A[i] == A[n-1] || A[i] == A[n-2] )
            {
                res = A[i];
                break;
            }
        }
        
        return res;
    }
};