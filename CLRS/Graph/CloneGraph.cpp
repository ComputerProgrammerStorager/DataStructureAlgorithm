/*
Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}
 

Test case format:

For simplicity sake, each node's value is the same as the node's index (1-indexed). For example, the first node with val = 1, the second node with val = 2, and so on. The graph is represented in the test case using an adjacency list.

Adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.

 
*/

// DFS
class Solution {
public:
    Node* cloneGraph(Node* node) {      
        unordered_map<Node*,Node*> pair;
        return helper(node,pair);
    }
    
    Node *helper(Node *node, unordered_map<Node*, Node*> &pair)
    {
        if ( !node )
            return node;
        if ( pair.count(node) )
            return pair[node];
        Node *cloneNode = new Node(node->val);
        pair[node] = cloneNode;
        for ( auto n : node->neighbors )
        {
            cloneNode->neighbors.push_back(helper(n,pair));
        }
        
        return cloneNode;
    }
};

//BFS
class Solution {
public:
    Node* cloneGraph(Node* node) {      
        unordered_map<Node *, Node*> pair;
        queue<Node*> q{{node}};
        if ( !node )
            return nullptr;
        Node *clone = new Node(node->val);
        pair[node] = clone;
        while( !q.empty() )
        {
            Node *t = q.front();
            q.pop();
            for ( auto n : t->neighbors )
            {
                if ( !pair.count(n) )
                {
                    pair[n] = new Node(n->val);
                    q.push(n);
                }
                pair[t]->neighbors.push_back(pair[n]);
            }
        }   
        return clone;
    }
};