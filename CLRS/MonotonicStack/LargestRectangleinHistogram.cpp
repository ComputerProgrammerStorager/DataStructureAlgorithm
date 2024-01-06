/*
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:


Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:


Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104
*/

// The problem is eqivalent to the ask: what is the max area if an element arr[m] is included in the max rectangle 
// To find the area, then we need to find the left smaller number and the right smaller number. Apparently, we can use monotonically increasing stack to help us get the lowers 
// A worthy note is when there are two consecutive same numbers, i.e., [..x1,x2..]. since when we pop out a number, meaning the right next number should not be included. 
// However, in this case x1 and x2 should be both included in the rectangle, it's simply because they can be a valid rectangle. 
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size(); 
        if ( n == 0 )
            return 0;
        stack<int> s;   // maintain a monotonic increasing stack 
        int area = 0;
        for ( int i = 0; i <= n; i++ )
        {
            while( !s.empty() && (i == n || heights[s.top()] > heights[i]) )
            {
                int val = heights[s.top()];
                s.pop();
                int l = s.empty() ? -1 : s.top();
                area = max(area,(i-l-1) * val);
            }
            s.push(i);
        }

        return area;
    }
};

// Divide and conquer
// for a range (l,r) with min_idx the minimum value, then the result is max of [l..min_idx-1], [l,r] and [min_idx+1,r].
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        return calculateArea(heights,0,heights.size()-1);
    }

private:
    int calculateArea(const vector<int>& heights, int l, int r)
    {
        if ( l > r )
            return 0;
        int min_idx = l;
        for ( int i = l+1; i <= r; i++ )
        {
            if (heights[i] < heights[min_idx])
                min_idx = i;
        }

        return max(heights[min_idx]*(r-l+1),max(calculateArea(heights,l,min_idx-1),calculateArea(heights,min_idx+1,r)));
    }
};