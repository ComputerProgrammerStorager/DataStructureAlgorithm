/*
Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.

Example 1:

Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10
 

Constraints:

1 <= expression.length <= 20
expression consists of digits and the operator '+', '-', and '*'.
All the integer values in the input expression are in the range [0, 99].
*/

// the key thought is that for each operator, we need to recursively process its left and right results respectively, and any operator could be the last operation 
// and then combine the results. If there is no operator in the expression, then it is a single numbre result
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> res;
        vector<int> left, right;
        for ( int i = 0; i < expression.size(); i++ )
        {
            if ( expression[i] != '+' && expression[i] != '-' && expression[i] != '*' )
                continue;
            left = diffWaysToCompute(expression.substr(0,i));
            right = diffWaysToCompute(expression.substr(i+1));
            
            for ( int l : left )
                for ( int r : right )
                {
                    switch(expression[i])
                    {
                        case '+':
                            res.push_back(l+r);
                            break;
                        case '-':
                            res.push_back(l-r);
                            break;
                        case '*':
                            res.push_back(l*r);
                            break;
                    }
                }
        }
            
        if ( res.empty() )
            res.push_back(stoi(expression));
        return res;
    }
};

// as always with the recursion solution, we could add memo to avoid repected calculation 
class Solution {
    vector<int> memo[21][21];
public:
    vector<int> diffWaysToCompute(string expression) {
        return dfs(expression,0,expression.size()-1);
    }
    
    vector<int> dfs(string const& expression, int s, int e)
    {
        vector<int> res, left, right;
        if ( !memo[s][e].empty() )
            return memo[s][e];
        for ( int i = s; i <= e; i++ )
        {
            if ( expression[i] != '+' && expression[i] != '-' && expression[i] != '*' )
                continue;
            left = dfs(expression, s, i-1 );
            right = dfs(expression,i+1, e);
            for ( int l : left )
                for ( int r : right )
                {
                    switch(expression[i])
                    {
                        case '+':
                            res.push_back(l+r);
                            break;
                        case '-':
                            res.push_back(l-r);
                            break;
                        case '*':
                            res.push_back(l*r);
                            break;
                    }
                }
        }
        if ( res.empty() )
            res.push_back(stoi(expression.substr(s,e-s+1)));
        return memo[s][e] = res;
    }
};