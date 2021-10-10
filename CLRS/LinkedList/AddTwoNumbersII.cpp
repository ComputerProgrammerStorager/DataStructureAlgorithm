/*
You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

Example 1:


Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Example 2:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
Example 3:

Input: l1 = [0], l2 = [0]
Output: [0]
 

Constraints:

The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.


*/

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

// Use stack to do the addition from the tail first 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode*> st1, st2;
        ListNode dummy(-1);
        int carry = 0;
        while( l1 )
        {
            st1.push(l1);
            l1 = l1->next;
        }
        
        while( l2 )
        {
            st2.push(l2);
            l2 = l2->next;
        }
        
        while( !st1.empty() && !st2.empty() )
        {
            l1 = st1.top();
            l2 = st2.top();
            st1.pop();
            st2.pop();
            int sum = l1->val + l2->val + carry;
            carry = sum / 10;
            l1->val = sum % 10;
            delete l2;
            l1->next = dummy.next;
            dummy.next = l1;
        }
        
        while( !st1.empty() ) 
        {
            l1 = st1.top();
            st1.pop();
            int sum = l1->val + carry;
            l1->val = sum % 10;
            carry = sum / 10;
            l1->next = dummy.next;
            dummy.next = l1;
        }
        
        while( !st2.empty() )
        {
            l2 = st2.top();
            st2.pop();
            int sum = l2->val + carry;
            l2->val = sum % 10;
            carry = sum / 10;
            l2->next = dummy.next;
            dummy.next = l2;
        }
        
        if ( carry )
        {
            ListNode *tmp = new ListNode(carry);
            tmp->next = dummy.next;
            dummy.next = tmp;
        }
        
        return dummy.next;
    }
};


// can also go without extra space by reversing the lists first 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;
        l1 = reverselist(l1);
        l2 = reverselist(l2);
        int carry = 0;
        while ( l1 || l2 )
        {
            int a = l1? l1->val : 0;
            int b = l2? l2->val : 0;
            int sum = a+b+carry;
            carry = sum / 10;
            ListNode *node = new ListNode(sum%10);
            node->next = head;
            head = node;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        
        if ( carry )
        {
            ListNode *node = new ListNode(carry);
            node->next = head;
            head = node;
        }
        
        return head;
    }
    
    ListNode *reverselist(ListNode* head)
    {
        ListNode dummy(-1);
        while(head)
        {
            ListNode *next = head->next;
            head->next = dummy.next;
            dummy.next = head;
            head = next;
        }
        
        return dummy.next;
    }
};