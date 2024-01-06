/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

 

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1
 

Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
*/

// We can calculate the rectangle for each row, by perceiving each row as a histogram. 
// And each row's histogram depends on the above row and if the matrix[i][j] is '1' or not. Use dynamic programming to update it. 
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), max_area = 0;
        vector<int> hist(n,0);
        for ( int i = 0; i < m; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                hist[j] = matrix[i][j] == '1' ? hist[j] + 1 : 0;
            }
            max_area = max(max_area,maxhist(hist));
        }

        return max_area;
    }

    int maxhist(const vector<int>& hist) {
        int n = hist.size(), max_area = 0;
        stack<int> st;
        for ( int i = 0; i <= n; i++ ) {
            while( !st.empty() && (i == n || hist[st.top()] > hist[i]) )  {
                int h = hist[st.top()];
                st.pop();
                int l = st.empty() ? -1 : st.top();
                max_area = max(max_area, h*(i-l-1));
            }
            st.push(i);
        }

        return max_area;
    }
};