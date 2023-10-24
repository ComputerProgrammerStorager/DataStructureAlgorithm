/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Follow up:
Could you do get and put in O(1) time complexity?

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.
*/

// use a map to facilitating find the position in a lru list 

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if ( it == m.end() )
            return -1;
        l.splice(l.begin(),l,it->second);
        return it->second->second;
        
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if ( it != m.end() )
            l.erase(it->second);
        l.push_front(make_pair(key,value));
        m[key] = l.begin();
        if ( m.size() > cap )
        {
            m.erase(l.rbegin()->first);
            l.pop_back();
        }
    }
    
private:
    unordered_map<int,list<pair<int,int>>::iterator> m;
    list<pair<int,int>> l;
    int cap;
};


// We can build our own doubly linked list 
struct Node {
    int val;
    int key;
    Node *next, *prev;
    Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
};

class LRUCache {
private:
    int cap;
    unordered_map<int,Node*> dict;
    Node *head = new Node(-1,-1);
    Node *tail = new Node(-1,-1);
    void removeNode(Node *node)
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    void addNode(Node *node)
    {
        Node *prevEnd = tail->prev;
        prevEnd->next = node;
        node->prev = prevEnd;
        node->next = tail;
        tail->prev = node;
    }
public:
    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if ( dict.find(key) == dict.end() )
            return -1;
        Node *node = dict[key];
        removeNode(node);
        addNode(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if ( dict.find(key) != dict.end() )
        {
            removeNode(dict[key]);
        }

        Node *node = new Node(key,value);
        dict[key] = node;
        addNode(node);
        if ( dict.size() > cap )
        {
            Node *todelete = head->next;
            dict.erase(todelete->key);
            removeNode(todelete);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */