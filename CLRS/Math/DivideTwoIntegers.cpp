/*
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, assume that your function returns 231 − 1 when the division result overflows.

 
Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Example 3:

Input: dividend = 0, divisor = 1
Output: 0
Example 4:

Input: dividend = 1, divisor = 1
Output: 1
 

Constraints:

-231 <= dividend, divisor <= 231 - 1
divisor != 0

*/

// The problem mainly tests the ability to identify and handle vairious edge cases 
// First, we need to note that the negative range is one larger than the positive range, so when we convert 
// negative to positive, -INT_MIN overflows 
// The key pooint is to convert positives to negative and then adjust final result based on sign 

class Solution {
public:
    int divide(int dividend, int divisor) {
        int negatives = 2;
        if ( dividend == INT_MIN && divisor == -1 )
            return INT_MAX;
        
        if ( dividend > 0 )
        {
            negatives--;
            dividend = -dividend;
        }
        
        if ( divisor > 0 )
        {
            negatives--;
            divisor = - divisor;
        }
        
        int quotient = 0;
        while ( dividend - divisor <= 0 )
        {
            dividend -= divisor;
            quotient++;
        }
        
        if ( negatives == 1 )
        {
            quotient = -quotient;
        }
        
        return quotient;
    }

};


//To speed up the convergence, we can double the divisor every time and loop multiple times
class Solution {
public:
    int divide(int dividend, int divisor) {
        int negatives = 2;
        int HALF_INT_MIN = -1073741824;
        if ( dividend == INT_MIN && divisor == -1 )
            return INT_MAX;
        
        if ( dividend > 0 )
        {
            negatives--;
            dividend = -dividend;
        }
        
        if ( divisor > 0 )
        {
            negatives--;
            divisor = -divisor;
        }
        
        int quotient = 0;
        while ( divisor >= dividend )
        {
            int poweroftwo = -1;
            int value = divisor;
            while ( value >= HALF_INT_MIN && value + value >= dividend )
            {
                poweroftwo += poweroftwo;
                value += value;
            }
            
            quotient += poweroftwo;
            dividend -= value;
        }
        
        if ( negatives != 1 )
        {
            quotient = -quotient;
        }
        
        return quotient;
    }

};

// to avoid repeating calculating the powers of the divisor, we can precomputer them in a array 
class Solution {
public:
    int divide(int dividend, int divisor) {
        int negatives = 2;
        int HALF_INT_MIN = -1073741824;
        if ( dividend == INT_MIN && divisor == -1 )
            return INT_MAX;
        
        if ( dividend > 0 )
        {
            negatives--;
            dividend = -dividend;
        }
        
        if ( divisor > 0 )
        {
            negatives--;
            divisor = -divisor;
        }
        
        vector<int> doubles;
        vector<int> powersoftwo;
        
        int poweroftwo = -1;
        while ( divisor >= dividend )
        {
            doubles.push_back(divisor);
            powersoftwo.push_back(poweroftwo);
            if ( divisor < HALF_INT_MIN )
                break;
            poweroftwo += poweroftwo;
            divisor += divisor;
        }
        
        int quotient = 0;

        for ( int i = doubles.size() - 1; i >= 0; i-- )
        {
            if ( doubles[i] >= dividend )
            {
                quotient += powersoftwo[i];
                dividend -= doubles[i];
            }
        }
        
        if ( negatives != 1 )
        {
            quotient = -quotient;
        }
        
        return quotient;
    }

};


// we can save storing the powers of two intermediate helper tables by starting from the 
// largest power of 2 and working back with smaller powers 
class Solution {
public:
    int divide(int dividend, int divisor) {
        int negatives = 2;
        int HALF_INT_MIN = -1073741824;
        if ( dividend == INT_MIN && divisor == -1 )
            return INT_MAX;
        
        if ( dividend > 0 )
        {
            negatives--;
            dividend = -dividend;
        }
        
        if ( divisor > 0 )
        {
            negatives--;
            divisor = -divisor;
        }
        
        int highestdouble = divisor;
        int highestpoweroftwo = -1;
        
        while ( highestdouble >= HALF_INT_MIN && highestdouble + highestdouble >= dividend ) 
        {
            highestdouble += highestdouble;
            highestpoweroftwo += highestpoweroftwo;
        }
        
        int quotient = 0;
        while ( dividend <= divisor )
        {
            if ( dividend <= highestdouble )
            {
                quotient += highestpoweroftwo;
                dividend -= highestdouble;
            }
            
            highestpoweroftwo >>= 1;
            highestdouble >>= 1;
        }
        
        if ( negatives != 1 )
        {
            quotient = -quotient;
        }
        
        return quotient;
    }

};


// this approach emulates the division process 
class Solution {
public:
    int divide(int dividend, int divisor) {
        int negatives = 2;
        int HALF_INT_MIN = -1073741824;
        if ( dividend == INT_MIN && divisor == -1 )
            return INT_MAX;
        
        if ( dividend == INT_MIN && divisor == 1 )
            return INT_MIN;
        
        if ( dividend > 0 )
        {
            negatives--;
            dividend = -dividend;
        }
        
        if ( divisor > 0 )
        {
            negatives--;
            divisor = -divisor;
        }
        
        int maxbit = 0;
        while ( divisor >= HALF_INT_MIN && divisor + divisor >= dividend )
        {
            maxbit += 1;
            divisor += divisor;
        }
        
        int quotient = 0;

        for ( int bit = maxbit; bit >= 0; bit-- )
        {
            if ( divisor >= dividend )
            {
                quotient -= (1 << bit);
                dividend -= divisor;
            }
            
            divisor = (divisor+1) >> 1;
        }
        
        if ( negatives != 1 )
        {
            quotient = -quotient;
        }
        
        return quotient;
    }

};