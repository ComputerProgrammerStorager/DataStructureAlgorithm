/*
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

Example 1:


Input: head = [1,2,3,4]
Output: [2,1,4,3]
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [1]
Output: [1]
 

Constraints:

The number of nodes in the list is in the range [0, 100].
0 <= Node.val <= 100

*/

// count the number of nodes first and then swap each pair 
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        int len = GetCount(head), n = len - len%2;
        if ( n < 2 )
            return head;
        ListNode dummy(0), *tail = &dummy;
        dummy.next = head;
        for ( int i = 0; i < n/2; i++ )
        {
            ListNode *third = tail->next->next->next;
            ListNode *second = tail->next->next;
            ListNode *first = tail->next;
            second->next = first;
            tail->next = second;
            first->next = third;
            tail = first;
        }
        
        return dummy.next;
    }
    int GetCount(ListNode *head)
    {
        int cnt = 0;
        while (head)
        {
            cnt++;
            head = head->next;
        }
        
        return cnt;
    }
};

// use recursive method to swap two nodes at a time 
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        return helper(head);
    }
    ListNode* helper(ListNode *head)
    {
        if ( head == nullptr || head->next == nullptr )
            return head;
        ListNode *newhead = head->next;
        ListNode *remaining = head->next->next;
        newhead->next = head;
        newhead->next->next = helper(remaining);
        return newhead;
    }
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        return helper(head);   
    }

    ListNode *helper(ListNode* node)
    {
        if ( !node || !node->next )
            return node;
        ListNode *tmp = node, *new_head = node->next, *new_next = node->next->next;
        new_head->next = tmp;
        tmp->next = helper(new_next);
        return new_head;
    }
};