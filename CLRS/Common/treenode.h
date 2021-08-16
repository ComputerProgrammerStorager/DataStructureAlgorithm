// This defines the tree node structure for various usage 
// @TODO: change to use template to allow for different valu types 

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *AllocTreeNode(int val);