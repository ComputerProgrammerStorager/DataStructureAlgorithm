/*
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:

Input: s = ")("
Output: [""]
 

Constraints:

1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.
*/

// First find the left and right that need to remove. then check each possible substrings if it is valid and rem are zeor 
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        auto [l,r] = getleftandrightcnt(s);
        dfs(s, res, 0, l, r );
        return res;
    }

    void dfs(const string&s, vector<string>& res, int start, int l, int r ) {
        if ( l == 0 && r == 0 && isValid(s) )
        {
            res.push_back(s);
            return ;
        }
        for ( int i = start; i < s.size(); i++ ) {
            if ( i > start && s[i] == s[i-1] )
                continue;
            if ( l > 0 && s[i] == '(' ) {
                dfs(s.substr(0,i)+s.substr(i+1), res, i,l-1,r);
            }
            if ( r > 0 && s[i] == ')' ) {
                dfs(s.substr(0,i)+s.substr(i+1), res, i,l,r-1);
            }
        }
    }

    bool isValid(const string&s ) {
        int open = 0;
        for ( auto c : s ) {
            if ( c == '(' ) {
                open++;
            } else if ( c == ')' ) {
                if ( open == 0 )
                    return false;
                open--;
            }
        }

        return open == 0;
    }


    pair<int,int> getleftandrightcnt(const string& s) {
        int l = 0, r = 0;
        for ( auto c : s ) {
            if ( c == '(' ) { 
                l++;
            } else if ( c == ')' ) {
                if ( l == 0 )
                    r++;
                else 
                    l--;
            }
        }

        return {l,r};
    }


};