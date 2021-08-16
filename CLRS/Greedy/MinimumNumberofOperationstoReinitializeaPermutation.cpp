/*
You are given an even integer n​​​​​​. You initially have a permutation perm of size n​​ where perm[i] == i​ (0-indexed)​​​​.

In one operation, you will create a new array arr, and for each i:

If i % 2 == 0, then arr[i] = perm[i / 2].
If i % 2 == 1, then arr[i] = perm[n / 2 + (i - 1) / 2].
You will then assign arr​​​​ to perm.

Return the minimum non-zero number of operations you need to perform on perm to return the permutation to its initial value.

 

Example 1:

Input: n = 2
Output: 1
Explanation: perm = [0,1] initially.
After the 1st operation, perm = [0,1]
So it takes only 1 operation.
Example 2:

Input: n = 4
Output: 2
Explanation: perm = [0,1,2,3] initially.
After the 1st operation, perm = [0,2,1,3]
After the 2nd operation, perm = [0,1,2,3]
So it takes only 2 operations.
Example 3:

Input: n = 6
Output: 4
 

Constraints:

2 <= n <= 1000
n​​​​​​ is even.
*/

// naive brute force method that emulates the process of changing 
class Solution {
public:
    int reinitializePermutation(int n) {
        vector<int> perm0(n);
        for ( int i = 0; i < n; i++ )
        {
            perm0[i] = i;
        }
        
        int count = 0;
        vector<int> perm = perm0;
        while (1)
        {
            vector<int> arr(n);
            for ( int i = 0; i < n; i++ )
            {
                if ( i % 2 == 0 )
                {
                    arr[i] = perm[i/2];
                }
                else 
                {
                    arr[i] = perm[n/2+(i-1)/2];
                }
            }
            count++;
            if ( arr == perm0 )
            {
                return count;
            }
            
            perm = arr;
        }
        
        return count;
    }
};

/*
next round: i --> f(i):

if ( i < n/2 )
    f(i) = 2 * i;
else 
    f(i) = 2 * i - (n-1);

f(i) = 2*i mod (n-1)
    
f^k(i) = i* 2^k * mod (n-1) == i

utimately we are looking for this const equation: a
2^k mod (n-1) == 1
*/

class Solution {
public:
    int reinitializePermutation(int n) {
        int k = 1, power = 2;
        if ( n == 2 )
            return 1;
        while ( power % (n-1) != 1 )
        {
            power *= 2;
            power %= (n-1);
            k++;
        }
        return k;
    }
};