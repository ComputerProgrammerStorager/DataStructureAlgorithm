/*
Your friend is typing his name into a keyboard. Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.

You examine the typed characters of the keyboard. Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.

 

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.
Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed output.
Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true
Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.
 

Constraints:

1 <= name.length <= 1000
1 <= typed.length <= 1000
name and typed contain only lowercase English letters.

*/

// we can check the number of consecutive chars for each char and if the number in typed should not be less than in the name 
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while( i < name.size() && j < typed.size() )
        {
            if ( name[i] != typed[j] )
                return false;
            int cnt1 = 1, cnt2 = 1, pos;
            pos = i+1;
            while( pos < name.size() && name[pos] == name[i] )
            {
                pos++;
                cnt1++;
            }
            pos = j+1;
            while(pos < typed.size() && typed[pos] == typed[j] )
            {
                pos++;
                cnt2++;
            }
            
            if ( cnt2 < cnt1 )
                return false;
            i += cnt1;
            j += cnt2;
        }
        return i == name.size() && j == typed.size();
    }
};

// we can compare one by one and if not equal, we look back at typed to check if it is the same as its preceding 
// if we typed is name is not consumed, it return false, and if typed has not been consumed, then the redundant chars must 
// be the same as the last one due to long pressing 
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while( i < name.size() && j < typed.size() )
        {
            if ( name[i] == typed[j] )
            {
                i++;
                j++;
            }
            else 
            {
                if ( j > 0 && typed[j] == typed[j-1] )
                {
                    j++;
                }
                else 
                    return false;
            }
        }
        
        while( j < typed.size() )
        {
            if ( typed[j] != typed[j-1] )
                return false;
            j++;
        }
        
        return i == name.size();
    }
};