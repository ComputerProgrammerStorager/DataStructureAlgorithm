/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 

Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
 

Follow up:

If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
*/

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// Naive solution: sort the data elements every time right before find median is called
class MedianFinder {
    vector<int> q;
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        sort(q.begin(),q.end());
    }
    
    double findMedian() {
        q.insert(q.begin(),num);
        int sz = q.size();
        if (sz % 2 )
            return q[sz/2];
        return (double)(q[sz/2-1]+q[sz/2]) / 2;
    }
};

// Naive solution: we can maintain the elements sorted as we insert elements using insertion sort
class MedianFinder {
    vector<int> q;
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        q.insert(lower_bound(q.begin(),q.end(),num),num);
    }
    
    double findMedian() {
        int sz = q.size();
        if (sz % 2 )
            return q[sz/2];
        return (double)(q[sz/2-1]+q[sz/2]) / 2;
    }
};

// use two heaps to maintain the two respective halves with first heap being a max-heap and second heap being min-heap 
// when we insert a new number to the data structure, we need to perform the following steps in order to maintain the heaps sorted and balanced 
// (we allow the left first heap to have not more than one elements than the second head)
// 1. insert to first heap
// 2. move the top of the first heap to the second heap 
// 3. if the first size is less than the second, then move the top of second to the first 
// In doing we can maintain the new numbe in it's correct position
class MedianFinder {
    priority_queue<int> lo;         // max-heap using less as comparator
    priority_queue<int,vector<int>,greater<int>> hi;    // min-heap using greater as comparator
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top());
        lo.pop();
        if (lo.size() < hi.size()) 
        {
            lo.push(hi.top());
            hi.pop();
        }
    }
    
    double findMedian() {
        return lo.size() > hi.size() ? lo.top() : (double) (lo.top() + hi.top()) / 2;
    }
};


