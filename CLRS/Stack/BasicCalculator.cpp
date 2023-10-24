/*
Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1 + 1"
Output: 2
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
 

Constraints:

1 <= s.length <= 3 * 105
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.
*/

// perceive '-' as the sign of the right number 
class Solution {
public:
    int calculate(string s) {
        stack<int> nums;
        int operand = 0, result = 0, sign = 1;
        for( int i = 0; i < s.size(); i++ )
        {
            char cur_ch = s[i];
            if ( isdigit(cur_ch) )
            {
                operand = operand * 10 + (cur_ch - '0');
            }
            if ( cur_ch == '+' )
            {
                result += sign * operand;
                sign = 1;
                operand = 0;
            }
            if ( cur_ch == '-' )
            {
                result += sign * operand;
                sign = -1;
                operand = 0;
            } 
            if ( cur_ch == '(' )
            {
                nums.push(result);
                nums.push(sign);
                sign = 1;
                result = 0;
            }
            if ( cur_ch == ')' )
            {
                result += sign * operand;
                result *= nums.top();
                nums.pop();
                result += nums.top();
                nums.pop();
                operand = 0;
            }
        }
        return result + (sign * operand);
    }
};

// Since we only allow '+' and '-' in this question, and they have the same precedence, then we can calculate each number's effect from left to right 
// Only thing is decided it's negativity. 
// To decide that, we need to know what is the sign of the it's parenthese as a whole. so we use a stack to maintain the sign of parenthese 
// then when we encounter an open, we push its sign to the stack, and when we encounter a close, we pop its corresponding sign from the stack 
// The effective sign of a num is (its immediate sign) * (it's parenthese sign)
class Solution {
public:
    int calculate(string s) {
        int cur_num = 0, sign = 1, ans = 0;
        stack<int> st{{sign}};      //signs preceding parenthese 
        for ( auto c : s )
        {
            if ( isdigit(c) )
                cur_num = cur_num * 10 + (c-'0');
            if ( c == '(')
                st.push(sign);
            if ( c == ')' )
                st.pop();
            if ( c == '+' || c == '-' )
            {
                ans += sign * cur_num;
                sign = (c == '+' ? 1 : -1) * st.top();
                cur_num = 0;
            }
        }

        return ans + sign * cur_num;
    }
};