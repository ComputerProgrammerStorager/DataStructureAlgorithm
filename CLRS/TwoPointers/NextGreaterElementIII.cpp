/*
Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.

Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.

 

Example 1:

Input: n = 12
Output: 21
Example 2:

Input: n = 21
Output: -1
 

Constraints:

1 <= n <= 2^31 - 1
*/
#include <string> 
#include <iostream>
using namespace std;
int main()
{
    int n = 1234;
    std::string val = std::to_string(n);
    int len = val.size();
    cout << val << "  " << len << endl;
    cout << val[0] << " " << val[3] << endl;
    return 0;
}

// Though process: given number[n1,n2,n3] as a string. Note n1 is idx 0, and n2 is idx 1, and so on 
// The next larger number will be swapping the first digit that breaks an increase trend from the right side with the smallest larger digit to its right side
// Step 1: find the inflection idx starting from the right side such that n[pivot_idx] > n[pivot_idx-1] 
// Step 2: swap all digits between [pivot_idx, end]
// Step 3: find the first digit that is larger than n[pivot_idx-1] and swap it with n[pivot_idx-1]

class Solution {
public:
    int nextGreaterElement(int n) {
        string val = to_string(n);
        int len = val.size(), pivot_idx = len -1;
        while(pivot_idx > 0)
        {
            if ( val[pivot_idx-1] < val[pivot_idx] )
                bre
            pivot_idx--;
        }

        if ( pivot_idx == 0 )
            return -1;
        reverse(val.begin()+pivot_idx, val.end());
        int j = pivot_idx - 1;
        while( pivot_idx < len)
        {
            if ( val[pivot_idx] > val[j] )
            {
                swap(val[pivot_idx], val[j]);
                break;
            }
            pivot_idx++;
        }

        double res = stod(val);
        return res > INT_MAX ? -1 : res;
    }
};