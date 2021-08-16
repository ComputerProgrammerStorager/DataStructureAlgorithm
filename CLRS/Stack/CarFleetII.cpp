/*
There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:

positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
speedi is the initial speed of the ith car in meters per second.
For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.

Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.

 

Example 1:

Input: cars = [[1,2],[2,1],[4,3],[7,2]]
Output: [1.00000,-1.00000,3.00000,-1.00000]
Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
Example 2:

Input: cars = [[3,4],[5,4],[6,3],[9,1]]
Output: [2.00000,1.00000,1.50000,-1.00000]
*/

// process the rightmost car first and use a stack to process the colliding cars. If the current car is slower or equal to the top or it takes longer than the top car's colliding time
// then keep popping out the cars 
class Solution {
    typedef array<double,3> COLLIDEINFO;
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> res(n,-1);
        constexpr double double_max = std::numeric_limits<double>::max();
        if ( n <= 1 )
            return res;
        stack<COLLIDEINFO> s;
        s.push({double_max,(double)cars[n-1][0],(double)cars[n-1][1]});
        for ( int i = n - 2; i >= 0; i-- )
        {   
            int cur_pos = cars[i][0];
            int cur_sp = cars[i][1];
            while ( !s.empty() && (cur_sp <= s.top()[2] || (s.top()[1] - cur_pos)/(cur_sp-s.top()[2]) >= s.top()[0] ) )
                s.pop();
            if ( s.empty() )
            {
                s.push({std::numeric_limits<double>::max(),(double)cur_pos,(double)cur_sp});
            }
            else 
            {
                double cur_collide_time = (s.top()[1] - cur_pos)/(cur_sp-s.top()[2]);
                s.push({cur_collide_time,(double)cur_pos,(double)cur_sp});
                res[i] = cur_collide_time;
            }
        }
        return res;
    }
};