/*
Morris traversal allows us to traverse the BST without recurision and using stack space. It's based on threaded tree. 
We will need to visit the nodes to create links first to establish the next pointers
Then we do an inorder-traversal to perform traversing
Finally, we revert the added links to restore the tree. This can be done while traversing 
*/

/*
Morris traversal procedure is as following:

1. Initialize current to the @root
2. While current is not NULL 
    If current does not have a left child // we are done with the left side, and it's time to deal with current 
        * visit/print current
        * move to right child current = current->right
    Else
        * Find rightmost node in the left subtree or node->right = current
        If we have found rightmost->right == current
            * Reset rightmost->right = nullptr; 
            * visit/print current 
            * Move to the right, current = current->right
        Else
            * Establish the next of the rightmost, i.e., rightmost->right = current
            * Move to the left child of the current, current = current->left
*/

#include "../Common/common_api.h"

void MorrisTraversal( TreeNode *root, vector<int> &res)
{
    TreeNode *current = root, *prev = nullptr;
    
    while ( current )
    {
        if ( current->left == nullptr )
        {
            res.push_back(current->data);
            current = current->right;
        }
        else
        {
            // go to left to find the rightmost node which is the predecessor of current 
            prev = current->left;
            while ( prev->right && prev->right != current )
                prev = prev->right;

            // we find the rightmost node the first time
            if ( prev->right == nullptr )
            {
                prev->right = current; 
                current = current->left;        // the left branch has not been visited yet, go to left branch
            }
            // find the rightmost node the second time, need to revert the change 
            else 
            {
                res.push_back(current->data);        // we have visisted the rightmost node, then visit current node and move to the right branch of current 
                prev->right = nullptr;
                current = current->right;          
            }
        }
    }
}


void dfs( TreeNode *root, int &sz )
{
    if ( root == nullptr )
        return;
    dfs(root->left,sz);
    sz++;
    dfs(root->right,sz);
}

// return true if we have found all medians 
bool processNode(float &sum, int idx, int sz, TreeNode *current)
{
    bool odd = sz % 2;
    if ( odd && idx == (sz+1) / 2 )
    {
        sum += current->data;
        return true;
    }
    if ( !odd && (idx == sz/2 || idx == sz/2 + 1) )
    {
        sum += current->data;
        if ( idx == sz/2 + 1 )
        {
            return true;
        }
    }
    
    return false;
}

float findMedian(TreeNode *root)
{
      //Code here
      int sz = 0, idx = 0;
      float sum = 0;
      dfs(root,sz);
      bool odd = sz%2;
      // do morris traversal and update sum when medians are encountered 
      TreeNode *current = root, *prev = nullptr;
      
      while ( current )
      {
          if ( current->left == nullptr )
          {
              idx++;
              processNode(sum,idx,sz,current);
              current = current->right;
          }
          
          else 
          {
              prev = current->left;
              while ( prev->right && prev->right != current )
                prev = prev->right;
              if ( prev->right == nullptr )
              {
                  prev->right = current;
                  current = current->left;
              }
              else
              {
                  prev->right = nullptr;
                  idx++;
                  processNode(sum,idx,sz,current);
                  current = current->right;
              }
          }
      }
      
      return sum / (odd ? 1 : 2 );
}

int main()
{
    /*
        construct the following binary tree:
                13 
              /      \
            10       18
           /   \     /   \
          3    11  15   20
         / \   / \ 
        1   6    12
    */
   vector<int> res;
   TreeNode *root = AllocTreeNode(13);
   root->left = AllocTreeNode(10);
   root->right = AllocTreeNode(18);
   root->left->left = AllocTreeNode(3);
   root->left->right = AllocTreeNode(11);
   root->right->left = AllocTreeNode(15);
   root->right->right = AllocTreeNode(20);
   root->left->left->left = AllocTreeNode(1);
   root->left->left->right = AllocTreeNode(6);
   root->left->right->right = AllocTreeNode(12);
    MorrisTraversal(root,res);
    PrintVector(res);
    float median = findMedian(root);

    cout << "median is " << median << endl;
}