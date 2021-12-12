/*
Given the root of a binary tree, collect a tree's nodes as if you were doing this:

Collect all the leaf nodes.
Remove all the leaf nodes.
Repeat until the tree is empty.
 

Example 1:


Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]
Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.
Example 2:

Input: root = [1]
Output: [[1]]
 

Constraints:

The number of nodes in the tree is in the range [1, 100].

*/

// Basically, this requries printing out the nodes in height order, i.e., print height zero (leaves) first..
// So we can construct node to height mapping using dfs and then group all nodes belong to the same height 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        unordered_map<TreeNode*, int> node2height;
        int height = dfs(root,node2height);
        vector<vector<int>> res(height+1);
        for ( auto n : node2height )
        {
            res[n.second].push_back(n.first->val);
        }
        
        return res;
    }
    
    int dfs(TreeNode* node, unordered_map<TreeNode*,int> &node2height)
    {
        if ( !node )
            return -1;
        int height = 1 + max(dfs(node->left,node2height),dfs(node->right,node2height));
        node2height[node] = height;
        return height;
    }
    
};


// we can avoid using the map space by updating the res as it recurses 
class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> res;
        dfs(root,res);
        return res;
    }
    
    int dfs(TreeNode* node, vector<vector<int>> &res)
    {
        if ( !node )
            return -1;
        int h = 1 + max(dfs(node->left,res),dfs(node->right,res));
        if ( res.size() < h + 1 )
            res.resize(h+1);
        res[h].push_back(node->val);
        return h;
    }
    
};