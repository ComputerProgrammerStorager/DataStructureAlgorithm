/*
A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.

We can rotate digits of a number by 180 degrees to form new digits.

When 0, 1, 6, 8, and 9 are rotated 180 degrees, they become 0, 1, 9, 8, and 6 respectively.
When 2, 3, 4, 5, and 7 are rotated 180 degrees, they become invalid.
Note that after rotating a number, we can ignore leading zeros.

For example, after rotating 8000, we have 0008 which is considered as just 8.
Given an integer n, return the number of confusing numbers in the inclusive range [1, n].

 

Example 1:

Input: n = 20
Output: 6
Explanation: The confusing numbers are [6,9,10,16,18,19].
6 converts to 9.
9 converts to 6.
10 converts to 01 which is just 1.
16 converts to 91.
18 converts to 81.
19 converts to 61.
Example 2:

Input: n = 100
Output: 19
Explanation: The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,100].
 

Constraints:

1 <= n <= 109

*/

// First naive solution, check each number within the range
class Solution {
public:
    int confusingNumberII(int n) {
        int cnt = 0;
        for ( int i = 0; i <= n; i++ )
            if ( isconfusingNumber(i))
                cnt++;
        return cnt;
    }
    
private: 
    bool isconfusingNumber(int n )
    {
        int data[10] = {0,1,-1,-1,-1,-1,9,-1,8,6};
        int new_num = 0, old_num = n;
        while( n )
        {
            int val = n % 10;
            if ( data[val] == -1 )
                return false;
            new_num = new_num * 10 + data[val];
            n /= 10;
        }
        
        return new_num != old_num;
    }
};

// instead of checking each and every number within the range, we skip to check only those nubers comprise of the valid digits. 
class Solution {
public:
    int confusingNumberII(int n) {
        int cnt = 0;
        vector<int> nums = {0,1,6,9,8};
        for (auto x : {1,6,9,8} )
            dfs(x,n,cnt,nums);
        return cnt;
    }
    
    void dfs(long long x, int n, int &cnt, vector<int> const& nums )
    {
        if ( x > n )
            return;
        if ( isconfusingNumber(x) )
            cnt++;
        for ( auto y : nums ) 
            dfs(x*10+y,n,cnt,nums);
    }
    
private: 
    bool isconfusingNumber(int n )
    {
        int data[10] = {0,1,-1,-1,-1,-1,9,-1,8,6};
        int new_num = 0, old_num = n;
        while( n )
        {
            int val = n % 10;
            if ( data[val] == -1 )
                return false;
            new_num = new_num * 10 + data[val];
            n /= 10;
        }
        
        return new_num != old_num;
    }
};