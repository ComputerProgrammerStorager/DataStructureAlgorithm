/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:

-231 <= val <= 231 - 1
*/

// Method 1: maintain a current min value corresponding to the current top 
class MinStack {
private:
    stack<pair<int,int>> s;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        int new_min = s.empty() ? val : min(s.top().second,val);
        s.push({val,new_min});
    }
    
    void pop() {
        s.pop();
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

// Method 2: use two stacks 
class MinStack {
private:
    stack<int> data;
    stack<pair<int,int>> mins;  // cur_min and frequence 
public:
    MinStack() {
        
    }
    
    void push(int val) {
        data.push(val);
        if ( mins.empty())
        {
            mins.push({val,1});
        }
        else 
        {
            auto cur_min = mins.top();
            if ( cur_min.first > val )
            {
                mins.push({val,1});
            }
            else if ( cur_min.first == val )
            {
                mins.pop();
                mins.push({val,cur_min.second+1});
            }
        }
    }
    
    void pop() {
        int pop_val = data.top();
        data.pop();
        auto min_val = mins.top();
        if ( min_val.first == pop_val )
        {
            mins.pop();
            if ( min_val.second > 1 )
            {
                mins.push({min_val.first,min_val.second-1});
            }
        }
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return mins.top().first;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */