/*
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
 

Constraints:

1 <= s.length <= 105
s[i] is either'(' , ')', or lowercase English letter.
*/


// essentially we are trying to maximually match the parentheses using stack 
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string res; 
        int cnt = s.size();
        unordered_set<int> invalid;
        stack<pair<char,int>> st;
        for ( int i = 0; i < cnt; i++ )
        {
            if ( s[i] == '(')
            {
                st.push({s[i],i});
            }
            else if ( s[i] == ')') {
                if ( st.empty() )
                {
                    invalid.insert(i);
                }
                else {
                    st.pop();
                }
            }
        }

        while (!st.empty())
        {
            auto cur = st.top();
            st.pop();
            invalid.insert(cur.second);
        }

        for ( int i = 0; i < cnt; i++ )
        {
            if ( invalid.count(i) == 0 )
                res += s[i];
        }

        return res;
    }
};