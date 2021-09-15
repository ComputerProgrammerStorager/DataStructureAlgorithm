/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

 

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
 

Follow up: Could you solve it both recursively and iteratively?
*/

// recursive: two trees are mirrored if their values are equal and left of left is mirror of right of right 

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isMirror(root,root);
    }
    bool isMirror(TreeNode *root1, TreeNode*root2 )
    {
        if ( !root1 && !root2 )
            return true;
        if ( !root1 || !root2 )
            return false;
        return root1->val == root2->val && isMirror(root1->left,root2->right) && isMirror(root1->right,root2->left);
    }
};

// we can use a queue to help us check the pair of nodes..
// The key is to construct pairs of (left,right) and (right,left)
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<pair<TreeNode*, TreeNode*> > q;
        q.push({root,root});
        while(!q.empty())
        {
            auto tmp = q.front();
            q.pop();
            if ( !checkMirror(tmp) )
                return false;
            if ( tmp.first)
            {
                q.push({(tmp.first)->left,(tmp.second)->right});
                q.push({(tmp.first)->right,(tmp.second)->left});
            }
        }
        
        return true;
    }
    
    bool checkMirror(pair<TreeNode*,TreeNode*> const& p)
    {
        if ( !p.first && !p.second )
            return true;
        if ( !p.first || !p.second )
            return false;
        if ( p.first->val != p.second->val )
            return false;
        return true;
    }
};