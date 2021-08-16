/*
Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where 0 <= i < j < nums.length and nums[i] > 2 * nums[j].

 

Example 1:

Input: nums = [1,3,2,3,1]
Output: 2
Example 2:

Input: nums = [2,4,3,5,1]
Output: 3
 

Constraints:

1 <= nums.length <= 5 * 104
231 <= nums[i] <= 231 - 1
*/

// naive brute force approach 
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int rePairs = 0;
        int n = nums.size();
        if ( n < 2 )
            return rePairs;
        for ( int i = 0; i < n; i++ )
            for ( int j = i+1; j < n; j++ )
            {
                if ( (long)nums[i] > (long)2 * nums[j] )
                    rePairs++;
            }
        
        return rePairs;
    }
};

// we can maintain the preceding elements in a data structure (BST) to facilitate finding the number of elements larger than or equal to the 
// the current number
// The problem with BST is the BST could become skewed in case of ordered data set, causing the complexity to O(n^2) as bad as the above approach
class Solution {
    class Node {
        public: 
        Node *left, *right;
        long val;
        int count_ge;
        Node(int val) {
            left = nullptr;
            right = nullptr;
            count_ge = 1;
            this->val = val;
        }
    };
    Node* insert(Node *root, long val)
    {
        if ( root == nullptr )
            return new Node(val);
        else if ( val == root->val )
        {
            root->count_ge++;
        }
        else if (val < root->val)
        {
            root->left = insert(root->left,val);
        }
        else {
            root->count_ge++;
            root->right = insert(root->right,val);
        }
        
        return root;
    }
    
    int search(Node *root, long target)
    {
        if ( root == nullptr )
            return 0;
        else if ( target == root->val )
        {
            return root->count_ge;
        }
        else if ( target < root->val )
        {
            return root->count_ge + search(root->left,target);
        }
        else 
            return search(root->right,target);
    }
    
public:
    int reversePairs(vector<int>& nums) {
        Node *root = nullptr;
        int res = 0;
        int n = nums.size();
        for ( int i = 0; i < n; i++ )
        {
            res += search(root,nums[i]*2LL+1);
            root = insert(root,nums[i]);
        }
        
        return res;
    }
};