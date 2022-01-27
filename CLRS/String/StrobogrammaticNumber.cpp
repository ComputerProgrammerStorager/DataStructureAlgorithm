/*
Given a string num which represents an integer, return true if num is a strobogrammatic number.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: num = "69"
Output: true
Example 2:

Input: num = "88"
Output: true
Example 3:

Input: num = "962"
Output: false
 

Constraints:

1 <= num.length <= 50
num consists of only digits.
num does not contain any leading zeros except for zero itself.
*/
// find the pair (8,8), (1,1), (0,0), (6,9) and handle only one letter properly 
class Solution {
public:
    bool isStrobogrammatic(string num) {
        int n = num.size(); 
        if ( n == 0 )
            return true;
        if ( n == 1 )
        {
            if ( num[0] == '8' || num[0] == '1')
                return true;
            return false;
        }
        int l = 0, r = n-1;
        while(l < r )
        {
            if ( (num[l] == '8' && num[r] == '8') || 
                 (num[l] == '6' && num[r] == '9') || 
                 (num[l] == '9' && num[r] == '6') ||
                 (num[l] == '1' && num[r] == '1') || 
                 (num[l] == '0' && num[r] == '0') )
            {
                l++;
                r--;
            }
            else
                return false;
        }
        return l == r ? (num[l] == '0' || num[l] == '1' || num[l] == '8') : true;

    }
};

// concise code using map 
class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char,char> m;
        char c1[] = {'0','1','8','9','6'};
        char c2[] = {'0','1','8','6','9'};
        for ( int i = 0; i < 5; i++ )
            m[c1[i]] = c2[i];
        
        int l = 0, r = num.size() - 1;
        while( l <= r )
        {
            if ( m[num[l]] != num[r] || m[num[r]] != num[l] )
                return false;
            l++;
            r--;
        }
        return true;
    }
};