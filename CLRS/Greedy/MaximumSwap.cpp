/*
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

 

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.
 

Constraints:

0 <= num <= 108
*/

// remember each digit's rightmax and swap the first digits is not the largest to its right side 
class Solution {
public:
    int maximumSwap(int num) {
        string digits = to_string(num);
        int n = digits.size(), maxIdx = -1;
        vector<int> rightmax(n,-1);
        for ( int i = n-1; i >= 0; i-- ) {
            if ( maxIdx == - 1 ) {
                rightmax[i] = -1;
                maxIdx = i;
            } else {
                if ( digits[i] > digits[maxIdx] ) {
                    rightmax[i] = -1;
                    maxIdx = i;
                } else if ( digits[i] == digits[maxIdx] ) {
                    rightmax[i] = -1;
                } else {
                    rightmax[i] = maxIdx;
                }
            }
        }

        for ( int i = 0; i < n; i++ ) {
            if ( rightmax[i] != -1 ) {
                swap(digits[i],digits[rightmax[i]]);
                break;
            }
        }
        return stol(digits);
    }
};