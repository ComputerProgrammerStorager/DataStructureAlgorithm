class Solution {
public:
    int calculate(string s) {
        int len = s.size(); 
        if ( len == 0 )
            return 0;
        stack<int> nums;
        int cur_num = 0, res = 0;
        char cur_op = '+';
        for ( int i = 0; i < len; i++ )
        {
            char cur_ch = s[i];
            if ( isdigit(cur_ch) )
            {
                cur_num = cur_num * 10 + (s[i]-'0');
            }

            if ( !isdigit(cur_ch) && !isspace(cur_ch) || i == len - 1 )
            {
                if ( cur_op == '+' ) {
                    nums.push(cur_num);
                }
                if ( cur_op == '-' ) {
                    nums.push(-cur_num);
                } 
                if ( cur_op == '*' )
                {
                    int top_num = nums.top();
                    nums.pop();
                    nums.push(top_num * cur_num);
                }
                if ( cur_op == '/') 
                {
                    int top_num = nums.top();
                    nums.pop();
                    nums.push(top_num/cur_num);
                }
                cur_op = cur_ch;
                cur_num = 0;
            }
        }

        while( !nums.empty() )
        {
            res += nums.top();
            nums.pop();
        }

        return res;
    }
};

// We can use a last number variable instead of a stack 

class Solution {
public:
    int calculate(string s) {
        int len = s.size();
        if ( len == 0 )
            return 0;
        int cur_num = 0, last_num = 0, res = 0;
        char sign = '+';
        for ( int i = 0; i < len; i++ )
        {
            char cur_ch = s[i];
            if ( isdigit(cur_ch) ) 
            {
                cur_num = cur_num * 10 + (cur_ch - '0');
            }
            if ( !isdigit(cur_ch) && !isspace(cur_ch) || i == len - 1)
            {
                if ( sign == '+' || sign == '-' )
                {
                    res += last_num;
                    last_num = sign == '+' ? cur_num : -cur_num;
                } else if ( sign == '*' )
                {
                    last_num = last_num * cur_num;
                } else if ( sign == '/' )
                {
                    last_num = last_num / cur_num;
                }

                sign = cur_ch;
                cur_num = 0;
            }
        }

        res += last_num;
        return res;
    }
};