/*
Write a function that reverses a string. The input string is given as an array of characters s.

 

Example 1:

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Example 2:

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
 

Constraints:

1 <= s.length <= 105
s[i] is a printable ascii character.
 

Follow up: Do not allocate extra space for another array. You must do this by modifying the input array in-place with O(1) extra memory.

*/

void reverseString(char* s, int sSize){
    for ( int i = 0; i < sSize/2; i++ )
    {
        char tmp = s[i];
        s[i] = s[sSize-1-i];
        s[sSize-1-i] = tmp;
    }
}


class Solution {
public:
    void reverseString(vector<char>& s) {
        int n = s.size();
        for ( int i = 0; i < n/2; i++ )
        {
            swap(s[i],s[n-1-i]);
        }
        
    }
};