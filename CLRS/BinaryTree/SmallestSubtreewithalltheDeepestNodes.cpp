/*
Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest nodes of the tree.
Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
Example 2:

Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree.
Example 3:

Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest node in the tree is 2, the valid subtrees are the subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.
 

Constraints:

The number of nodes in the tree will be in the range [1, 500].
0 <= Node.val <= 500
The values of the nodes in the tree are unique.

*/

// we first find the deepest nodes set and then find the lca of those deepest nodes 
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
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        set<TreeNode*> deepestnode;
        int max_depth = 0, cur_depth = 0;
        stack<TreeNode*> s;
        unordered_map<TreeNode*, int> node2depth;
        if ( !root )
            return root;
        node2depth[root] = 0;
        s.push(root);
        while(!s.empty())
        {
            TreeNode* cur_node = s.top();
            s.pop();
            if ( cur_node->left )
            {
                node2depth[cur_node->left] = node2depth[cur_node] + 1;
                s.push(cur_node->left);
            }
            if ( cur_node->right )
            {
                node2depth[cur_node->right] = node2depth[cur_node] + 1;
                s.push(cur_node->right);
            }
        }
        
        for ( auto n : node2depth )
            max_depth = max(max_depth,n.second);
        
        for ( auto n : node2depth )
            if ( n.second == max_depth )
                deepestnode.insert(n.first);
        return find_lca(root,deepestnode);
    }
    
    TreeNode* find_lca(TreeNode *root, set<TreeNode*> const& nodes)
    {
        TreeNode *res = nullptr;
        dfs(root,nodes,&res);
        return res;
    }
    
    int dfs(TreeNode* root, set<TreeNode*> const& nodes, TreeNode **res)
    {
        if ( !root )
            return 0;
        int left = dfs(root->left,nodes,res);
        int right = dfs(root->right,nodes,res);
        int cur = nodes.count(root);
        int total = left+right+cur;
        if ( *res == nullptr && total == nodes.size() )
            *res = root;
        return total;
    }
};