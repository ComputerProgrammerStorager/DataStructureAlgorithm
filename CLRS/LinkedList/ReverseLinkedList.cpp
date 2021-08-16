/*
Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

// recurison version 
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if ( head == nullptr || head->next == nullptr )
            return head;
        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newhead;
    }
};

// iterative version
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(-1);
        dummy.next = head;
        while ( head && head->next )
        {
            ListNode *tmp = head->next;
            head->next = tmp->next;
            tmp->next = dummy.next;
            dummy.next = tmp;
        }
        return dummy.next;
    }
};