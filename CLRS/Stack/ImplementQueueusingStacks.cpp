/*
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
 

Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.
 

Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.

*/

// Method one: 
// s1 is used to store all elements, and s2 is used to help maintain the queue property in s1 
// i.e., bottom of s1 is the rear of queue and top of s1 is front of s1. In such case, 
// for each push, existing elements in s1 have to be popped to s2, and then push the new element to s1 and then push them back to s1. 
// Push: O(n)
// peek: O(1) check the top of s1
// pop: O(1) pop from s1 
// empty: O(1) check s1 empty 

class MyQueue {
private: 
    stack<int> s1;
    stack<int> s2;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        while( !s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }

        s1.push(x);
        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    int pop() {
        int val = s1.top();
        s1.pop();
        return val;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

/*
Method 2: s1 and s2 share all the elements, where s1 stores part of queue rear element in reverse order, i.e., bottom is front side and top is rear direction 
and s2 store part of the queue front elements in queue order, i.e., bottom is the rear and top is the front 

The transfer from s1 to s2 only happens when a pop operation is requested and s2 is empty
push: just push to s1 and thus O(1)
pop: if s2 is not empty, return top; otherwise move s1 to s2.. amortized O(1) 
peek: if s2 is not empty, return s2.top, otherwise, return front
*/

class MyQueue {
private:
    stack<int> s1;
    stack<int> s2;
    int front; // front in the s1 part (s1 stores elements in reverse order)
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        if ( s1.empty() )
            front = x;
        s1.push(x);
    }
    
    int pop() {
        if ( s2.empty())
        {
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }

        int val = s2.top();
        s2.pop();
        return val;
    }
    
    int peek() {
        if ( !s2.empty() ) 
            return s2.top();
        return front;
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */