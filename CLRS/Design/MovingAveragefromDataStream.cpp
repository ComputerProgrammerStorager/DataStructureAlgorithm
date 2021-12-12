/*
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Implement the MovingAverage class:

MovingAverage(int size) Initializes the object with the size of the window size.
double next(int val) Returns the moving average of the last size values of the stream.
 

Example 1:

Input
["MovingAverage", "next", "next", "next", "next"]
[[3], [1], [10], [3], [5]]
Output
[null, 1.0, 5.5, 4.66667, 6.0]

Explanation
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // return 1.0 = 1 / 1
movingAverage.next(10); // return 5.5 = (1 + 10) / 2
movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3
 

Constraints:

1 <= size <= 1000
-105 <= val <= 105
At most 104 calls will be made to next.

*/

// we can design and use our own circular queue based on array for the purpose. 
// Note there are a lot of relaxed checks given the circular buffer is only internally used 
class MovingAverage {
private: 
    vector<int> data;
    int head, tail, cap, load;
    long sum;
    bool isFull()
    {
        return ((tail+1) % cap) == head;
    }
    bool isEmpty()
    {
        return head == -1;
    }
    
    int front()
    {
        return data[head];
    }

    void enqueue(int val)
    {
        if ( isFull() )
        {
            sum -= front();
            load--;
            dequeue();
        }
        if( isEmpty() )
        {
            head = 0;
        }
        tail = (tail+1) % cap;
        data[tail] = val;
        sum += val;
        load++;
    }
    
    void dequeue()
    {
        head = (head+1) % cap;
    }
public:
    MovingAverage(int size) {
        data.resize(size);
        cap = size;
        head = -1;
        tail = -1;
        load = 0;
        sum = 0;
    }
    
    double next(int val) {
        enqueue(val);
        return (double) sum / load;
    }
};

// if allowed to use the built-in queue, we don't need to reinvent the wheel
class MovingAverage {
    queue<int> q;
    int sz;
    long sum;
public:
    MovingAverage(int size) {
        sz = size;
        sum = 0;
    }
    
    double next(int val) {
        if ( q.size() == sz )
        {
            sum -= q.front();
            q.pop();
        }
        q.push(val);
        sum += val;
        return (double) sum / q.size();
    }
};