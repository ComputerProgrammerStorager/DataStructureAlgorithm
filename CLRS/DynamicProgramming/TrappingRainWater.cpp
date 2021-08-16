/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105

*/

// Brute force approach. 
// For the water trapped on each bar, we calculate the left_max and right_max (when calculating including itself, so min would be itself)
// then the water is min(left_max,right_max) - height
// O(n^2)
// O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, n = height.size();
        
        for ( int i = 0; i < n; i++ )
        {
            int left_max = 0, right_max = 0;
            for ( int l = 0; l <= i; l++ )
                left_max = max(left_max,height[l]);
            for ( int r = i; r < n; r++ )
                right_max = max(right_max,height[r]);
            ans += min(left_max,right_max) - height[i];
        }
        
        return ans;
    }
};

// we could improve a bit over the above solution by storing the left_max and right_max
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        vector<int> left_max(n), right_max(n);
        if ( n == 0 )
            return ans;
        left_max[0] = height[0];
        right_max[n-1] = height[n-1];

        for ( int i = 1; i < n; i++ )
            left_max[i] = max(left_max[i-1],height[i]);
        for ( int i = n-2; i >= 0; i-- )
            right_max[i] = max(right_max[i+1],height[i]);
        
        for ( int i = 0; i < n; i++ )
            ans += min(left_max[i],right_max[i]) - height[i];
        
        return ans;
    }
};

// we can use a stack to maintain the left max so-far and calculate the top water if the current height is higher than top 

class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> s;
        int current = 0, ans = 0;
        while ( current < height.size() )
        {
            while ( !s.empty() && height[s.top()] < height[current] )
            {
                int top = s.top();
                s.pop();
                if ( s.empty() )
                    break;
                int width = current - s.top() - 1;
                int h = min(height[current],height[s.top()]) - height[top];
                ans += width * h ;
            }
            
            s.push(current++);
        }
        
        return ans;
    }
};

// use two pointers to calculate the water trapped on the current bar 
// we get rid of the shorter bar first and move it 
// if it's a new higher height, we just discard the current bar
// otherwith add the water trapped by the current bar
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left_max = 0, right_max = 0;
        int left = 0, right = height.size() - 1;
        while ( left < right )
        {
            if ( height[left] <= height[right] )
            {
                if (height[left] >= left_max )
                {
                    left_max = height[left];
                }
                else 
                {
                    ans += left_max - height[left];
                }
                left++;
            }
            
            else
            {
                if ( height[right] >= right_max )
                {
                    right_max = height[right];
                }
                else 
                {
                    ans += right_max - height[right];
                }
                
                right--;
            }
        }
        return ans;
    }
};