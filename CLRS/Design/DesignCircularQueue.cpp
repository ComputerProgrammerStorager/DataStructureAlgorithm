/*
Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implementation the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
You must solve the problem without using the built-in queue data structure in your programming language. 

 

Example 1:

Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]

Explanation
MyCircularQueue myCircularQueue = new MyCircularQueue(3);
myCircularQueue.enQueue(1); // return True
myCircularQueue.enQueue(2); // return True
myCircularQueue.enQueue(3); // return True
myCircularQueue.enQueue(4); // return False
myCircularQueue.Rear();     // return 3
myCircularQueue.isFull();   // return True
myCircularQueue.deQueue();  // return True
myCircularQueue.enQueue(4); // return True
myCircularQueue.Rear();     // return 4
 

Constraints:

1 <= k <= 1000
0 <= value <= 1000
At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.

*/

// it's much easy to keep the size info 
class MyCircularQueue {
private:
    vector<int> data;
    int capacity;
    int size;
    int head;
    int tail;
public:
    MyCircularQueue(int k) {
        capacity = k;
        data.resize(capacity);
        size = 0;
        head = 0;
        tail = -1;
    }
    
    bool enQueue(int value) {
        if ( size == capacity )
            return false;
        tail = (tail+1) % (capacity);
        data[tail] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if ( size == 0 )
            return false;
        head = (head+1) % (capacity);
        size--;
        return true;
    }
    
    int Front() {
        if ( isEmpty() )
            return -1;
        return data[head];
    }
    
    int Rear() {
        if ( isEmpty() )
            return -1;
        return data[tail];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

// if we don't record the current size of the queue, then it's much convenient to have one additional unused space to distinguish the 
// the cases of being full and empty such that when head == tail indicates empty, while (tail+1) % (cap+1) == head indicates full. 
// Invariant: tail always points to the next unfilled position 
class MyCircularQueue {
private:
    vector<int> data;
    int cap;
    int head;
    int tail;
public:
    MyCircularQueue(int k) {
        cap = k;
        data.resize(cap+1);
        head = 0;
        tail = 0;
    }
    
    bool enQueue(int value) {
        if ( isFull() )
            return false;
        data[tail] = value;
        tail = (tail+1) % (cap+1);
        return true;
    }
    
    bool deQueue() {
        if ( isEmpty() )
            return false;
        head = (head+1) % (cap+1);
        return true;
    }
    
    int Front() {
        if ( isEmpty() )
            return -1;
        return data[head];
    }
    
    int Rear() {
        if ( isEmpty() )
            return -1;
        return data[(tail+cap)%(cap+1)];        // because tail pionts to the next unfill position, so the tail is (tail-1+cap+1) % (cap+1), i.e., (tail+cap) % (cap+1). 
    }
    
    bool isEmpty() {
        return tail == head;
    }
    
    bool isFull() {
        return (tail+1) % (cap+1) == head;
    }
};

// The key point is to distinguish if head == tail represents one-size or empty situation 
// we can set head = -1 to indicate empty case and whenev
class MyCircularQueue {
private:
    vector<int> data;
    int head, tail, cap;
public:
    MyCircularQueue(int k) {
        cap = k;
        data.resize(k);
        head = -1;
        tail = -1;
    }
    
    bool enQueue(int value) {
        if ( isFull() )
            return false;
        if ( isEmpty() )
        {
            head = 0;
        }
        tail = (tail+1)%cap;
        data[tail] = value;
        return true;
    }
    
    bool deQueue() {
        if ( isEmpty() )
            return false;
        if ( head == tail )
        {
            head = -1;
            tail = -1;
        }
        else
        {
            head = (head+1) % cap;
        }
        return true;
    }
    
    int Front() {
        if ( isEmpty() )
            return -1;
        return data[head];
    }
    
    int Rear() {
        if ( isEmpty() )
            return -1;
        return data[tail];
    }
    
    bool isEmpty() {
        return head == -1;
    }
    
    bool isFull() {
        return ((tail+1) % cap) == head;
    }
};
