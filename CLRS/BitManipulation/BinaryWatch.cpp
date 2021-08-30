/*
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.

For example, the below binary watch reads "4:51".


Given an integer turnedOn which represents the number of LEDs that are currently on, return all possible times the watch could represent. You may return the answer in any order.

The hour must not contain a leading zero.

For example, "01:00" is not valid. It should be "1:00".
The minute must be consist of two digits and may contain a leading zero.

For example, "10:2" is not valid. It should be "10:02".
 

Example 1:

Input: turnedOn = 1
Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
Example 2:

Input: turnedOn = 9
Output: []
 

Constraints:

0 <= turnedOn <= 10
*/

class Solution {
    
private:
    int countbitset(int val)
    {
        int cnt = 0;
        while ( val )
        {
            cnt++;
            val &= (val-1);
        }
        
        return cnt;
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> res;
        
        for (int h = 0; h <= 4 && h <= turnedOn; h++ )
        {
            vector<string> hours, mins;
            
            for( int val = 0; val < (1<<4); val++ )
                if ( countbitset(val) == h && val < 12 )
                    hours.push_back(to_string(val));
            
            for ( int val = 0; val < (1<<6); val++)
                if ( countbitset(val) == turnedOn-h && val < 60 )
                    mins.push_back(val < 10 ? "0"+to_string(val) : to_string(val));
            
            for ( auto h : hours )
            {
                
                for ( auto m : mins )
                    res.push_back(h+":"+m);
            }
 
        }
        
        return res;
    }
};


class Solution {
    
private:
    int countbitset(int val)
    {
        int cnt = 0;
        while ( val )
        {
            cnt++;
            val &= (val-1);
        }
        
        return cnt;
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> res;
        
        for ( int h = 0; h < 12; h++ )
            for (int m = 0; m < 60; m++ )
            {
                if ( countbitset(h) + countbitset(m) == turnedOn )
                {
                    res.push_back(to_string(h)+":"+ (m < 10 ? "0"+to_string(m) : to_string(m)));
                }
            }
                
        
        return res;
    }
};