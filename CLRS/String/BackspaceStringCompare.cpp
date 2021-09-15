/*
Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

 

Example 1:

Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
Example 2:

Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".
Example 3:

Input: s = "a##c", t = "#a#c"
Output: true
Explanation: Both s and t become "c".
Example 4:

Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".
 

Constraints:

1 <= s.length, t.length <= 200
s and t only contain lowercase letters and '#' characters.
 

Follow up: Can you solve it in O(n) time and O(1) space?

*/

// one way would be to process the backspace separately for these two strings using two stacks and then compare 
// the processed results 

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> s1, s2;
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( s[i] != '#' )
                s1.push(s[i]);
            else if ( !s1.empty() )
                    s1.pop();
        }
    
        for ( int i = 0; i < t.size(); i++ )
        {
            if ( t[i] != '#' )
                s2.push(t[i]);
            else if ( !s2.empty() )
                s2.pop();
        }
        
        if ( s1.size() != s2.size() )
            return false;
        
        while(!s1.empty())
        {
            if ( s1.top() != s2.top() )
                return false;
            s1.pop();
            s2.pop();
        }
        
        return true;
    }
};

// Simiar idea as the above but without using stacks.
// Like parenthese matching, we keep a balance of unmatched '#' and if we encounter a '#', we increment the balance, otherwise we decrement the balance. 
// Then if both are consumed at the same time, then it return true. Otherwise, if any mismatch is encountered, return false.
// O(n) O(1)
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1, j = T.size() - 1;
        int numback1 = 0, numback2 = 0;
        while ( i >= 0 || j >= 0 )
        {
            while( i >= 0 && (numback1 > 0 || S[i] == '#') )
                S[i--] == '#' ? numback1++ : numback1--;
            while( j >= 0 && (numback2 >0 || T[j] == '#') )
                T[j--] == '#' ? numback2++ : numback2--;
            if ( i < 0 || j < 0 )
                return i == j;
            if ( S[i--] != T[j--] )
                return false;
        }
        
        return true;
    }
};