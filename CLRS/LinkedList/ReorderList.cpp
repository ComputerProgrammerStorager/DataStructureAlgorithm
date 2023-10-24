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


// 1. find the middle 
// 2. reverse the second half
// 3. merge the two lists 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if ( !head )
            return ;
        // find middle 
        ListNode* slow = head, *fast = head;
        while( fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // reverse the second half starting from slow;
        ListNode *prev = nullptr, *curr = slow, *tmp;
        while(curr)
        {
            tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }

        ListNode *first = head, *second = prev;
        while( second->next )
        {
            tmp = first->next;
            first->next = second;
            first = tmp;
            tmp = second->next;
            second->next = first;
            second = tmp;
        }
    }
};