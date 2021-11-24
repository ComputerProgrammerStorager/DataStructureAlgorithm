/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.

 

Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 

Follow up: Could you do this in one pass?

*/

// We count the total number of nodes(denoted as nodes), then the rank of the node prior to the node to be deleted is (nodes-n)
// Then we find the previous node and set skipping its next node
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int nodes = CountNodes(head);
        int prev = nodes - n;
        if ( n == 0 || n > nodes )
            return head;
        ListNode *prev_node = findnth(head,prev);
        
        if ( !prev_node )
            return head->next;
        prev_node->next = prev_node->next->next;
        return head;
    }
    
private: 
    int CountNodes( ListNode *head )
    {
        int cnt = 0;
        while(head)
        {
            cnt++;
            head = head->next;
        }
        
        return cnt;
    }
    // 1 based 
    ListNode* findnth( ListNode* head, int n) 
    {
        int cnt = 0;
        while( head )
        {
            cnt++;
            if ( cnt == n )
            {
                return head;
            }
            head = head->next;
        }
        return nullptr;
    }
};

// we can use a stack to help tracking the nodes 
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int nodes = 0;
        stack<ListNode*> st;
        ListNode *tmp = head, *newhead = nullptr;
        while(tmp)
        {
            st.push(tmp);
            tmp = tmp->next;
            nodes++;
        }
        if ( n == 0 || n > nodes )
            return head;
        nodes = 0;
        while(!st.empty())
        {
            nodes++;
            ListNode *cur = st.top();
            st.pop();
            if ( nodes != n )
            {
                cur->next = newhead;
                newhead = cur;
            }
        }
        
        return newhead;
    }
};

// we can spend just one pass by maintaing two parts whose distance is n nodes. Then when the first pointer reaches the end, 
// the later second points is right pointing to the node prior to the node to be deleted. 
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *first = &dummy, *second = &dummy;
        for ( int i = 0; i <= n; i++ )
            first = first->next;
        while( first )
        {
            first = first->next;
            second = second->next;
        }
        
        second->next = second->next->next;
        return dummy.next;
    }
};