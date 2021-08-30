/*
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: 3
Example 2:

Input: root = [1,null,2]
Output: 2
Example 3:

Input: root = []
Output: 0
Example 4:

Input: root = [0]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-100 <= Node.val <= 100

*/

// For defs on tree problems, the key point is to assume you are standing at the current node
// In this case, the depth of the currently standing node is the max of left and right subtree plus 1 (itself)
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};

// we can use a stack to simulate the recursion process and update the result if we find a larger value 
// the key point is remember the height of the currently being visited node 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        int max_depth = 0;
        stack<pair<int,TreeNode*>> st;
        st.push({1,root});
        while ( !st.empty() ) 
        {
            auto cur = st.top();
            st.pop();
            max_depth = max(max_depth,cur.first);
            if ( cur.second->left )
            {
                st.push({cur.first+1,cur.second->left});
            }
            
            if ( cur.second->right)
            {
                st.push({cur.first+1,cur.second->right});
            }
        }
        
        return max_depth;
    }
};

// In face, we can leverage level-order traversal to get the depth of the tree, i.e., the levels of the tree is its max depth 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        int max_depth = 0;
        queue<TreeNode *> q;
        q.push(root);
        while( !q.empty())
        {
            int cur_sz = q.size();
            for ( int i = 0; i < cur_sz; i++ )
            {
                TreeNode *cur_node = q.front();
                q.pop();
                if ( cur_node->left )
                    q.push(cur_node->left);
                if ( cur_node->right)
                    q.push(cur_node->right);
            }
            max_depth++;
        }
        
        return max_depth;
    }
};