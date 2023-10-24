/*
Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.

A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

 

Example 1:


Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true
Example 2:


Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false
 

Constraints:

The number of nodes in the root tree is in the range [1, 2000].
The number of nodes in the subRoot tree is in the range [1, 1000].
-104 <= root.val <= 104
-104 <= subRoot.val <= 104
*/

// Recursion: check if the trees with each node as its root is the same as the given subtree, if it is return true
// otherwise, check if its left or right subtree containts the given subtree 

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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if ( !root )
            return false;
        if ( isIdentical(root,subRoot) )
            return true;
        return isSubtree(root->left,subRoot) || isSubtree(root->right,subRoot);
    }
private:
    bool isIdentical( TreeNode* root1, TreeNode* root2)
    {
        if ( !root1 || !root2 )
            return !root1 && !root2;
        return root1->val == root2->val && isIdentical(root1->left,root2->left) && isIdentical(root1->right,root2->right);
    }
};

// Use KMP to check if the serializaton of sub tree is a substring of the serialization of tree 
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string r, s;
        serialize(root,r);
        serialize(subRoot,s);
        return kmp(s,r);    // check if s is substring of r
    }
private:
    void serialize(TreeNode* root, string& tree_str)
    {
        if ( !root )
        {
            tree_str += "#";
            return;
        }
        tree_str += "^";
        tree_str += to_string(root->val);
        serialize(root->left,tree_str);
        serialize(root->right,tree_str);
    }
    bool kmp(string& needle, string& haystack)
    {
        int m = needle.size(), n = haystack.size();
        if ( n < m )
            return false;
        vector<int> lps(m);
        int prev = 0, i = 1;
        while( i < m)
        {
            if ( needle[i] == needle[prev] )
            {
                prev += 1;
                lps[i] = prev;
                i++;
            } else {
                if ( prev == 0 ){
                    lps[i] = 0;
                    i++;
                } else {
                    prev = lps[prev-1];
                }
            }
        }

        int haystackpos = 0, needlepos = 0;
        while( haystackpos < n )
        {
            if (haystack[haystackpos] == needle[needlepos] ) {
                haystackpos++;
                needlepos+;+
                if ( needlepos == m ) 
                    return true;
            }
            else {
                if ( needlepos == 0 ) {
                    haystackpos++;
                } else {
                    needlepos = lps[needlepos-1];
                }
            }
        }

        return false;
    }
};