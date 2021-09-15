/*
Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).

 

Example 1:


Input: root = [5,2,-3]
Output: [2,-3,4]
Example 2:


Input: root = [5,2,-5]
Output: [2]
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-105 <= Node.val <= 105

*/


// Again, answer the following two questions:
// 1. what to return upon visiting a node?
//          the subtree sum
// 2. what state to remember ?
//          increment the cnt of this sum to the global state 
class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int, int> sum2freq;
        dfs(root,sum2freq);
        int max_freq = INT_MIN;
        vector<int> res;
        for ( auto it : sum2freq )
        {
            max_freq = max(max_freq,it.second);
        }
        
        for ( auto it : sum2freq )
            if ( it.second == max_freq )
                res.push_back(it.first);
        
        return res;
    }
    
    int dfs(TreeNode* root, unordered_map<int,int>& sum2freq)
    {
        if (!root)
            return 0;
        int left_sum = dfs(root->left,sum2freq);
        int right_sum = dfs(root->right,sum2freq);
        int sum = left_sum + right_sum + root->val;
        sum2freq[sum]++;
        return sum;
    }
};