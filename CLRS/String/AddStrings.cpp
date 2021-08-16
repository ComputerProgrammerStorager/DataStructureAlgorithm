/*
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

#include "../Common/common_api.h"

class Solution {
public:
    string addStrings(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        int len = max(m,n);
        string res;
        if ( len == m )
        {
            int i = 0;
            while ( i < len - n)
            {
                num2.insert(num2.begin(),'0');
                i++;
            }
                
        }
        if ( len == n )
        {
            int i = 0;
            while ( i < len - m )
            {
                num1.insert(num1.begin(),'0');
                i++;
            }
        }
        
        int carry = 0;
        for ( int i = len-1; i >= 0; i-- )
        {
            int sum = num1[i]-'0' + num2[i]-'0' + carry;
            carry = sum / 10;
            res.insert(res.begin(),(sum%10+'0'));
        }
        
        if ( carry )
            res.insert(res.begin(),'1');
        return res;
    }
};

class Solution {
public:
    string addStrings(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        int carry = 0, i = m-1, j = n -1;
        string res;
        while(i>= 0 && j >= 0)
        {
            int sum = num1[i] - '0' + num2[j] - '0' + carry;
            res = to_string(sum%10) + res;
            carry = sum / 10;
            i--;
            j--;
        }
        
        while( i >= 0 )
        {
            int sum = num1[i] -'0' + carry;
            res = to_string(sum%10) + res;
            carry = sum / 10;
            i--;
        }
        while ( j >= 0 )
        {
            int sum = num2[j] - '0' + carry;
            res = to_string(sum%10)+ res;
            carry = sum /10;
            j--;
        }
        if ( carry )
            res = "1" + res;
        return res;
    }
};

class Solution {
public:
    string addStrings(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        int i = m-1, j = n-1, carry = 0;
        string res;
        while( i >= 0 || j >= 0 )
        {
            int a = i >= 0 ? num1[i--]-'0' : 0;
            int b = j >= 0 ? num2[j--]-'0' : 0;
            int sum = a + b + carry;
            res.insert(res.begin(),sum%10+'0');
            carry = sum/10;
        }
        if ( carry )
            res = "1"+res;
        return res;
    }
};

int main()
{
    string num1 = "9", num2 = "99";
    Solution s;
    s.addStrings(num1,num2);

}