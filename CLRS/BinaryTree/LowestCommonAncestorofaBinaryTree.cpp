/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1
*/

// we search the current node's subtrees and return the nodes (either p or q ) in the subtress, respectively. 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ( !root )
            return nullptr;
        if ( root == p || root == q )
            return root;
        TreeNode *leftResult = lowestCommonAncestor(root->left,p,q);
        TreeNode *rightResult = lowestCommonAncestor(root->right,p,q);
        if ( leftResult && rightResult )
        {
            return root;
        }
        if ( !leftResult )
            return rightResult;
        if ( !rightResult )
            return leftResult;
        return nullptr;
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res;
        dfs(root,p,q, &res);
        return res;
    }

    bool dfs(TreeNode* root, TreeNode* p, TreeNode *q, TreeNode **res)
    {
        if ( !root ) 
            return false;
        bool left = dfs(root->left,p,q, res);
        bool right = dfs(root->right,p,q, res);
        bool mid = root == p || root == q;
        if ( mid + left + right == 2 )
            *res = root;
        return mid || left || right;
    }
};

// we first get the parent path for both p and q, and then walk up the tree to find the lowest common ancestor 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> s;
        unordered_map<TreeNode *, TreeNode*> m; // map to their parents 
        unordered_set<TreeNode*> ancestors;
        m[root] = nullptr;
        s.push(root);
        
        while( !m.count(p) || !m.count(q) )
        {
            TreeNode *cur_node = s.top();
            s.pop();
            if ( cur_node->left )
            {
                m[cur_node->left] = cur_node;
                s.push(cur_node->left);
            }
            if ( cur_node->right )
            {
                m[cur_node->right] = cur_node;
                s.push(cur_node->right);
            }
        }
        
        while(p)
        {
            ancestors.insert(p);
            p = m[p];
        }
        
        while(q)
        {
            if ( ancestors.count(q) )
                return q;
            q = m[q];
        }
        
        return nullptr;
    }
};

// The same as to get parent first, but using dfs. 
// Note that the last elment of both P and Q are the root
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> P;
        vector<TreeNode*> Q;
        TreeNode *res = nullptr;
        
        dfs_get_path(root,p,P);
        dfs_get_path(root,q,Q);
        int i = P.size()-1, j = Q.size()-1;
        while ( i >= 0 && j >= 0 && P[i] == Q[j] ) {
            res = P[i];
            i--;
            j--;
        }
            
        return res;
    }
    
    bool dfs_get_path(TreeNode* root, TreeNode *node, vector<TreeNode*> &path)
    {
        if (!root)
            return false;
        if ( root == node || dfs_get_path(root->left,node,path) || dfs_get_path(root->right,node,path) )
        {
            path.push_back(root);
            return true;
        }
        else
        return false;
    }
    
};