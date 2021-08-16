/*
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...
 

Example 1:

Input: columnNumber = 1
Output: "A"
Example 2:

Input: columnNumber = 28
Output: "AB"
Example 3:

Input: columnNumber = 701
Output: "ZY"
Example 4:

Input: columnNumber = 2147483647
Output: "FXSHRXW"
 

Constraints:

1 <= columnNumber <= 231 - 1
*/

// The only special case is when a number is modulo of 26, then we need to set the bit to 'Z'. 

// Recursive solution
class Solution {
public:
    string convertToTitle(int n) {
        return n == 0 ? "" : (convertToTitle(n%26==0? n/26 - 1 : n/26) + (char)(--n%26 + 'A'));
    }
};

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans;
        while ( columnNumber )
        {
            int a = columnNumber % 26;
            ans += (a == 0 ? 'Z' : 'A' + (a-1));
            columnNumber = (--columnNumber) / 26;       // gracefully handle the case of being 26 multiples 
        }
        
        reverse(ans.begin(),ans.end());
        return ans;
    }
};