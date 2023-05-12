/*

Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

The first node is considered odd, and the second node is even, and so on.

Note that the relative order inside both the even and odd groups should remain as it was in the input.

You must solve the problem in O(1) extra space complexity and O(n) time complexity.

 

Example 1:


Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]
Example 2:


Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]
 

Constraints:

The number of nodes in the linked list is in the range [0, 104].
-106 <= Node.val <= 106
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

// maint two seperate odd and even linked lists 
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd_dummy(0), even_dummy(0), *odd_tail = &odd_dummy, *even_tail = &even_dummy;
        bool cur_odd = true;
        while( head )
        {
            ListNode *next = head->next;
            if ( cur_odd )
            {
                head->next = odd_tail->next;
                odd_tail->next = head;
                odd_tail = head;
            }
            else 
            {
                head->next = even_tail->next;
                even_tail->next = head;
                even_tail = head;
            }
            cur_odd = !cur_odd;
            head = next;
        }

        odd_tail->next = even_dummy.next;
        return odd_dummy.next;
    }
};

// alternatively we can massage the list nodes in place 
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
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd_dummy(0), even_dummy(0), *odd_tail = &odd_dummy, *even_tail = &even_dummy;
        bool cur_odd = true;
        while( head )
        {
            ListNode *next = head->next;
            if ( cur_odd )
            {
                head->next = odd_tail->next;
                odd_tail->next = head;
                odd_tail = head;
            }
            else 
            {
                head->next = even_tail->next;
                even_tail->next = head;
                even_tail = head;
            }
            cur_odd = !cur_odd;
            head = next;
        }

        odd_tail->next = even_dummy.next;
        return odd_dummy.next;
    }
};