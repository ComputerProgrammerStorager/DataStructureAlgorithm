/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = ""
Output: []
Example 3:

Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
*/


// Classical backtracking problem, considering the possible candidates at each and every step
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string cur;
        if ( digits.empty() )
            return res;
        vector<string> num2char = {{},{},{"abc"},{"def"},{"ghi"},{"jkl"},{"mno"},{"pqrs"},{"tuv"},{"wxyz"}};
        backtrack(digits,res,cur,num2char, 0);
        return res;
    }
    
    void backtrack(string const& digits, vector<string>& res, string& cur, vector<string> const& num2char, int idx )
    {
        if ( idx == digits.size() )
        {
            res.push_back(cur);
            return;
        }
        string can = num2char[digits[idx]-'0'];
        for ( auto c : can )
        {
            cur.push_back(c);
            backtrack(digits,res,cur,num2char,idx+1);
            cur.pop_back();
        }
    }
};