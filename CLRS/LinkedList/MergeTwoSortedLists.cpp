/*
Merge two sorted linked lists and return it as a sorted list. The list should be made by splicing together the nodes of the first two lists.
*/

// iterative solution 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1), *tail = &dummy;
        while ( l1 && l2 )
        {
            if ( l1->val < l2->val )
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else 
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

// Recursive solution 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if ( !l1 )
            return l2;
        if ( !l2 )
            return l1;
        if ( l1->val < l2->val )
        {
            l1->next = mergeTwoLists(l1->next,l2);
            return l1;
        }
        else 
        {
            l2->next = mergeTwoLists(l1,l2->next);
            return l2;
        }
    }
};