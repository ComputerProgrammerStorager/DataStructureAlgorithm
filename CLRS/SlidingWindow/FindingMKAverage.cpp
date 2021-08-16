/*
You are given two integers, m and k, and a stream of integers. You are tasked to implement a data structure that calculates the MKAverage for the stream.

The MKAverage can be calculated using these steps:

If the number of the elements in the stream is less than m you should consider the MKAverage to be -1. Otherwise, copy the last m elements of the stream to a separate container.
Remove the smallest k elements and the largest k elements from the container.
Calculate the average value for the rest of the elements rounded down to the nearest integer.
Implement the MKAverage class:

MKAverage(int m, int k) Initializes the MKAverage object with an empty stream and the two integers m and k.
void addElement(int num) Inserts a new element num into the stream.
int calculateMKAverage() Calculates and returns the MKAverage for the current stream rounded down to the nearest integer.
 

Example 1:

Input
["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "addElement", "addElement", "calculateMKAverage"]
[[3, 1], [3], [1], [], [10], [], [5], [5], [5], []]
Output
[null, null, null, -1, null, 3, null, null, null, 5]

Explanation
MKAverage obj = new MKAverage(3, 1); 
obj.addElement(3);        // current elements are [3]
obj.addElement(1);        // current elements are [3,1]
obj.calculateMKAverage(); // return -1, because m = 3 and only 2 elements exist.
obj.addElement(10);       // current elements are [3,1,10]
obj.calculateMKAverage(); // The last 3 elements are [3,1,10].
                          // After removing smallest and largest 1 element the container will be [3].
                          // The average of [3] equals 3/1 = 3, return 3
obj.addElement(5);        // current elements are [3,1,10,5]
obj.addElement(5);        // current elements are [3,1,10,5,5]
obj.addElement(5);        // current elements are [3,1,10,5,5,5]
obj.calculateMKAverage(); // The last 3 elements are [5,5,5].
                          // After removing smallest and largest 1 element the container will be [5].
                          // The average of [5] equals 5/1 = 5, return 5
 

Constraints:

3 <= m <= 105
1 <= k*2 < m
1 <= num <= 105
At most 105 calls will be made to addElement and calculateMKAverage.

*/

#include "../Common/common_api.h"


// if the current number of element is less than m, then just push and if it reaches m after pushing the current element, then we need to divide the elements to left and right
// if it currently has m elements, then we first decide which multiset to insert he number and adjust the three sets
// then we delete the oldest element and adjust the three sets again 
// Note that: using queue to store the elements is more efficient than using vector. 
class MKAverage {
    int m, k;
    queue<int> q;
    long mid_sum;
    multiset<int> left,mid,right;
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
        mid_sum = 0;
    }
    
    void addElement(int num) {
        
        if ( q.size() < m )
        {   
            q.push(num);
            mid.insert(num);
            mid_sum += num;
            
            if( q.size() == m) 
            {           
                while ( left.size() < k )
                {
                    mid_sum -= *mid.begin();
                    shiftLeft(left,mid);
                }
                while ( right.size() < k )
                {
                    mid_sum -= *mid.rbegin();
                    shiftRight(mid,right);
                }
            }
        }
        else if ( q.size() == m )
        {
            q.push(num);
            // insert the new number to the three sets
            if ( !left.empty() && num <= *left.rbegin() )
                left.insert(num);
            else if ( !right.empty() && num >= *right.begin() )
                right.insert(num);
            else
            {
                mid_sum += num;
                mid.insert(num);
            }
            
            // adjust sizes
            if ( left.size() > k )
            {
                mid_sum += *left.rbegin();
                shiftRight(left,mid);
            }
                
            if ( right.size() > k )
            {
                mid_sum += *right.begin();
                shiftLeft(mid,right);
            }
            
            // remove the oldest number
            int num_del = q.front();
            q.pop();
            #if 1
            if ( num_del <= *left.rbegin())
                left.erase(left.find(num_del));
            else if ( num_del >= *right.begin())
                right.erase(right.find(num_del));
            else
            {
                mid_sum -= num_del;
                mid.erase(mid.find(num_del));
            }
            #endif
            
            #if 0
            if (left.find(num_del)!=left.end())
                left.erase(left.find(num_del));
            else if (right.find(num_del)!=right.end())
                right.erase(right.find(num_del));
            else
            {
                mid_sum -= num_del;
                mid.erase(mid.find(num_del));                
            }   
            #endif
    
            // adjust sizes
            if ( left.size() < k )
            {
                mid_sum -= *mid.begin();
                shiftLeft(left,mid);
            }
                
            if ( right.size() < k )
            {
                mid_sum -= *mid.rbegin();
                shiftRight(mid,right);
            }
        }
    }
    
    int calculateMKAverage() {
        if ( q.size() < m )
            return -1;
        return mid_sum / (mid.size());
    }
private:
    void shiftLeft(multiset<int> &left, multiset<int> &right)
    {
        left.insert(*right.begin());
        right.erase(right.begin());
    }
    
    void shiftRight(multiset<int> &left, multiset<int> &right)
    {
        right.insert(*left.rbegin());
        left.erase(prev(left.end()));
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
/*
["MKAverage","addElement","addElement","calculateMKAverage","addElement","addElement","calculateMKAverage","addElement","addElement","calculateMKAverage","addElement"]
[[3,1],[17612],[74607],[],[8272],[33433],[],[15456],[64938],[],[99741]]
*/
int main()
{
    MKAverage *obj = new MKAverage(3,1);
    obj->addElement(17612);
    obj->addElement(74607);
    obj->calculateMKAverage();
    obj->addElement(8272);
    obj->addElement(33433);
    obj->calculateMKAverage();
    obj->addElement(15456);
    obj->addElement(64938);
    obj->calculateMKAverage();
    obj->addElement(99741);
}