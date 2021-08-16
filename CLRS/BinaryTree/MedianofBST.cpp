/*
Given a Binary Search Tree of size N, find the Median of its Node values.
*/

// This method uses inorder traversal to obtain an inorder traversal of the elements and then find the median.. Note consierdering odd or even size. 
// O(n) space 
void findSize( struct Node *node, int &sz )
{
    if ( node == nullptr )
        return;
    findSize(node->left,sz);
    findSize(node->right,sz);
    sz++;
    
}

void dfs( struct Node *root, vector<int> &inorder)
{
    if ( root == nullptr )
        return;
    dfs(root->left,inorder);
    inorder.push_back(root->data);
    dfs(root->right,inorder);
}


float findMedian(struct Node *root)
{
      //Code here
      //int sz = 0;
      //findSize(root,sz);
      vector<int> inorder;
      dfs(root,inorder);
      int n = inorder.size();
      if ( n % 2 )
        return inorder[n/2];
      else
        return float(inorder[n/2-1] + inorder[n/2]) / 2;
}


// we can also use Morris Traversal to obtain the median withou extra space (stack) 
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
