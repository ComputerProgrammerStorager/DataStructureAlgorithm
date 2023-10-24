/*
Given the head of a linked list, return the list after sorting it in ascending order.

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
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


// Insertion sort: O(n^2)
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
    ListNode* sortList(ListNode* head) {
        ListNode* new_head = nullptr;
        while(head)
        {
            ListNode* remaining = head->next;
            head->next = nullptr;
            if ( new_head == nullptr )
            {
                new_head = head;
            }
            else {
                ListNode* walk = new_head, *prev = nullptr;
                while(walk && walk->val < head->val)
                {
                    prev = walk;
                    walk = walk->next;
                }
                head->next = walk;
                if ( prev == nullptr )
                    new_head = head;
                else 
                    prev->next = head;

            }
            head = remaining;
        }

        return new_head;
    }
};

// Merge sort: divide and conquer 
// Top-down merge sort: O(lgn) stack space
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if ( !head || !head->next )
            return head;
        ListNode *mid = getMid(head);
        ListNode *first = sortList(head);
        ListNode *second = sortList(mid);
        return merge(first,second);
    }
    
    ListNode *getMid( ListNode *head )
    {
        ListNode *midPrev = nullptr;
        while ( head && head->next )
        {
            midPrev = midPrev == nullptr ? head : midPrev->next;
            head = head->next->next;
        }
        
        ListNode *mid = midPrev->next;
        midPrev->next = nullptr;
        return mid;
    }  
    
    ListNode *merge(ListNode *l1, ListNode *l2) 
    {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
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
        if ( l1 )
            tail->next = l1;
        else 
            tail->next = l2;
        return dummy.next;
    }
};

// bottom-up: merge sort O(1) space 
class Solution {
    ListNode *tail = new ListNode();
    ListNode *nextSubList = new ListNode();
    
public:
    ListNode* sortList(ListNode* head) {
        if ( !head || !head->next )
            return head;
        int n = getCount(head);
        ListNode *start = head;
        ListNode dummyHead(0);
        for ( int len = 1; len < n; len *= 2 )
        {
            tail = &dummyHead;
            while(start)
            {
                if ( !start->next ){
                    tail->next = start;
                    break;
                }
                ListNode *mid = split(start,len);
                merge(start,mid);
                start = nextSubList;
            }
            start = dummyHead.next;
        }
        return dummyHead.next;
    }
    
    ListNode *split(ListNode *start, int len )
    {
        ListNode *midPrev = start;
        ListNode *end = start->next;
        // use fast and slow approach to find middle and end of second linked list 
        for ( int idx = 1; idx < len && (midPrev->next || end->next); idx++ )
        {
            if ( end->next ) {
                end = (end->next->next) ? end->next->next : end->next;
            }
            if ( midPrev->next )
            {
                midPrev = midPrev->next;
            }
        }
        ListNode *mid = midPrev->next;
        nextSubList = end->next;
        midPrev->next = nullptr;
        end->next = nullptr;
        // return the start of the second linked list 
        return mid;
    }
    
    // 
    void merge(ListNode *l1, ListNode *l2 )
    {
        ListNode dummyHead(0);
        ListNode *newTail = &dummyHead;
        while ( l1 && l2 )
        {
            if ( l1->val < l2->val )
            {
                newTail->next = l1;
                l1 = l1->next;
            }
            else 
            {
                newTail->next = l2;
                l2 = l2->next;
            }
            newTail = newTail->next;
        }
        
        newTail->next = (l1) ? l1 : l2;
        while ( newTail->next )
        {
            newTail = newTail->next;
        }
        tail->next = dummyHead.next;
        tail = newTail;
    }
    
    int getCount( ListNode *head )
    {
        int cnt = 0;
        while( head )
        {
            cnt++;
            head = head->next;
        }
        
        return cnt;
    }
};