/*
Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
*/

// need to keep track of the previous nodes of the node to be changed 
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev = &dummy; 
        int i = 0;
        while ( i++ < m-1 ) 
        {
            prev = prev->next;
            head = head->next;
        }

        ListNode *tmp = head->next;
        while ( tmp && i++ < n)
        {
            head->next = tmp->next;
            tmp->next = prev->next;
            prev->next = tmp;
            tmp = head->next;
        }
        
        return dummy.next;
    }
};

// concise version 
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *prev = &dummy;
        for ( int i = 0; i < m - 1; i++ )
            prev = prev->next;
        ListNode *cur = prev->next;
        for ( int i = m; i < n; i++ )
        {
            ListNode *tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = prev->next;
            prev->next = tmp;
        }
        
        return dummy.next;
    }
};