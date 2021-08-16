/*
Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2x.

 

Example 1:

Input: n = 1
Output: true
Explanation: 20 = 1
Example 2:

Input: n = 16
Output: true
Explanation: 24 = 16
Example 3:

Input: n = 3
Output: false
Example 4:

Input: n = 4
Output: true
Example 5:

Input: n = 5
Output: false
 

Constraints:

-231 <= n <= 231 - 1
*/

// basically we need to check there is only one bit set in the num

// use x&-x keep only the rightmost 1
// Note: convert it to long first to avoid underflow 
#if 0
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if ( n == 0 )
            return false;
        long x = n;
        return (x & -x) == x;
    }
};

// use x & x - 1 clearing the rightmost bit 
// Note: convert it to long first to avoid underflow 
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if ( n == 0 )
            return false;
        long x = n;
        return (x & x-1) == 0;
    }
};
#endif 

#include <iostream>
#include <algorithm>

constexpr int HEAD = 5;
constexpr int NOTCHES = 4;
constexpr int RANG_NOTCHES = 3;

typedef struct {
    uint16_t start;
    uint16_t end;
} sidrange;

int main()
{
    sidrange data[HEAD][NOTCHES][RANG_NOTCHES];
    sidrange s = {0xdead,0xbeef};
    std::fill_n(static_cast<sidrange*>(&data[0][0][0]),HEAD*NOTCHES*RANG_NOTCHES,s);
    int32_t val = -512;
    std::cout << " val = " << std::hex << val << std::endl;
    return 0;
}
