/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
*/

// Assume @row rows, then the pattern proceeds as following: 
//  0                            2*row-2 
//  1                   2*row-3  2*row  
//  ..           ...             2*row+1
//  row-2   row
//  row-1   

// Approach 1: simulate the filling process. for each repeatd pattern, we first go down for row nums, then go up for row - 2 nums... 
// repeat untill all nums are used 
class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> line(numRows);
        int n = s.size(), j = 0, curline=0;
        int verticle = numRows, diag = numRows-2;
        if (numRows == 1)
        return s;
        while (j < n)
        {
            for (int i = 0; i < numRows; i++)
            {
                if (j == n)
                    break;
                line[curline++].append(1,s[j++]);
            }
            curline -= 2;
            for (int i= 0; i < diag; i++)
            {
                if (j == n)
                    break;
                line[curline--].append(1,s[j++]);
            }
        }
        string res;
        for (auto l:line)
            res+=l;
        return res;
    }
};

// Approach 2: observe the pattern, for the first and the last rows, the distance is 2*row - 2. 
// for the remaing rows, we have another number between it and its next element in the next block.. 
// assume the row is i, than the second is 2*row - 2*i. As can be seen, increase i + by 1 would decreate i on the vertical side and another i on the diag side 
//      x
// i    x ---- >  x 
// i+1  .. ---> x
//      x 
//      x

class Solution {
public:
    string convert(string s, int numRows) {
        string res;
        int n = s.size(), batch_size = 2 * numRows - 2;
        if ( numRows == 1 )
            return s;
        for ( int row = 0; row < numRows; row++ ) {
            int idx = row;
            while( idx < n) {
                res.push_back(s[idx]);
                if ( row != 0 && row != numRows - 1 ) {
                    int second_idx = idx + batch_size - 2 * row;
                    if ( second_idx < n )
                        res.push_back(s[second_idx]);
                }
                idx += batch_size;
            }
        }

        return res;
    }
};