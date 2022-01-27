/*
Given an integer n, return all the strobogrammatic numbers that are of length n. You may return the answer in any order.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: n = 2
Output: ["11","69","88","96"]
Example 2:

Input: n = 1
Output: ["0","1","8"]
 

Constraints:

1 <= n <= 14
*/

// basically we have (n+1)/2 step to construct the string and at each step we have the state, i.e., the choices to choose from 
class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        unordered_map<char,char> m = {{'0','0'},{'1','1'},{'8','8'},{'6','9'},{'9','6'}};
        vector<string> res;
        string left,right;
        dfs(res,0,n-1,left,right,m);
        return res;
    }
    
    void dfs(vector<string> &res, int l, int r, string &left, string &right, unordered_map<char,char> const& m )
    {
        if ( l > r )
        {
            res.push_back(left+right);
        }
        else if ( l == r )
        {
            for ( auto c : {'0','1','8'} )
            {
                res.push_back(left+c+right);
            }
        }
        else 
        {
            for ( auto it : m )
            {
                if ( it.first == '0' && left.empty() )
                    continue;
                left += it.first;
                right.insert(right.begin(),it.second);
                dfs(res,l+1,r-1,left,right,m);
                left.pop_back();
                right.erase(right.begin());
            }
        }
    }
};