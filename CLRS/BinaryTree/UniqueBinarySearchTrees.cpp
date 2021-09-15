/*
Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.


Example 1:


Input: n = 3
Output: 5
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 19

*/

// We can perceieve this problem recurisvely, i.e., each node can be a root, and calculate the left subtree 
// and the right subtree BST recurively. Once we get the left and right, then the total number of left * right 
// Let G(i) denote the number of BST that has i nodes [1,i]. Then G(0) = 1, G(1) = 1.
// Let F(i,n) denote the number of BST that has i as root and total number of BST, then F(i,n) = G(i-1) * G(n-i)
// G(n) = F(1,n) + F(2,n) + ... + F(n,n)
//        Sigma(G(i-1)*G(n-i)) for i = 1 to n 
// then we can use dynamical programming to calculate the result 

class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1,0);
        dp[0] = 1, dp[1] = 1;
        for ( int i = 2; i <= n; i++ )
        {
            for ( int j = 1; j < i+1; j++ )
                dp[i] += dp[j-1] * dp[i-j];
        }
        
        return dp[n];
    }
};