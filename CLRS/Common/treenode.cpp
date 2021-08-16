#include "common_api.h"

TreeNode *AllocTreeNode(int val)
{
    TreeNode *node = new TreeNode;
    node->data = val;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}