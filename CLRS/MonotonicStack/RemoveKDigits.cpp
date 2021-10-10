/*
Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

 

Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 

Constraints:

1 <= k <= num.length <= 105
num consists of only digits.
num does not have any leading zeros except for the zero itself.

*/

// First intuition is that we need to remove from the most signficant number first, as it has the highest weight 
// Second, we can for sure to remove the digits if whenever there is a smaller digit on their right side... Monotonically increasing stack !! 
// In the end, we need to removed how many digits we have removed and deal with: 
// The removed cnt is less than k, then we just remove the remaining from the end 
// It has leading zero
// it's empty.. 

class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st; 
        string res, tmp; 
        for ( auto ch : num )
        {
            while( !st.empty() && k > 0 && st.top() > ch )
            {
                st.pop();
                k--;
            }
            st.push(ch);
        }
        
        for ( int i = 0; i < k; i++ )
            st.pop();

        while( !st.empty() )
        {
            tmp.append(1,st.top());
            st.pop();
        }
        
        reverse(tmp.begin(),tmp.end());
        bool leading_zero = true;
        for ( auto ch : tmp )
        {
            if (leading_zero && ch == '0')
                continue;
            leading_zero = false;
            res.append(1,ch);
        }
        
        if ( res.empty() )
            return "0";
        return res;
    }
};