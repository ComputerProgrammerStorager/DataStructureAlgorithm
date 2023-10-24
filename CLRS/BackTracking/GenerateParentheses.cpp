/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
*/

// Build the valid strings of parenthese using backtracking 
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string cur;
        helper(res,cur,n,n);
        return res;
    }
private:
    void helper(vector<string>& res, string cur, int opens, int closes)
    {
        if ( opens > closes )
            return;
        if ( opens == 0 && closes == 0 )
            res.push_back(cur);
        if ( opens > 0 )
            helper(res,cur+'(',opens-1,closes);
        if ( closes > 0 )
            helper(res,cur+')',opens,closes -1);
    }
};

// divide and conquer them to left and right, and concatenate left and right
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if ( n == 0 )
            return {""};
        vector<string> res;
        for ( int left = 0; left < n; left++ )
        {
            for ( auto leftstr : generateParenthesis(left) )
            {
                for ( auto rightstr : generateParenthesis(n-1-left) )
                {
                    res.push_back("("+leftstr+")"+rightstr);
                }
            }
        }

        return res;
    }
};