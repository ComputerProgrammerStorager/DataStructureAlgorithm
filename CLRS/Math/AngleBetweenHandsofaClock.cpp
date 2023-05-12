/*
Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.

Answers within 10-5 of the actual value will be accepted as correct.

 

Example 1:


Input: hour = 12, minutes = 30
Output: 165
Example 2:


Input: hour = 3, minutes = 30
Output: 75
Example 3:


Input: hour = 3, minutes = 15
Output: 7.5
 

Constraints:

1 <= hour <= 12
0 <= minutes <= 59

*/

// calulate the angle of hour and minutes relative to 12 position,  respectively 
class Solution {
public:
    double angleClock(int hour, int minutes) {
        double min_degree = 6 * minutes;
        double hour_degree = 30 * ((double)minutes/60) + (hour % 12) * 30;
        double res = abs(min_degree - hour_degree);
        
        return res > 180 ? 360 - res : res;
    }
};

// Python solution 
class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        min_degree = minutes * 6
        hr_degree = (hour + minutes / 60 ) * 30;
        diff = abs(min_degree - hr_degree)
        return min(diff,360-diff)