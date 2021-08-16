/*
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Example 2:

Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
Example 3:

Input: head = [1], k = 1
Output: [1]
Example 4:

Input: head = [1,2], k = 1
Output: [2,1]
Example 5:

Input: head = [1,2,3], k = 2
Output: [1,2,3]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 105
0 <= Node.val <= 100
*/

// find the nodes the swap their values
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode *node1 = head, *node2 = nullptr;
        stack<ListNode *> st;
        int i = 1;
        while ( i++ < k)
        {
            node1 = node1->next;
        }
        ListNode *walk = head;
        while ( walk )
        {
            st.push(walk);
            walk = walk->next;
        }
        
        i = 1;
        while ( i++ < k )
        {
            st.pop();
        }
        
        node2 = st.top();
        if ( node2 == node1 )
            return head;
        node1->val ^= node2->val;
        node2->val ^= node1->val;
        node1->val ^= node2->val;
        return head;
    }
};

// we can rely on multiple passes to get the len first or we can use only one pass where we start traverse the endpointer when 
// we have reached the kth node from the head, because the end pointer will end at len-k position. 
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode *front = nullptr, *behind = nullptr, *walk = head;
        int len = 0;
        while ( walk )
        {
            len++;
            if ( behind != nullptr )
                behind = behind->next;
            
            if ( len == k )
            {
                front = walk;
                behind = head;
            }

            walk = walk->next;
        }
        
        swap(front->val,behind->val);
        return head;
    }
};