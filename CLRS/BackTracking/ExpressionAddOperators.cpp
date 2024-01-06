/*
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
Example 3:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
 

Constraints:

1 <= num.length <= 10
num consists of only digits.
-231 <= target <= 231 - 1
Accepted
211.4K
Submissions
535K

*/

// consider each and every possible num by choosing the dividing positions 
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        dfs(res,num,"",0,0,0,target);
        return res;
    }

    void dfs(vector<string>& res, const string& input, string path, int pos, long curVal, long last, int target) {
        if ( pos == input.size() && curVal == target ) {
            res.push_back(path);
            return;
        }

        for ( int i = pos; i < input.size(); i++ ) {
            if ( i > pos && input[pos] == '0' ) 
                return;
            string tmp = input.substr(pos,i-pos+1);
            long val = stol(tmp);
            if ( pos == 0 ) { 
                dfs(res,input,path+tmp,pos+1,val,val,target);
            } else {
                dfs(res,input,path+"+"+tmp,pos+1,curVal+val,val,target);
                dfs(res,input,path+"-"+tmp,pos+1,curVal-val,-val,target);
                dfs(res,input,path+"*"+tmp,pos+1,curVal-last+last*val, last*val,target);
            }
        }
    }
};