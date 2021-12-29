/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
*/

// use a stack 
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for ( auto c : s )
        {
            if ( isOpen(c) )
            {
                st.push(c);
            }
            else
            {
                if (st.empty() || !isMatched(st.top(),c) )
                    return false;
                st.pop();
            }
        }
        
        return st.empty();
    }
private: 
    bool isOpen(char c)
    {
        return c == '(' || c == '{' || c == '[';
    }
    
    bool isMatched(char open, char close)
    {
        return (open == '(' && close == ')') || (open == '[' && close == ']' ) || (open == '{' && close == '}');
    }
};