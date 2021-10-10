/*
Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
 

Constraints:

1 <= a.length, b.length <= 104
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.
*/

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int a_len = a.size(), b_len = b.size();
        int min_len = min(a_len,b_len);
        int carry = 0, a_pos = a_len-1, b_pos = b_len-1;
        while( min_len-- > 0 )
        {
            int cur = carry + (a[a_pos--]-'0')  + (b[b_pos--]-'0');
            carry = cur / 2;
            cur %= 2;
            res += (cur+'0');
        }
        
        while( a_pos >= 0 )
        {
            int cur = carry + (a[a_pos--]-'0');
            carry = cur / 2;
            cur %= 2;
            res += (cur+'0');
        }
        
        while( b_pos >= 0 )
        {
            int cur = carry + (b[b_pos--]-'0');
            carry = cur / 2;
            cur %= 2;
            res += (cur+'0');
        }
        if ( carry )
            res += (carry + '0');
        reverse(res.begin(),res.end());
        return res;
    }
};

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int a_len = a.size(), b_len = b.size(), i = a_len - 1, j = b_len - 1, carry = 0;
        while( i >= 0 || j >= 0)
        {
            int a_val = i >= 0 ? a[i--]-'0' : 0;
            int b_val = j >= 0 ? b[j--]-'0' : 0;
            int val = a_val + b_val + carry;
            carry = val/2;
            val %= 2;
            res.push_back(val+'0');
        }
        
        if ( carry )
            res.push_back('1');
        reverse(res.begin(),res.end());
        return res;
    }
};