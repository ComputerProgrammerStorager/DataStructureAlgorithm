/*
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

 

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Example 2:

Input: n = 2
Output: false
 

Constraints:

1 <= n <= 231 - 1
*/

// set to remember which numbers have been tested 
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen; 
        while( n != 1 ) {
            if ( seen.count(n) )
                return false;
            seen.insert(n);
            n = GetNext(n);
        }
        return true;
    }
    int GetNext(int num) {
        vector<int> digits;
        while( num ) {
            digits.push_back(num % 10);
            num /= 10;
        }
        for ( int i = 0; i < digits.size(); i++ ) {
            num += digits[i] * digits[i];
        }

        return num;
    }
};

// Slow and fast pointers
class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = GetNext(n);
        if ( n == 1 )
            return true;
        while( fast != 1 && slow != fast ) 
        {
            slow = GetNext(slow);
            fast = GetNext(GetNext(fast));
        }
        return fast == 1;
    }
    int GetNext(int num) {
        int sum = 0;
        while( num ) {
            sum += (num % 10) * (num % 10);
            num /= 10;
        }
        return sum;
    }
};