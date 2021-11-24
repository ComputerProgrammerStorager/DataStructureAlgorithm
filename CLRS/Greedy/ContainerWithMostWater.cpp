/*
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

Notice that you may not slant the container.

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
Example 3:

Input: height = [4,3,2,1,4]
Output: 16
Example 4:

Input: height = [1,2,1]
Output: 2
 

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104

*/

// This is a classical problem that combines two pointer technique with gready idea 
// We know that the container volume is determined by both its height and width. Then if we start from a max width, then we 
// can only expect to increase the volume by increasing the height, while we are reducing the width. Therefore: 
// 1. We start with the max width, i.e., using the first and last lines as its boundary lines. 
// 2. Then we move the smaller end util it encounters a taller line (to expectantly find a larger volume) or meets the other end (i.e., terminate). 
//    The reason is because if we move the larger end, then we only decrease the volume relative to the current volume. The bucket water theory. 
// 3. If the current two ends are the same, then we can move both of them. 

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int max_area = min(height[left],height[right]) * (right-left);
        while( left < right )
        {
            int mn_end = min(height[left],height[right]);
            if ( height[left] < height[right] )
            {
                int new_left = left+1;
                while( new_left < right && height[new_left] <= mn_end )
                    new_left++;
                max_area = max(max_area, min(height[new_left],height[right]) * (right-new_left) );
                left = new_left;
            }
            else if ( height[left] > height[right] )
            {
                int new_right = right - 1;
                while( new_right > left && height[new_right] <= mn_end )
                    new_right--;
                max_area = max(max_area, min(height[left],height[new_right]) * (new_right-left) );
                right = new_right;
            }
            else
            {
                left++;
                right--;
                max_area = max(max_area, min(height[left],height[right]) * (right-left) );
            }
        }
        
        return max_area;
    }
};

// of course, we can write it in a more concise manner 
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int max_area = 0;
        while( l < r )
        {
            max_area = max(max_area,min(height[l],height[r]) * (r-l));
            if ( height[l] < height[r] )
                l++;
            else if ( height[l] > height[r] )
                r--;
            else 
            {
                l++;
                r--;
            }
        }
        
        return max_area;
    }
};

// And of course, there is always an O(n^2) brute force solution 
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0, n = height.size();
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = i+1; j < n; j++ )
            {
                max_area = max(max_area, min(height[i],height[j])*(j-i));
            }
        }
        
        return max_area;
    }
};