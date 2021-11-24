/*
Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
 

Example 1:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Example 2:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-109 <= matrix[i][j] <= 109
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-109 <= target <= 109

*/

// We know for sure the rows and cols are sorted, so we can do two binary search at each of the diagonal positions (min(row,col))

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int dia = min(m,n);
        for( int i = 0; i < dia; i++ )
            if ( BinarySearchRowCol(matrix,target,i) )
                return true;
        return false;
    }
    
    bool BinarySearchRowCol(vector<vector<int>> const& matrix, int target, int dia )
    {
        bool found = false;
        int row = matrix.size(), col = matrix[0].size();
        // search row first 
        int l = dia, r = col - 1;
        while( l <= r )
        {
            int mid = l + (r-l)/2; 
            if ( matrix[dia][mid] == target )
            {
                found = true;
                break;
            }
            if ( matrix[dia][mid] > target )
            {
                r = mid - 1;
            }
            else 
            {
                l = mid + 1;
            }
        }
        // if not found in the row, then searchin the column
        if ( !found )
        {
            l = dia, r = row - 1;
            while( l <= r )
            {
                int mid = l + (r-l) / 2;
                if ( matrix[mid][dia] == target )
                {
                    found = true;
                    break;
                }
                if ( matrix[mid][dia] < target )
                {
                    l = mid + 1;
                }
                else 
                {
                    r = mid - 1;
                }
            }
        }
        return found;
    }
};

// Divide and conquer 
// The problem can be perceived as searching the value in a submatrix. 
// Please note the following: the left-up element is the smallest and the bottom-right is the largest 
// Then we can partition the matrix into four submatries by using the above property 
// It's really helpfu to visualize by drawing a picture 
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        return searchsubmatrix(matrix,{0,0},{m-1,n-1},target);
    }
    // a searched submatrix is defined by left-up and bottom-right coordinates 
    bool searchsubmatrix(vector<vector<int>> const& matrix, pair<int,int> const& left_up, pair<int,int> const& bottom_right, int target)
    {
        int r1 = left_up.first, c1 = left_up.second, r2 = bottom_right.first, c2 = bottom_right.second;
        if ( r1 > r2 || c1 > c2 ) 
            return false;
        if ( target < matrix[r1][c1] || target > matrix[r2][c2] )
            return false;
        int mid_col = c1 + (c2-c1) / 2, mid_row = r1;
        while( mid_row <= r2 && matrix[mid_row][mid_col] <= target )
        {
            if ( matrix[mid_row][mid_col] == target )
                return true;
            mid_row++;
        }
        
        return searchsubmatrix(matrix,{mid_row,c1},{r2,mid_col-1},target) || searchsubmatrix(matrix,{r1,mid_col+1},{mid_row-1,c2},target);
    }
};

// line sweep starting from left-bottom or right-up
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int row = m - 1, col = 0;
        while( row >= 0 && col < n )
        {
            if ( matrix[row][col] == target )
                return true;
            if ( matrix[row][col] < target )
                col++;
            else 
                row--;
        }
        
        return false;
    }
};