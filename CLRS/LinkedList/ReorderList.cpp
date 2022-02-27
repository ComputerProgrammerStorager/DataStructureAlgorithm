/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4]
Output: [1,4,2,3]
Example 2:


Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
 

Constraints:

The number of nodes in the list is in the range [1, 5 * 104].
1 <= Node.val <= 1000

*/

// Basically we parse the list to construct pairs of nodes with first from the first half of the list and second from the second half of the list 
// with the second half picked in the reverse order. This hints us to use a double queue to help us.
class Solution {
public:
    void reorderList(ListNode* head) {
        deque<ListNode*> dq;
        if ( !head || !head->next )
            return;
        ListNode *walk = head;
        ListNode dummy(-1), *tail = &dummy;
        while( walk )
        {
            ListNode* next = walk->next;
            dq.push_back(walk);
            walk = next;
        }
        
        while( dq.size() > 1 )
        {
            tail->next = dq.front();
            dq.pop_front();
            tail->next->next = dq.back();
            dq.pop_back();
            tail = tail->next->next;
            tail->next = nullptr;
        }
        
        if ( dq.size() )
        {
            tail->next = dq.front();
            tail = tail->next;
            tail->next = nullptr;
        }
        
        dq.pop_front();
    }
};