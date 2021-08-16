/*
Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

 

Example 1:


Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [0]
Output: [0]
Example 4:

Input: head = [1,3]
Output: [3,1]
 

Constraints:

The number of nodes in head is in the range [0, 2 * 104].
-10^5 <= Node.val <= 10^5
*/

// Recursive approach
// The key point is to find the middle ListNode (e.g., using slow and fast pointer) and break it (by tracking the prev of slow ptr, and note corner cases)

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if ( head == nullptr )
        {
            return nullptr;
        }
        
        ListNode *mid = findMiddleNode(head);
        TreeNode *root = new TreeNode(mid->val);
        if ( mid == head )
            return root;
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(mid->next);
        delete mid;
        return root;
    }
    
    ListNode *findMiddleNode(ListNode* head )
    {
        ListNode *prev_ptr = nullptr, *slow_ptr = head, *fast_ptr = head;
        while( fast_ptr != nullptr && fast_ptr->next != nullptr )
        {
            prev_ptr = slow_ptr;
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
        }
        if ( prev_ptr != nullptr )
        {
            prev_ptr->next = nullptr;
        }
        
        return slow_ptr;
    }
};

// the same idea, but using an auxiliary array to facilitate finding the middle element of the list 
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<ListNode*> listArr;
        if ( head == nullptr )
            return nullptr;
        while( head )
        {
            listArr.push_back(head);
            head = head->next;
        }
        
        return helper(listArr, 0,listArr.size()-1);
    }
    
    TreeNode* helper(vector<ListNode*> listArr, int s, int e)
    {
        TreeNode *root = nullptr;
        if ( s > e )
            return nullptr;
        
        int mid = (s+e)/2;
        root = new TreeNode(listArr[mid]->val);
        if ( s != e )
        {
            root->left = helper(listArr,s,mid-1);
            root->right = helper(listArr,mid+1,e);
        }
        return root;
    }
};

// simulating in-order traversal to build the tree 
class Solution {
    ListNode* head;
public:
    TreeNode* sortedListToBST(ListNode* head) {
        this->head = head;
        int n = findCount(head);
        return helper(0,n-1);
    }
    
    int findCount(ListNode* head)
    {
        int cnt = 0;
        ListNode* walk = head;
        while ( walk )
        {
            cnt++;
            walk = walk->next;
        }
        
        return cnt;
    }
    
    TreeNode* helper(int l, int r)
    {
        if ( l > r ) 
            return nullptr;
        int mid = (l+r)/2;
        TreeNode* left = helper(l,mid-1);

        TreeNode *root = new TreeNode(head->val);

        root->left = left;
        head = head->next;
        root->right = helper(mid+1,r);
        return root;
    }
};