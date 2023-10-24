/*
A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

 

Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
 

Constraints:

0 <= n <= 1000
-104 <= Node.val <= 104
Node.random is null or is pointing to some node in the linked list.
*/


// Recursively check each and every node, clone its next and random 
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*,Node*> m;
        return helper(head,m);
    }

private:
    Node* helper(Node* node, unordered_map<Node*, Node*> &m)
    {
        if ( !node )
            return nullptr;
        if ( m.count(node) )
            return m[node];
        Node *new_node = new Node(node->val);
        m[node] = new_node;
        new_node->next = helper(node->next,m);
        new_node->random = helper(node->random,m);
        return new_node;
    }
};


// Use the same idea, but we can write it in iterative manner 
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if ( !head )
            return nullptr;
        Node *old_node = head;
        Node *new_node = new Node(head->val);
        m[old_node] = new_node;
        while(old_node)
        {
            new_node->next = getcloneNode(old_node->next);
            new_node->random = getcloneNode(old_node->random);
            old_node = old_node->next;
            new_node = new_node->next;
        }

        return m[head];
    }
private: 
    unordered_map<Node*,Node*> m;
    Node* getcloneNode(Node* node)
    {
        if ( node )
        {
            if ( m.count(node) )
                return m[node];
            return m[node] = new Node(node->val);
        }

        return nullptr;
    }
};

// We can also get rid of using additional space by creating next nodes first and then separate the two lists 
// 1. add the next nodes 
// 2. establish the random nodes 
// 3. separate the two lists 
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 1. add the next node 
        if ( !head )
            return nullptr;
        Node *tmp = head;
        while( tmp )
        {
            Node *newNode = new Node(tmp->val);
            newNode->next = tmp->next;
            tmp->next = newNode;
            tmp = newNode->next;
        }

        // 2. establish the random pointers
        tmp = head;
        while( tmp )
        {
            tmp->next->random = tmp->random ? tmp->random->next : nullptr;
            tmp = tmp->next->next;
        }

        // 3. split the two lists 
        Node* old_list = head;
        Node* new_list = head->next;
        Node* new_head = head->next;
        while(old_list)
        {
            old_list->next = old_list->next->next;
            new_list->next = new_list->next ?  new_list->next->next : nullptr;
            old_list = old_list->next;
            new_list = new_list->next;
        }
        return new_head;
    }
};