/*
Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

Return the number of good subarrays of A.

 

Example 1:

Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
Example 2:

Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 

Note:

1 <= A.length <= 20000
1 <= A[i] <= A.length
1 <= K <= A.length
Accepted
42,311
Submissions
83,252
*/

// Translate this problem to calculate at most K elements.
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return atMostK(A,K) - atMostK(A,K-1);
    }
    
    int atMostK( vector<int> const &A, int k )
    {
        unordered_map<int,int> m;
        int cnt = 0;
        int s = 0;
        for ( int e = 0; e < A.size(); e++ )
        {
            m[A[e]]++;
            while ( m.size() > k )
            {
                m[A[s]]--;
                if ( m[A[s]] == 0 )
                    m.erase(A[s]);
                s++;
            }
            cnt += (e-s)+1;
        }
        
        return cnt;
    }
};

int main()
{
    Solution s;
    vector<int> data = {1,2,1,2,3};
    s.EqualK(data,2);
}