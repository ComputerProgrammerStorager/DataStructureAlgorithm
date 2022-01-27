/*
Given two strings low and high that represent two integers low and high where low <= high, return the number of strobogrammatic numbers in the range [low, high].

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: low = "50", high = "100"
Output: 3
Example 2:

Input: low = "0", high = "0"
Output: 1
 

Constraints:

1 <= low.length, high.length <= 15
low and high consist of only digits.
low <= high
low and high do not contain any leading zeros except for zero itself.

*/

// translate it to integral problem 
class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
        int cnt = 0, lessequallow = 0, lessequalhigh = 0;
        long long low_val = stoll(low,nullptr), high_val = stoll(high,nullptr);
        for ( auto num: {1,6,8,9})
            dfs_lessequalcnt(num,lessequallow,low_val);
        
        for ( auto num: {1,6,8,9})
           dfs_lessequalcnt(num,lessequalhigh,high_val);
        return lessequalhigh - lessequallow + isStrobogrammatic(low_val);
    }
private:
    
    // count how many strobogrammatic number that between [0,end]
    void dfs_lessequalcnt(long long num, int &cnt, long long end)
    {
        if ( num > end)
            return;
        if ( isStrobogrammatic(num) )
            cnt++;
        for ( auto val : {0,1,6,8,9} )
        {
            dfs_lessequalcnt(num*10+val,cnt,end);
        }
            
    }
    
    bool isStrobogrammatic(long long n)
    {
        int data[10] = {0,1,-1,-1,-1,-1,9,-1,8,6};
        long long new_num = 0, old_num = n;
        while( n )
        {
            int val = n % 10;
            if ( data[val] == -1 )
                return false;
            new_num = new_num * 10 + data[val];
            n /= 10;
        }
        
        return new_num == old_num;
    }
};