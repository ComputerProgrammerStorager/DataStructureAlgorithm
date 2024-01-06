/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return any of them.

It is guaranteed that the length of the answer string is less than 104 for all the given inputs.

 

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 4, denominator = 333
Output: "0.(012)"
 

Constraints:

-231 <= numerator, denominator <= 231 - 1
denominator != 0
*/


// check zero, check sign, watch over overflow, use a map to remember a digit reappears or not and if so the position to insert the parenthese 
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string res;
        if ( numerator == 0) 
            return "0";
        if ( numerator < 0 ^ denominator < 0 ) 
            res += "-";
        long n = labs(numerator), d = labs(denominator);
        res += to_string(n/d);
        if ( n % d == 0 )
            return res;
        res += ".";
        unordered_map<long,int> m;
        for ( n %= d; n; n %= d ) {
            if ( m.count(n) ) {
                res.insert(m[n],1,'(');
                res += ")";
                return res;
            }
            m[n] = res.size();
            n *= 10;
            res += to_string(n/d);
        }
        
        return res;
    }
};