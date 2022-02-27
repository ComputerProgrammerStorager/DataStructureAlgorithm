/*
Given a rectangle of size n x m, return the minimum number of integer-sided squares that tile the rectangle.

 

Example 1:



Input: n = 2, m = 3
Output: 3
Explanation: 3 squares are necessary to cover the rectangle.
2 (squares of 1x1)
1 (square of 2x2)
Example 2:



Input: n = 5, m = 8
Output: 5
Example 3:



Input: n = 11, m = 13
Output: 6
 

Constraints:

1 <= n, m <= 13

*/

//Side node:
// Claim: denote h(n,m) is the fewest number of square, then h(n,m) <= max(n,m). 
// we can prove this by induction.. 
// Base 1: if n == m, then h(n,m) == 1, then h(n,m) < max(n,m)
// Assum n > m: 
//      then h(n,m) <= 1 + h(n-m,m) <= 1 + max(n-m,m) 
//                                  <= max(n,m)
// if n < m, it's symmetric.

// We can divide an nxm rectangle in two ways:
// 1. Greedily partition the largest possible at each step 
// |------->    m   <---------|
//  ___________________________
// |              |           |
// |              |           |
// |    n x n     |  (n-m)xm  |
// |              |           |
// |______________|___________|

// 2. Try to partition left-bottom and right-up squares and conquer the remaining rectangles
//  This case has three subcases, as the value of s and k moves 
// |------->    m   <---------|
//  ___________________________
// |                   |      |
// |     rect1         |      | 
// --------------------|      |
// |              |    | kxk  |
// |              |rec2|      |
// |              |    |      |
// |     sxs      ------------|
// |              |  rect3    |
// |              |           |
// |______________|___________|

// |------->    m   <---------|
//  ___________________________
// |                   |      |
// |     rect1         | kxk  | 
// |-------------------|------|
// |              |           |
// |     rec2     |           |
// |              |           |
// ---------------|  rect3    |
// |              |           |
// |   sxs        |           |
// |______________|___________|