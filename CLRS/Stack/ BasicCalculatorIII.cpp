/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1+1"
Output: 2
Example 2:

Input: s = "6-4/2"
Output: 4
Example 3:

Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21
 

Constraints:

1 <= s <= 104
s consists of digits, '+', '-', '*', '/', '(', and ')'.
s is a valid expression.
*/

class Solution {
public:
    int calculate(string s) {
        stack<int> nums;
        stack<int> ops;
        bool hasprevnum = false;
        auto calc = [&] {
            int b = nums.top();
            nums.pop();
            int a = nums.top();
            nums.pop();
            char op = ops.top();
            ops.pop();
            if ( op == '+' )
                nums.push(a+b);
            if ( op == '-' )
                nums.push(a-b);
            if ( op == '*' )
                nums.push(a*b);
            if ( op == '/' )
                nums.push(a/b);
        };

        for ( int i = 0; i < s.length(); i++ )
        {
            const char c = s[i];
            if ( isdigit(c) )
            {
                int val = c -'0';
                while( i+1 < s.length() && isdigit(s[i+1]) )
                    val = val * 10 + (s[i++ + 1] - '0');
                nums.push(val);
                hasprevnum = true;
            } 
            if ( c == '(' )
            {
                ops.push('(');
                hasprevnum = false;
            }
            if ( c == ')' )
            {
                while(ops.top() != '(')
                    calc();
                ops.pop();
            }
            if ( c == '+' || c == '-' || c == '*' || c == '/' )
            {
                if ( !hasprevnum )
                    nums.push(0);
                while(!ops.empty() && precedes(ops.top(),c) )
                    calc();
                ops.push(c);
            }
        }
        while(!ops.empty())
            calc();
        return nums.top();
    }
private:
    // return true if op1 is an operator and has higher or equal precedece than op2 
    bool precedes(char op1, char op2)
    {
        if ( op1 == '(')
            return false;
        return op1 == '*' || op1 == '/' || op2 == '+' || op2 == '-';
    }
};

class Solution {
 public:
  int calculate(string s) {
    stack<int> nums;
    stack<int> ops;
    bool hasPrevNum = false;

    auto calc = [&]() {
      const int b = nums.top();
      nums.pop();
      const int a = nums.top();
      nums.pop();
      const char op = ops.top();
      ops.pop();
      if (op == '+')
        nums.push(a + b);
      else if (op == '-')
        nums.push(a - b);
      else if (op == '*')
        nums.push(a * b);
      else  // Op == '/'
        nums.push(a / b);
    };

    for (int i = 0; i < s.length(); ++i) {
      const char c = s[i];
      if (isdigit(c)) {
        int num = c - '0';
        while (i + 1 < s.length() && isdigit(s[i + 1]))
          num = num * 10 + (s[i++ + 1] - '0');
        nums.push(num);
        hasPrevNum = true;
      } else if (c == '(') {
        ops.push('(');
        hasPrevNum = false;
      } else if (c == ')') {
        while (ops.top() != '(')
          calc();
        ops.pop();  // Pop '('
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        if (!hasPrevNum)
          nums.push(0);
        while (!ops.empty() && precedes(ops.top(), c))
          calc();
        ops.push(c);
      }
    }

    while (!ops.empty())
      calc();

    return nums.top();
  }

 private:
  // Returns true if prevOp is a operator and
  // Priority(prevOp) >= priority(currOp)
  bool precedes(char prevOp, char currOp) {
    if (prevOp == '(')
      return false;
    return prevOp == '*' || prevOp == '/' || currOp == '+' || currOp == '-';
  }
};
