/*
Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane, return true if these points are a boomerang.

A boomerang is a set of three points that are all distinct and not in a straight line.

 

Example 1:

Input: points = [[1,1],[2,3],[3,2]]
Output: true
Example 2:

Input: points = [[1,1],[2,2],[3,3]]
Output: false
 

Constraints:

points.length == 3
points[i].length == 2
0 <= xi, yi <= 100


*/

// check the slope. To unify the handling of slope1 == slope2 and slope1 == -slope2, we can sort the points first 
// But before we calculate the slope, we need to avoid dividing by zero case. 
// Also, we need to cast the slope to double in order to avoid rounding down errors. 
class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        if ( points[0] == points[1] || points[1] == points[2] || points[0] == points[2] )
            return false;
        auto cmp = [](vector<int> const& p1, vector<int> p2) {
            if ( p1[0] < p2[0] || (p1[0] == p2[0] && p1[1] < p2[1] ) )
                return true;    
            return false;
        };
        sort(points.begin(),points.end(),cmp);
        if ( points[0][0] == points[1][0] )
        {
            if ( points[1][0] == points[2][0] )
                return false;
            return true;
        }
        
        if ( (double)(points[1][1] - points[0][1])/(points[1][0] - points[0][0]) == double(points[2][1] - points[0][1]) / (points[2][0] - points[0][0]) )
            return false;
        return true;
        
    }
};

// altervatively and simpler, still using the slope relationship, but avoiding division 
class Solution {
public:
    bool isBoomerang(vector<vector<int>>& p) {
        return (p[0][0] - p[1][0]) * (p[0][1] - p[2][1]) != (p[0][0] - p[2][0]) * (p[0][1] - p[1][1]);
        
    }
};